#include"stdafx.h"
#include "CLogEntity.h"
#include"CharHelper.h"
CLogEntity::CLogEntity()
{
	name = _T("");
	password = _T("");
}

CLogEntity::CLogEntity(const CString logname, const CString logpassword)
{
	name = logname;
	password = logpassword;
}

CLogEntity::~CLogEntity()
{
}

void CLogEntity::setBlock(LoginBlock lb)
{
	name=CharHelper::ToString(lb.name, sizeof(VARCHAR));
	password = CharHelper::ToString(lb.name, sizeof(VARCHAR));
}

LoginBlock CLogEntity::getBlock()
{
	LoginBlock lb;
	memset(&lb, 0, sizeof(LoginBlock));
	CharHelper::ToChars(lb.name, name, sizeof(VARCHAR));
	CharHelper::ToChars(lb.password, password, sizeof(VARCHAR));
	return lb;
}
