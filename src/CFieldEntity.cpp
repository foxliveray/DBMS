#include "stdafx.h"
#include "CFieldEntity.h"
#include"CharHelper.h"
CFieldEntity::CFieldEntity()
{
	m_strName = _T("");			
	m_nType = DT_NONE;			
	m_nParam = -1;				
	GetLocalTime(&m_tMTime);	//最后一次修改时间
	m_nIntegrities = 0;			// 完整性约束的个数
}


CFieldEntity::CFieldEntity(const CFieldEntity & fieldEntity)
{
	m_strName = fieldEntity.m_strName;
	m_nType = fieldEntity.m_nType;
	m_nParam = fieldEntity.m_nParam;
	m_tMTime = fieldEntity.m_tMTime;
	m_nIntegrities = fieldEntity.m_nIntegrities;
}

CFieldEntity::CFieldEntity(CString name, int type, int paramNum, int integrity)
{
	GetLocalTime(&m_tMTime);
	m_strName = name;
	m_nType = type;
	m_nParam = paramNum;
	m_nIntegrities = integrity;
}

CFieldEntity::~CFieldEntity()
{

}

CString CFieldEntity::getFieldName()
{
	return m_strName;
}

void CFieldEntity::setFieldName(CString strName)
{
	m_strName = strName;
}

CString CFieldEntity::getFieldType()
{
	CString strName = _T("");
	switch (m_nType)
	{
	case CFieldEntity::DT_INTEGER:	// INT type
	{
		strName = _T("INT");
		break;
	}
	case CFieldEntity::DT_BOOL:		// BOOL type
	{
		strName = _T("BOOL");
		break;
	}
	case CFieldEntity::DT_DOUBLE:	// DOUBLE type
	{
		strName = _T("DOUBLE");
		break;
	}
	case CFieldEntity::DT_VARCHAR:	// VRACHAR type
	{
		strName = _T("VARCHAR");
		break;
	}
	case CFieldEntity::DT_DATETIME:	// DATETIME type
	{
		strName = _T("DATATIME");
		break;
	}
	default:
		break;
	}
	return strName;
}

void CFieldEntity::setFieldType(int type)
{
	m_nType = type;
}

void CFieldEntity::setParam(int num)
{
	m_nParam = num;
}

void CFieldEntity::setIntegrity(int num)
{
	m_nIntegrities = num;
}

int CFieldEntity::getFieldParamNum()
{
	return m_nType;
}

int CFieldEntity::GetParam() {
	return m_nParam;
}

int CFieldEntity::getFieldIntegrity()
{
	return m_nIntegrities;
}

SYSTEMTIME CFieldEntity::getTMTime()
{
	return m_tMTime;
}

void CFieldEntity::setTMTime(SYSTEMTIME t)
{
	m_tMTime = t;
}
void CFieldEntity::SetBlock(FieldBlock fb)
{
	m_strName = CharHelper::ToString(fb.name, sizeof(VARCHAR));
	m_tMTime = fb.mtime;
	m_nType = fb.type;
	m_nParam = fb.param;
	m_nIntegrities = fb.integrities;
}

FieldBlock CFieldEntity::GetBlock()
{
	FieldBlock fb;
	memset(&fb, 0, sizeof(FieldBlock));
	CharHelper::ToChars(fb.name, m_strName, sizeof(VARCHAR));
	fb.mtime = m_tMTime;
	fb.type = m_nType;
	fb.param = m_nParam;
	fb.integrities = m_nIntegrities;
	return fb;
}