#include"stdafx.h"
#include "IntegrityDao.h"
#include"CharHelper.h"
#include"FileHelper.h"
IntegrityDao::IntegrityDao()
{
}

IntegrityDao::~IntegrityDao()
{
}

bool IntegrityDao::CreateIntegrity(const CString strFilepath, CIntegrityEntity & ib, bool bAppend)
{
	try {
		CFile file;
		if (bAppend == true) {
			if (file.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
				return false;
			}
		}
		else {
			if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
				return false;
			}
		}

		file.SeekToEnd();		//跳转至文件的开头进行写入
		file.Write(&ib.getBlock(), sizeof(IntegrityBlock));	//写入数据库块的信息
		file.Close();
		return true;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to create the Integrity file!"));
	}

	return false;
}

bool IntegrityDao::GetIntegrity(const CString strFilepath, CIntegrityEntity & ib)
{
	try {
		//首先匹配文件名
		CString strfieldName = ib.getFieldName();
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//以只读的方式打开文件
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
			return false;
		}

		//读取数据库信息
		bool  Exist = false;
		IntegrityBlock ibk;
		file.SeekToBegin();
		while (file.Read(&ibk, sizeof(IntegrityBlock)) > 0) {
			CString strName = CharHelper::ToString(ibk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//数据库名完全一致
				ib.SetBlock(ibk);
				Exist = true;
				break;
			}
		}
		file.Close();
		return Exist;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to read the FIELD file!"));
	}

}

vector<CIntegrityEntity> IntegrityDao::readIntegrityList(const CString strFilepath)
{
	vector<CIntegrityEntity>res;
	try {
		CFile file;
		file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone);	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
		IntegrityBlock fbk;

		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(IntegrityBlock)) > 0) {
			CIntegrityEntity fb;
			fb.SetBlock(fbk);
			res.push_back(fb);
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get all integrities!"));
	}

	return res;
}
bool IntegrityDao::ChangeFieldticName(const CString strFilepath, const CString strIndexPaath, CString oldNamme, CString newName)
{
	try {
		//首先匹配文件名
		CString strfieldName = oldNamme;
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//以只读的方式打开文件
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
			return false;
		}

		//读取数据库信息
		bool  Exist = false;
		CIntegrityEntity cie;
		IntegrityBlock ibk;
		file.SeekToBegin();
		while (file.Read(&ibk, sizeof(IntegrityBlock)) > 0) {
			CString strName = CharHelper::ToString(ibk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//数据库名完全一致
				CharHelper::ToChars(ibk.name, newName, sizeof(VARCHAR));
				Exist = true;
			}
			cie.SetBlock(ibk);
			if (FileHelper::IsVaildFile(strIndexPaath) == false) {
				if (FileHelper::CreateFile(strIndexPaath) == false) {
					return false;
				}
			}
			if (CreateIntegrity(strIndexPaath, cie, TRUE) == FALSE) {
				return false;
			}
		}
		file.Close();
		//删除原文件并重命名临时文件
		char* name1 = new char[sizeof(VARCHAR)];
		char* name2 = new char[sizeof(VARCHAR)];
		memset(name1, 0, sizeof(VARCHAR));
		memset(name2, 0, sizeof(VARCHAR));
		CharHelper::ToChars(name1, strIndexPaath, sizeof(VARCHAR));
		CharHelper::ToChars(name2, strFilepath, sizeof(VARCHAR));
		remove(name2);
		rename(name1, name2);

		return Exist;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}

	return false;
}