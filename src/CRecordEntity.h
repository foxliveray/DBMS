#pragma once

#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
#include"DataStructure.h"
#include"global.h"
class CRecordEntity : public CObject
{
private:
	CMapStringToString m_mapData;
public:
	CRecordEntity();
	CRecordEntity(CRecordEntity &record);
	CRecordEntity &operator =(const CRecordEntity &e);
	~CRecordEntity();

	void put(CString strKey,CString strValue);
	void put(CString strKey, int nValue);
	void put(CString strKey, double dbValue);
	void put(CString strKey, SYSTEMTIME t);

	CString get(CString strKey);

	void deleteField(CString strKey);

};
typedef CTypedPtrArray<CPtrArray, CRecordEntity*>RECORDARR;