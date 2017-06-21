#include "stdafx.h"
#include"CDBEntity.h"

CDBEntity::CDBEntity(DatabaseBlock &db)
{
	//CString ��char*��ת�����ܻ������
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

//�������캯��
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

//��ȡ���ݿ�ṹ����Ϣ
DatabaseBlock CDBEntity::GetBlock(void) {
	DatabaseBlock db;
	//��ʼ���ڴ�ռ�
	memset(&db, 0, sizeof(DatabaseBlock));
	CharHelper::ToChars(db.filepath, m_strFilepath, sizeof(VARCHAR));  
	CharHelper::ToChars(db.name, m_strName, sizeof(VARCHAR));
	db.crtime = m_tCtTime;
	db.type = m_bType;
	return db;
}

//�������ݿ����Ϣ
void CDBEntity::SetBlock(DatabaseBlock db) {
	m_strName = CharHelper::ToString(db.name, sizeof(VARCHAR));
	m_strFilepath = CharHelper::ToString(db.filepath, sizeof(VARCHAR));
	m_bType = db.type;
	m_tCtTime = db.crtime;
}