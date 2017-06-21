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

		file.SeekToEnd();		//��ת���ļ��Ŀ�ͷ����д��
		file.Write(&fd.GetBlock(), sizeof(FieldBlock));	//д�����ݿ�����Ϣ
		file.Close();

		return true;
	}
	catch (CException *e) {
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to create the Field file!"));
	}

	return false;
}

bool FieldDao::GetField(const CString strFilepath, CFieldEntity &fd)
{
	try {
		//����ƥ���ļ���
		CString strfieldName = fd.getFieldName();
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		bool  Exist = false;
		FieldBlock fbk;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name,sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//���ݿ�����ȫһ��
				fd.SetBlock(fbk);
				Exist = true;
				break;
			}
		}
		file.Close();
		return Exist;
	}
	catch (CException *e) {
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
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
			file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone);	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
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
			AfxMessageBox(_T("�ñ������ֶΣ�"), MB_OK);
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
		//����ƥ���ļ���
		CString strfieldName = oldNamme;
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		bool  Exist = false;
		FieldBlock fbk;
		CFieldEntity fb;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//���ݿ�����ȫһ��
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
		//ɾ��ԭ�ļ�����������ʱ�ļ�
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
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}

	return false;
}

bool FieldDao::ChangeFieldTType(const CString strFilepath, const CString strIndexPaath, CString oldNamme, int length)
{
	try {
		//����ƥ���ļ���
		CString strfieldName = oldNamme;
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		bool  Exist = false;
		FieldBlock fbk;
		CFieldEntity fb;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//���ݿ�����ȫһ��
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
		//ɾ��ԭ�ļ�����������ʱ�ļ�
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
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}

	return false;
}
bool FieldDao::DeleteField(const CString strFilepath, const CString strIndexPath, CString oldNamme)
{
	try {
		//����ƥ���ļ���
		CString strfieldName = oldNamme;
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		FieldBlock fbk;
		CFieldEntity fb;
		file.SeekToBegin();
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0) {
			CString strName = CharHelper::ToString(fbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName)!= 0) {//��һ���򱣴�����ʱ�ļ���
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
		//ɾ��ԭ�ļ�����������ʱ�ļ�
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
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}
	return false;
}
