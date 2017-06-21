#pragma once
#include"CFieldEntity.h"
#include "FileHelper.h"
#include "global.h"
#include"FieldDao.h"
#include"FileLogic.h"
#include "LogLogic.h"
class FieldLogic
{
public:
	FieldLogic();
	~FieldLogic();
	bool CreateField(const CString dbName, const CString tbName, CFieldEntity & fd);
	//创建数据库
	//查询数据库
	bool getField(const CString dbName,const CString tbName,CFieldEntity &fd);
	bool getField(const CString dbName, const CString tbName,CString oldName,CString newName);
	bool getField(const CString dbName, const CString tbName, CString oldName,int newtype);
	bool getField(const CString dbName, const CString tbName, CString oldName);
	vector<CFieldEntity> GetFieldList(const CString dbName, const CString tbName);
private:
	FieldDao fieldDao;
	FileLogic filelogic;	//数据库文件的逻辑对象
};