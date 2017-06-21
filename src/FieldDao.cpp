#include "stdafx.h"
#include "FieldDao.h"
#include<stdio.h>
#include"CharHelper.h"
#include <windows.h>
#include"FileHelper.h"
FieldDao::FieldDao()
{
}
FieldDao::~FieldDao()
{
}
bool FieldDao::CreateField(const CString strFilepath, CFieldEntity &fd, bool bAppend)
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
		file.Write(&fd.GetBlock(), sizeof(FieldBlock));	//写入数据库块的信息
		file.Close();

		return true;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to create the Field file!"));
	}

	return false;
}

bool FieldDao::GetField(const CString strFilepath, CFieldEntity &fd)
{
	try {
		//首先匹配文件名
		CString strfieldName = fd.getFieldName();
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
		FieldBlock fbk;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name,sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//数据库名完全一致
				fd.SetBlock(fbk);
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

	return false;
}

vector<CFieldEntity> FieldDao::ReadFieldList(CString strFilepath)
{
	vector<CFieldEntity>res;
	FileHelper f;
	try {
		CFile file;
		if (f.IsVaildFile(strFilepath)) {
			file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone);	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
			FieldBlock fbk;

			file.SeekToBegin();
			while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
				CFieldEntity fb;
				fb.SetBlock(fbk);
				res.push_back(fb);
			}
			file.Close();
		}
		else {
			AfxMessageBox(_T("该表不存在字段！"), MB_OK);
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get all FIELDS!"));
	}

	return res;
}

bool FieldDao::ChangeFieldName(const CString strFilepath, const CString strIndexPaath, CString oldNamme, CString newName)
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
		FieldBlock fbk;
		CFieldEntity fb;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//数据库名完全一致
				CharHelper::ToChars(fbk.name, newName,sizeof( VARCHAR));
				Exist = true;
			}
			fb.SetBlock(fbk);
			if (FileHelper::IsVaildFile(strIndexPaath) == false) {
				if (FileHelper::CreateFile(strIndexPaath) == false) {
					return false;
				}
			}
			if (CreateField(strIndexPaath,fb,TRUE)==FALSE) {
				return false;
			}
		}
		file.Close();
		//删除原文件并重命名临时文件
		char* name1=new char[sizeof(VARCHAR)];
		char* name2 = new char[sizeof(VARCHAR)];
		memset(name1, 0, sizeof(VARCHAR));
		memset(name2, 0, sizeof(VARCHAR));
		CharHelper::ToChars(name1, strIndexPaath, sizeof(VARCHAR));
		CharHelper::ToChars(name2, strFilepath, sizeof(VARCHAR));
		remove(name2);
	    rename(name1,name2);
		
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

bool FieldDao::ChangeFieldTType(const CString strFilepath, const CString strIndexPaath, CString oldNamme, int length)
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
		FieldBlock fbk;
		CFieldEntity fb;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//数据库名完全一致
				fbk.param = length;
				Exist = true;
			}
			fb.SetBlock(fbk);
			if (FileHelper::IsVaildFile(strIndexPaath) == false) {
				if (FileHelper::CreateFile(strIndexPaath) == false) {
					return false;
				}
			}
			if (CreateField(strIndexPaath, fb, TRUE) == FALSE) {
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
bool FieldDao::DeleteField(const CString strFilepath, const CString strIndexPath, CString oldNamme)
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
		FieldBlock fbk;
		CFieldEntity fb;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName)!= 0) {//不一致则保存至临时文件夹
				fb.SetBlock(fbk);
				if (FileHelper::IsVaildFile(strIndexPath) == false) {
					if (FileHelper::CreateFile(strIndexPath) == false) {
						return false;
					}
				}
				if (CreateField(strIndexPath, fb, TRUE) == FALSE) {
					return false;
				}
			}
		}
		//删除原文件并重命名临时文件
		file.Close();
		char* name1 = new char[sizeof(VARCHAR)];
		char* name2 = new char[sizeof(VARCHAR)];
		memset(name1, 0, sizeof(VARCHAR));
		memset(name2, 0, sizeof(VARCHAR));
		CharHelper::ToChars(name1, strIndexPath, sizeof(VARCHAR));
		CharHelper::ToChars(name2, strFilepath, sizeof(VARCHAR));
		remove(name2);
		rename(name1, name2);
		return TRUE;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}
	return false;
}
