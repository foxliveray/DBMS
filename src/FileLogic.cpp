#include "stdafx.h"
#include "FileLogic.h"
#include "FieldLogic.h"

FileLogic::FileLogic()
{
}

FileLogic::~FileLogic()
{
}

//获取数据库描述文件的路径
CString FileLogic::GetDBFile(void) {
	CString strPath = _T("");
	try {
		 //获取star.db文件的绝对路径
		strPath = GetAbsolutePath(_T("star.db"));
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get the path of 'star.db'."));
	}
	return strPath;
}

//获取数据库文件夹的路径
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

//将相对路径转化为绝对路径
CString FileLogic::GetAbsolutePath(const CString strRelativePath) {
	CString strFolder = _T("");
	try {
		//获取可执行文件的绝对路径
		wchar_t fullPath[MAX_PATH];		//MAX_PATH为系统定义常量，最大路径长度（260）
		::GetModuleFileName(NULL, fullPath, MAX_PATH);	//	获取当前进程已加载模块的完整路径名
		strFolder = fullPath;
		//获取可执行文件的文件夹路径
		int pos = strFolder.ReverseFind('\\');		//找到路径中最后一个反斜杠所在的位置，索引从0开始
		strFolder = strFolder.Left(pos + 1);		//取路径从左往右的pos+1个字符，正好取到最后一个\\
		//返回绝对路径
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
		//获取表描述文件的绝对路径
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
		//获取表描述文件的绝对路径
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
		//获取表描述文件的绝对路径
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
		//获取表描述文件的绝对路径
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