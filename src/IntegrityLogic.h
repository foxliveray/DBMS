#pragma once
#include "FileHelper.h"
#include "global.h"
#include"CIntegrityEntity.h"
#include"FileLogic.h"
#include"IntegrityDao.h"
class IntegrityLogic
{
public:
	IntegrityLogic();
	~IntegrityLogic();
	bool createIntegrity(const CString dbName, const CString tbName, CIntegrityEntity& fd);
	bool isPrimaryKey(const CString dbname, const CString tbName, const CString fieldName);
	bool isNotNullKey(const CString dbname, const CString tbName, const CString fieldName);
	bool isDefaultKey(const CString dbname, const CString tbName, const CString fieldName);
	CString getDefaultValue(const CString dbname, const CString tbName, const CString fieldName);
	bool getInter(const CString dbName, const CString tbName, CString oldName, CString newName);
private:
	IntegrityDao inteDao;
	FileLogic filelogic;	//数据库文件的逻辑对象
};