#pragma once
#include "AppException.h"
class FileLogic
{
public:
	FileLogic();
	~FileLogic();
	//获取数据库描述文件的路径
	CString GetDBFile(void);
	//获取数据库文件夹的路径
	CString GetDBFolder(const CString strDBName);
	//获取表描述文件的路径
	CString GetTableFile(const CString strDBName);
	CString GetFieldFile(const CString strDBName, const CString strTBName);
	CString GetRecordFile(const CString strDBName, const CString strTableName);
	CString GetIntegrityFile(const CString strDBName, const CString strTBName);
	CString GetLoginFile();
	CString GetLogFile();
	CString GetTempUsernameFile();
private:
	//将相对路径转化为绝对路径
	CString GetAbsolutePath(const CString strRelativePath);
};

