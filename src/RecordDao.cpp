#include "stdafx.h"
#include "TimeHelper.h"
#include "AppException.h"
#include "RecordDao.h"

bool RecordDao::Insert(CString strFilepath, CTablEntity &te, CRecordEntity &re)
{
	try
	{
		CFile recordFile;
		if (recordFile.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			return false;
		recordFile.SeekToEnd(); //从文件尾开始写入

		Write(recordFile, te, re);
		recordFile.Close();

		return true;
	} //异常处理：插入记录失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("插入记录失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("插入记录失败！"));
	}

	return false;
}

int RecordDao::SelectAll(CString strFilepath, CTablEntity &te, RECORDARR &data)
{
	try
	{
		CFile recordFile;
		if (recordFile.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
			return false;
		recordFile.SeekToBegin();

		int nCount = 0;
		while (true)
		{
			CRecordEntity* pRecdEntity = new CRecordEntity();
			if (Read(recordFile, te, *pRecdEntity) == true)
			{
				data.Add(pRecdEntity);
				nCount++;
			}
			else
			{
				delete pRecdEntity;
				pRecdEntity = NULL;
				break;
			}
		}

		recordFile.Close();

		return nCount;
	} //异常处理：查询记录失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("查询记录失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("查询记录失败！"));
	}

	return -1;
}

bool RecordDao::Update(CString strFilepath, CTablEntity &te, RECORDARR &newData) //uniqueID starts from 0
{
	try
	{
		CFile recordFile;
		if (recordFile.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			return false;
		recordFile.SeekToBegin();

		for (int i = 0; i < newData.GetSize(); i++)
		{
			Write(recordFile, te, *newData.GetAt(i));
		}

		recordFile.Close();

		return true;
	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("更新记录失败！"));
	}

	return false;
}

bool RecordDao::Delete(CString strFilepath, CTablEntity &te, int uniqueID) //uniqueID starts from 0
{
	try
	{
		RECORDARR data;
		SelectAll(strFilepath, te, data);
		data.RemoveAt(uniqueID);

		CFile recordFile;
		if (recordFile.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			return false;
		recordFile.SeekToBegin();

		for (int i = 0; i < data.GetSize(); i++)
		{
			Write(recordFile, te, *data.GetAt(i));
		}
		recordFile.Close();

		return true;
	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("删除记录失败！"));
	}

	return false;
}

bool RecordDao::Rewrite(CTablEntity &te, RECORDARR &data)
{
	try
	{
		CFile recordFile;
		if (recordFile.Open(te.getTableTrdPath(), CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			return false;
		recordFile.SeekToBegin();

		for (int i = 0; i < data.GetSize(); i++)
		{
			Write(recordFile, te, *data.GetAt(i));
		}
		recordFile.Close();

		return true;
	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("刷新记录失败！"));
	}

	return false;
}

bool RecordDao::Write(CFile &recordFile, CTablEntity &te, CRecordEntity &re)
{
	try
	{
		int nFieldNum = te.getFieldNum();
		for (int i = 0; i < nFieldNum; i++)
		{
			CFieldEntity* pField = te.getField(i);

			CString fieldName = pField->getFieldName();
			CString strVal = re.get(fieldName);

			switch (pField->getFieldParamNum())
			{
			case CFieldEntity::DT_INTEGER:
			{
				int nVal = _wtoi(strVal);
				recordFile.Write(&nVal, sizeof(int));
				break;
			}
			case CFieldEntity::DT_BOOL:
			{
				int bVal = _wtoi(strVal);
				recordFile.Write(&bVal, sizeof(bool));
				break;
			}
			case CFieldEntity::DT_DOUBLE: //floating-point number
			{
				double dbVal = _wtof(strVal);
				recordFile.Write(&dbVal, sizeof(double));
				break;
			}
			case CFieldEntity::DT_DATETIME:
			{
				SYSTEMTIME st = TimeHelper::ToSystemTime(strVal);
				recordFile.Write(&st, sizeof(SYSTEMTIME));
				break;
			}
			case CFieldEntity::DT_VARCHAR:
			{
				/*CArchive arch(&recordFile, CArchive::store);
				arch << strVal;
				arch.Close();
				break;*/

				// 字符串的长度
			//	pField->setParam(256);
				int nSize = sizeof(char) * pField->GetParam();
				//创建一个缓存来储存这个字符串
				char* pBuf = new char[nSize];
				CharHelper::ToChars(pBuf, strVal, nSize);
				//写入文件
				recordFile.Write(pBuf, nSize);
				//释放缓存
				delete[] pBuf;
				break;
			}
			default: //异常处理：其他数据类型
			{
				throw new CAppException(_T("保存记录时遇到无法识别的数据类型！"));
				break;
			}
			} //end-switch
		} //end-for

		return true;
	} //异常处理：保存记录失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("保存记录失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("保存记录失败！"));
	}

	return false;
}

bool RecordDao::Read(CFile &recordFile, CTablEntity &te, CRecordEntity &re)
{
	try
	{
		bool readResult = 0;
		int nFieldNum = te.getFieldNum();
		for (int i = 0; i < nFieldNum; i++)
		{
			CFieldEntity* pField = te.getField(i);
			CString fieldName = pField->getFieldName();

			switch (pField->getFieldParamNum())
			{
			case CFieldEntity::DT_INTEGER:
			{
				/*int nVal;
				if (recordFile.Read(&nVal, sizeof(int)) == FALSE)
				return false;
				re.put(fieldName, nVal);
				break;*/
				readResult = readmode<int>(recordFile, fieldName, re);
				break;
			}
			case CFieldEntity::DT_BOOL:
			{
				readResult = readmode<bool>(recordFile, fieldName, re);
				break;
			}
			case CFieldEntity::DT_DOUBLE:
			{
				readResult = readmode<double>(recordFile, fieldName, re);
				break;
			}
			case CFieldEntity::DT_DATETIME:
			{
				readResult = readmode<SYSTEMTIME>(recordFile, fieldName, re);
				break;
			}
			case CFieldEntity::DT_VARCHAR:
			{
				/*
				CString strVal;
				CArchive arch(&recordFile, CArchive::load);
				arch >> strVal;
				arch.Close();
				re.put(fieldName, strVal);*/
				//pField->setParam(256);
				int nSize = sizeof(char) * pField->GetParam();
				char* pBuf = new char[nSize];
				if (recordFile.Read(pBuf, nSize) == 0)
				{
					return false;
				}
				re.put(fieldName, CharHelper::ToString(pBuf, nSize));
				delete[] pBuf;

				readResult = 1;
				break;
			}
			default: //异常处理：其他数据类型
			{
				throw new CAppException(_T("读取记录时遇到无法识别的数据类型！"));
				break;
			}
			}//end-switch
		} //end-for

		return readResult;
	} //异常处理：读取记录失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("读取记录失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("读取记录失败！"));
	}

	return false;
}

template<typename T>
bool RecordDao::readmode(CFile &file, CString &field, CRecordEntity &cre)
{
	T value;
	if (file.Read(&value, sizeof(T)) == FALSE)
		return false;
	cre.put(field, value);
	return true;
}