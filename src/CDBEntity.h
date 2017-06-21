#pragma once
#include<cstring>
#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
#include"DataStructure.h"
#include"global.h"
#include "CharHelper.h"
class CDBEntity : public CObject
{
private:
	CString m_strName;//数据库名
	bool m_bType;//数据库类型
	CString m_strFilepath;//存放路径
	SYSTEMTIME m_tCtTime;//建库时间
public:
	//构造、析构函数
	CDBEntity(DatabaseBlock &db);
	CDBEntity(const CString strName);
	CDBEntity(void);
	~CDBEntity(void);
	CDBEntity(const CDBEntity &c);	//拷贝构造函数
	CDBEntity& operator =(const CDBEntity &d);		//赋值构造函数


	CString getDBName();
	void setDBName(CString strName);
	bool getDBType();
	void setDBType(bool type);
	CString getDBFilePath();
	void setDBFilePath(CString filePath);
	void setSystemTime(SYSTEMTIME t);
	SYSTEMTIME getSystenTime();

	//获取数据库块的信息
	DatabaseBlock GetBlock(void);
	//设置数据库块信息
	void SetBlock(DatabaseBlock db);
};