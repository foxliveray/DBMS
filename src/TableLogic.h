#pragma once
#include "CTableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"
#include "FileHelper.h"
#include "LogLogic.h"
class TableLogic
{
public:
	//创建一个表
	bool CreateTable(const CString strDBName, CTablEntity &te);
	//查询表信息
	int GetTables(const CString strDBName, TABLEARR &arrTables);
	//获取该数据库内的所有表描述信息
	vector <CTablEntity> getTableList(const CString dbname);
	//修改表名
	bool ModifyTable(const CString &dbname, CString &oldTBName, CString &newTBName);
	//删除表
	bool DeleteTable(const CString &dbname, CString tbname);
private:
	TableDao m_dao;
	FileLogic m_fileLogic;	
};

