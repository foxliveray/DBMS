#include "stdafx.h"
#include "FileLogic.h"
#include "FieldLogic.h"

FileLogic::FileLogic()
{
}

FileLogic::~FileLogic()
{
}

//��ȡ���ݿ������ļ���·��
CString FileLogic::GetDBFile(void) {
	CString strPath = _T("");
	try {
		 //��ȡstar.db�ļ��ľ���·��
		strPath = GetAbsolutePath(_T("star.db"));
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get the path of 'star.db'."));
	}
	return strPath;
}

//��ȡ���ݿ��ļ��е�·��
CString FileLogic::GetDBFolder(const CString strDBName) {
	CString strFolder = _T("");
	try {
		strFolder.Format(_T("data\\%s"), strDBName);
		strFolder = GetAbsolutePath(strFolder);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get the path of the database folder."));
	}
	return strFolder;
}

//�����·��ת��Ϊ����·��
CString FileLogic::GetAbsolutePath(const CString strRelativePath) {
	CString strFolder = _T("");
	try {
		//��ȡ��ִ���ļ��ľ���·��
		wchar_t fullPath[MAX_PATH];		//MAX_PATHΪϵͳ���峣�������·�����ȣ�260��
		::GetModuleFileName(NULL, fullPath, MAX_PATH);	//	��ȡ��ǰ�����Ѽ���ģ�������·����
		strFolder = fullPath;
		//��ȡ��ִ���ļ����ļ���·��
		int pos = strFolder.ReverseFind('\\');		//�ҵ�·�������һ����б�����ڵ�λ�ã�������0��ʼ
		strFolder = strFolder.Left(pos + 1);		//ȡ·���������ҵ�pos+1���ַ�������ȡ�����һ��\\
		//���ؾ���·��
		return strFolder + strRelativePath;
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get the absolute path of the file."));
	}

	return strFolder;
}

CString FileLogic::GetTableFile(const CString strDBName) {
	CString strPath = _T("");
	try {
		//��ȡ�������ļ��ľ���·��
		strPath.Format(_T("data\\%s\\%s.tb"), strDBName, strDBName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get tb file path!"));
	}

	return strPath;
}
CString FileLogic::GetFieldFile(const CString strDBName,const CString strTBName) {
	CString strPath = _T("");
	try {
		//��ȡ�������ļ��ľ���·��
		strPath.Format(_T("data\\%s\\%s.tdf"), strDBName, strTBName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get field file path!"));
	}

	return strPath;
}

CString FileLogic::GetRecordFile(const CString strDBName, const CString strTableName)
{
	CString strPath = _T("");
	try
	{
		strPath.Format(_T("data\\%s\\%s.trd"), strDBName, strTableName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get the path of the table record file!"));
	}

	return strPath;
}

CString FileLogic::GetIntegrityFile(const CString strDBName, const CString strTBName) {
	CString strPath = _T("");
	try {
		//��ȡ�������ļ��ľ���·��
		strPath.Format(_T("data\\%s\\%s.tic"), strDBName, strTBName);
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get integrity file path!"));
	}

	return strPath;
}
CString FileLogic::GetLoginFile() {
	CString strPath = _T("");
	try {
		//��ȡ�������ļ��ľ���·��
		strPath.Format(_T("sys\\user.sys"));
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get login file path!"));
	}

	return strPath;
}

CString FileLogic::GetLogFile() {
	CString strPath = _T("");
	try {
		strPath.Format(_T("sys\\log.txt"));
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get log file path!"));
	}

	return strPath;
}

CString FileLogic::GetTempUsernameFile() {
	CString strPath = _T("");
	try {
		strPath.Format(_T("sys\\temp.txt"));
		strPath = GetAbsolutePath(strPath);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get temp file path!"));
	}

	return strPath;
}