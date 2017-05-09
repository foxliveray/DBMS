//数据库文件操作类DBDao实现文件
#include "stdafx.h"
#include "CDBEntity.h"
#include "AppException.h"
#include "DBDao.h"

//创建一个数据库
//输入参数：
// const CString filePath：数据库描述文件路径
// const CDBEntity db：该数据库实体（已包含数据库名）
// bool bAppend：是否以添加的形式写入文件；true即以添加的形式写入，false即重写
bool DBDao::CreateDB(const CString filePath, const CDBEntity db, bool bAppend)
{
	try
	{
		CFile dbFile;
		if (bAppend == true)
		{
			if (dbFile.Open(filePath, CFile::modeWrite | CFile::shareDenyWrite) == false)
				return false;
		}
		else
			if (dbFile.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == false)
				return false;

		dbFile.SeekToBegin();
		dbFile.Write(&db, sizeof(CDBEntity));
		dbFile.Close();

		return true;
	} //异常处理：创建数据库失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("创建数据库文件失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("创建数据库文件失败！"));
	}

	return false;
}

//获取一个数据库的信息
//输入参数：
// const CString filePath：数据库描述文件路径
// CDBEntity &db：用于存储查询结果的CDBEntity对象
//返回参数：是否成功获取数据库信息；true即该数据库已存在，false即没有数据库与该数据库重名
bool DBDao::GetDatabase(const CString filePath, CDBEntity &db)
{
	try
	{
		CString dbName = db.getDBName();
		if (dbName.GetLength() == 0)
			return false;

		CFile dbFile;
		if (dbFile.Open(filePath, CFile::modeRead | CFile::shareDenyNone) == false)
			return false;
		dbFile.SeekToBegin();

		bool bExist = false;
		CDBEntity cdb;

		while (dbFile.Read(&cdb, sizeof(CDBEntity)) > 0)
		{
			CString strName = cdb.getDBName();
			if (strName.CompareNoCase(dbName) == 0)
			{
				db.copyDB(cdb);
				bExist = true;
				break;
			}
		}

		dbFile.Close();

		return bExist;
	} //异常处理：获取数据库信息失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("打开数据库文件失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("打开数据库文件失败！"));
	}

	return false;
}
