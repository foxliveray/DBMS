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
	//创建数据库
	bool CreateDatabase(CDBEntity &db);
	//查询数据库
	bool GetDatabase(CDBEntity &db);
	vector<CDBEntity>  GetDatabaseList();
	bool DeleteDatabase(CString &dbname);
	bool ModifyDatabase(CString &oldDBName, CString &newDBName);
	bool BackupDatabase(CString & dbName, CString & destPath);
private:
	DBDao m_dao;			//数据库数据操作对象
	FileLogic m_logic;	//数据库文件的逻辑对象
};

