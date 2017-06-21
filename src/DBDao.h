#pragma once
#include "CDBEntity.h"
#include "AppException.h"
#include "FileLogic.h"
#include "FileHelper.h"
class DBDao
{

public :
	//创建数据库，将数据库信息保存到文件中
	bool Create(const CString strFilepath, CDBEntity &db, bool bAppend);
	//从文件中读取数据库信息
	bool GetDatabase(const CString strFilepath, CDBEntity &db);
	//读取所有数据库描述信息
	vector<CDBEntity> ReadDBList(CString strFilepath);
	//删除star.db文件中关于该数据库的块信息
	bool DeleteDB(const CString strFilepath, CString &dbname);
	//根据数据库名删除关于该数据库的全部文件
	bool DeleteDBFile(CString &dbName);
	//修改数据库名
	bool ModifyDB(CString strFilePath, CString &oldDBName, CString &newDBName);
	//修改数据库路径名及表描述文件名
	bool ModifyDBPath(CString &oldDBName, CString &newDBName);
	bool BackupDB(CString & dbName, CString & filepath, CString & destPath);
};

