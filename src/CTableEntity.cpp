#include "stdafx.h"
#include "CTableEntity.h"

CTablEntity::CTablEntity()
{
	m_strName = _T("");			
	m_nRecordNum = 0;			
	m_strTdfPath = _T("");		
	m_strTrdPath = _T("");		
	m_strTicPath = _T("");
	m_strTidPath = _T("");
	GetLocalTime(&m_tCrTime);	
	m_tMTime = m_tCrTime;		
}
CTablEntity::CTablEntity(TableBlock &tb) {
	this->SetBlock(tb);
}

CTablEntity::CTablEntity(CString name)
{
	m_strName = name;
	m_nRecordNum = 0;
	m_strTdfPath = _T("");
	m_strTrdPath = _T("");
	m_strTicPath = _T("");
	m_strTidPath = _T("");
	GetLocalTime(&m_tCrTime);
	m_tMTime = m_tCrTime;
}

CTablEntity::CTablEntity(const CTablEntity &c) {
	m_strName = c.m_strName;
	m_nRecordNum = c.m_nRecordNum;
	m_strTdfPath = c.m_strTdfPath;
	m_strTrdPath = c.m_strTrdPath;
	m_strTicPath = c.m_strTicPath;
	m_strTidPath = c.m_strTidPath;
	m_tCrTime = c.m_tCrTime;
	m_tMTime = c.m_tMTime;
}

CTablEntity& CTablEntity::operator=(const CTablEntity &d) {
	m_strName = d.m_strName;
	m_nRecordNum = d.m_nRecordNum;
	m_strTdfPath = d.m_strTdfPath;
	m_strTrdPath = d.m_strTrdPath;
	m_strTicPath = d.m_strTicPath;
	m_strTidPath = d.m_strTidPath;
	m_tCrTime = d.m_tCrTime;
	m_tMTime = d.m_tMTime;

	return *this;
}

CTablEntity::~CTablEntity()
{
	int nCount = m_arrFields.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CFieldEntity* pField = m_arrFields.GetAt(i);
		if (pField != NULL)
		{
			delete pField;
			pField = NULL;
		}
	}
}

void CTablEntity::addField(CFieldEntity & fe)
{
	CFieldEntity* pField = new CFieldEntity(fe);
	m_arrFields.Add(pField);
}

void CTablEntity::deleteField(CFieldEntity & fe)
{
	for (int i = 0; i < m_arrFields.GetCount(); i++) {
		CFieldEntity* nfe = m_arrFields.GetAt(i);
		if (nfe->getFieldName() == fe.getFieldName()) {
			m_arrFields.RemoveAt(i);
			break;
		}
	}
}

CFieldEntity* CTablEntity::getField(int nIndex)
{
	return m_arrFields.GetAt(nIndex);
}

CString CTablEntity::getTableName()
{
	return CString(m_strName);
}

void CTablEntity::setTableName(CString strName)
{
	m_strName = strName;
}

int CTablEntity::getRecordNum()
{
	return m_nRecordNum;
}

int CTablEntity::getFieldNum()
{
	return m_arrFields.GetSize();
}

void CTablEntity::addNewRecord()
{
	m_nRecordNum++;
}

void CTablEntity::deleteRecord()
{
	m_nRecordNum--;
}

SYSTEMTIME CTablEntity::getTCRTime()
{
	return m_tCrTime;
}

void CTablEntity::setTCRTime(SYSTEMTIME t)
{
	m_tCrTime = t;
}

SYSTEMTIME CTablEntity::getTMTime()
{
	return m_tMTime;
}

void CTablEntity::setTMTime(SYSTEMTIME t)
{
	m_tCrTime = t;
}

CString CTablEntity::getTableTdfPath()
{
	return CString(m_strTdfPath);
}

void CTablEntity::setTableTdfPath(CString filePath)
{
	m_strTdfPath = filePath;
}

CString CTablEntity::getTableTrdPath()
{
	return CString(m_strTrdPath);
}

void CTablEntity::setTableTrdPath(CString filePath)
{
	m_strTrdPath = filePath;
}

CString CTablEntity::getTableTicPath()
{
	return CString(m_strTicPath);
}

void CTablEntity::setTableTicPath(CString filePath)
{
	m_strTicPath = filePath;
}

CString CTablEntity::getTableTidPath()
{
	return CString(m_strTidPath);
}

void CTablEntity::setTableTidPath(CString filePath)
{
	m_strTidPath = filePath;
}

//获取表块的信息
TableBlock CTablEntity::GetBlock() {
	TableBlock tb;
	memset(&tb, 0, sizeof(TableBlock));
	CharHelper::ToChars(tb.name, m_strName, sizeof(VARCHAR));
	tb.field_num = m_arrFields.GetCount();
	tb.record_num = m_nRecordNum;
	CharHelper::ToChars(tb.tdf, m_strTdfPath, sizeof(VARCHAR));
	CharHelper::ToChars(tb.tic, m_strTicPath, sizeof(VARCHAR));
	CharHelper::ToChars(tb.tid, m_strTidPath, sizeof(VARCHAR));
	CharHelper::ToChars(tb.trd, m_strTrdPath, sizeof(VARCHAR));
	tb.crtime = m_tCrTime;
	tb.mtime = m_tMTime;

	return tb;
}

void CTablEntity::SetBlock(TableBlock tb) {
	m_strName = CharHelper::ToString(tb.name, sizeof(VARCHAR));
	m_nRecordNum = tb.record_num;
	m_strTdfPath = CharHelper::ToString(tb.tdf, sizeof(VARCHAR));
	m_strTrdPath = CharHelper::ToString(tb.trd, sizeof(VARCHAR));
	m_strTicPath = CharHelper::ToString(tb.tic, sizeof(VARCHAR));
	m_strTidPath = CharHelper::ToString(tb.tid, sizeof(VARCHAR));
	m_tCrTime = tb.crtime;
	m_tMTime = tb.mtime;
}