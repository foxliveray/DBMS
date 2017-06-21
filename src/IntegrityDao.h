#pragma once
#include"CIntegrityEntity.h"
#include"AppException.h"

class IntegrityDao
{
public:
	IntegrityDao();
	~IntegrityDao();
	bool CreateIntegrity(const CString strFilepath, CIntegrityEntity &db, bool bAppend);
	bool GetIntegrity(const CString strFilepath, CIntegrityEntity &db);
	vector<CIntegrityEntity> readIntegrityList(const CString strFilepath);
	bool ChangeFieldticName(const CString strFilepath, const CString strIndexPaath, CString oldNamme, CString newName);
};