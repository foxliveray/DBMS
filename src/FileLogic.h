#pragma once
#include "AppException.h"
class FileLogic
{
public:
	FileLogic();
	~FileLogic();
	//��ȡ���ݿ������ļ���·��
	CString GetDBFile(void);
	//��ȡ���ݿ��ļ��е�·��
	CString GetDBFolder(const CString strDBName);
	//��ȡ�������ļ���·��
	CString GetTableFile(const CString strDBName);
	CString GetFieldFile(const CString strDBName, const CString strTBName);
	CString GetRecordFile(const CString strDBName, const CString strTableName);
	CString GetIntegrityFile(const CString strDBName, const CString strTBName);
	CString GetLoginFile();
	CString GetLogFile();
	CString GetTempUsernameFile();
private:
	//�����·��ת��Ϊ����·��
	CString GetAbsolutePath(const CString strRelativePath);
};

