#include "stdafx.h"
#include "CRecordEntity.h"

CRecordEntity::CRecordEntity()
{

}

CRecordEntity::CRecordEntity(CRecordEntity & record)
{
	POSITION pos = record.m_mapData.GetStartPosition();
	CString strFieldName, strValue;
	while (pos)
	{
		record.m_mapData.GetNextAssoc(pos, strFieldName, strValue);
		m_mapData.SetAt(strFieldName, strValue);
	}
}

CRecordEntity &CRecordEntity::operator =(const CRecordEntity &e)
{
	CString strFieldName, strValue;
	POSITION ipos = e.m_mapData.GetStartPosition();
	while (ipos != NULL)
	{
		e.m_mapData.GetNextAssoc(ipos, strFieldName, strValue);
		m_mapData.SetAt(strFieldName, strValue);
	}

	return *this;
}

CRecordEntity::~CRecordEntity()
{
}

void CRecordEntity::put(CString strKey, CString strValue)
{
	m_mapData.SetAt(strKey, strValue);
}

void CRecordEntity::put(CString strKey, int nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	m_mapData.SetAt(strKey,strValue);
}

void CRecordEntity::put(CString strKey, double dbValue)
{
	CString strValue;
	strValue.Format(_T("%f"), dbValue);
	m_mapData.SetAt(strKey,strValue);
}

void CRecordEntity::put(CString strKey, SYSTEMTIME t)
{
	CString strTime;
	strTime.Format(_T("%04u-%02u-%02u %02u:%02u:%02u"), t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	//strTime.Format(_T("%02u:%02u:%02u %03u"), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	m_mapData.SetAt(strKey,strTime);
}

CString CRecordEntity::get(CString strKey)
{
	CString strVal;
	if (m_mapData.Lookup(strKey, strVal) == FALSE)
	{
		// Get the default value
		strVal = _T("");
	}
	return strVal;
}

void CRecordEntity::deleteField(CString strKey)
{
	m_mapData.RemoveKey(strKey);
}

