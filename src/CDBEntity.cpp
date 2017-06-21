#include "stdafx.h"
#include"CDBEntity.h"

CDBEntity::CDBEntity(DatabaseBlock &db)
{
	//CString 和char*的转换可能会出问题
	//m_strName = db.name;
	//m_strFilepath = db.filepath;
	//m_bType = db.type;
	//m_tCtTime = db.crtime;
	this->SetBlock(db);
}

CDBEntity::CDBEntity(const CString strName)
{
	m_strFilepath= _T("");
	m_bType = false;
	m_strName = strName;
	GetLocalTime(&m_tCtTime);
}

CDBEntity::CDBEntity(void)
{
	GetSystemTime(&m_tCtTime);
	m_strFilepath = _T("");
	m_bType = false;
	m_strName = _T("");
}

//拷贝构造函数
CDBEntity::CDBEntity(const CDBEntity &c) {
	m_strFilepath = c.m_strFilepath;
	m_bType = c.m_bType;
	m_strName = c.m_strName;
	m_tCtTime = c.m_tCtTime;
}

CDBEntity& CDBEntity::operator =(const CDBEntity &d) {
	m_strFilepath = d.m_strFilepath;
	m_bType = d.m_bType;
	m_strName = d.m_strName;
	m_tCtTime = d.m_tCtTime;

	return *this;
}

CDBEntity::~CDBEntity(void)
{
}

CString CDBEntity::getDBName()
{
	return m_strName;
}

void CDBEntity::setDBName(CString strName)
{
	m_strName = strName;
}

bool CDBEntity::getDBType()
{
	return m_bType;
}

void CDBEntity::setDBType(bool type)
{
	m_bType = type;
}

CString CDBEntity::getDBFilePath()
{
	return m_strFilepath;
}

void CDBEntity::setDBFilePath(CString filePath)
{
	m_strFilepath = filePath;
}

void CDBEntity::setSystemTime(SYSTEMTIME t)
{
	m_tCtTime = t;
}

SYSTEMTIME CDBEntity::getSystenTime()
{
	return m_tCtTime;
}

//获取数据库结构的信息
DatabaseBlock CDBEntity::GetBlock(void) {
	DatabaseBlock db;
	//初始化内存空间
	memset(&db, 0, sizeof(DatabaseBlock));
	CharHelper::ToChars(db.filepath, m_strFilepath, sizeof(VARCHAR));  
	CharHelper::ToChars(db.name, m_strName, sizeof(VARCHAR));
	db.crtime = m_tCtTime;
	db.type = m_bType;
	return db;
}

//设置数据库块信息
void CDBEntity::SetBlock(DatabaseBlock db) {
	m_strName = CharHelper::ToString(db.name, sizeof(VARCHAR));
	m_strFilepath = CharHelper::ToString(db.filepath, sizeof(VARCHAR));
	m_bType = db.type;
	m_tCtTime = db.crtime;
}