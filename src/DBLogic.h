#pragma once
#include "CDBEntity.h"
#include "FileLogic.h"
#include "DBDao.h"
#include "FileHelper.h"
#include "global.h"
#include "LogLogic.h"
class DBLogic
{
public:
	DBLogic();
	~DBLogic();
	//�������ݿ�
	bool CreateDatabase(CDBEntity &db);
	//��ѯ���ݿ�
	bool GetDatabase(CDBEntity &db);
	vector<CDBEntity>  GetDatabaseList();
	bool DeleteDatabase(CString &dbname);
	bool ModifyDatabase(CString &oldDBName, CString &newDBName);
	bool BackupDatabase(CString & dbName, CString & destPath);
private:
	DBDao m_dao;			//���ݿ����ݲ�������
	FileLogic m_logic;	//���ݿ��ļ����߼�����
};

