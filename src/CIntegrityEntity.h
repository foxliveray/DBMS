#pragma once
#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
#include<afxtempl.h>
#include"DataStructure.h"
#include"global.h"
class CIntegrityEntity : public CObject
{
private:
	CString fieldName;
	int isPrimary;
	int isNotNull;
	int isDefault;
	CString DefaultValue;
public:
	CIntegrityEntity();
	CIntegrityEntity(const CIntegrityEntity & integrityEntity);
	CIntegrityEntity(CString name, int p, int n, int d, CString v);
	~CIntegrityEntity();
	int getIsPrimary();
	int getIsNotNull();
	int getIsDefault();
	CString getFieldName();
	CString getDefault();
	void setPrimary(int p);
	void setNotNull(int n);
	void setDefault(int d);
	void setName(CString name);
	void setDefaultValue(CString v);
	void SetBlock(IntegrityBlock ib);
	IntegrityBlock getBlock();
};