#include "stdafx.h"
#include "CIntegrityEntity.h"
#include"CharHelper.h"
CIntegrityEntity::CIntegrityEntity()
{
	fieldName = _T("");
	isPrimary = 0;
	isDefault = 0;
	isNotNull = 0;
	DefaultValue = _T("");
}
CIntegrityEntity::CIntegrityEntity(const CIntegrityEntity & integrityEntity)
{
	fieldName = integrityEntity.fieldName;
	isPrimary = integrityEntity.isPrimary;
	isNotNull = integrityEntity.isNotNull;
	isDefault = integrityEntity.isDefault;
	DefaultValue = integrityEntity.DefaultValue;
}
CIntegrityEntity::CIntegrityEntity(CString name, int primary, int n, int d, CString v)
{
	fieldName = name;
	isPrimary = primary;
	isNotNull = n;
	isDefault = d;
	DefaultValue = v;
}

CIntegrityEntity::~CIntegrityEntity()
{
}

int CIntegrityEntity::getIsPrimary()
{
	return isPrimary;
}

int CIntegrityEntity::getIsNotNull()
{
	return isNotNull;
}

int CIntegrityEntity::getIsDefault()
{
	return isDefault;
}

CString CIntegrityEntity::getFieldName()
{
	return fieldName;
}

CString CIntegrityEntity::getDefault()
{
	return DefaultValue;
}

void CIntegrityEntity::setPrimary(int p)
{
	isPrimary = p;
}

void CIntegrityEntity::setNotNull(int n)
{
	isNotNull = n;
}

void CIntegrityEntity::setDefault(int d)
{
	isDefault = d;
}

void CIntegrityEntity::setName(CString name)
{
	fieldName = name;
}

void CIntegrityEntity::setDefaultValue(CString v)
{
	DefaultValue = v;
}

void CIntegrityEntity::SetBlock(IntegrityBlock ib)
{
	fieldName = CharHelper::ToString(ib.name, sizeof(VARCHAR));
	isPrimary = ib.isPrimary;
	isNotNull = ib.isNotNull;
	isDefault = ib.isDefault;
	DefaultValue = ib.defaultValue;
}

IntegrityBlock CIntegrityEntity::getBlock()
{
	IntegrityBlock ib;
	memset(&ib, 0, sizeof(IntegrityBlock));
	CharHelper::ToChars(ib.name, fieldName, sizeof(VARCHAR));
	CharHelper::ToChars(ib.defaultValue, DefaultValue, sizeof(VARCHAR));
	ib.isPrimary = isPrimary;
	ib.isNotNull = isNotNull;
	ib.isDefault = isDefault;
	return ib;
}
