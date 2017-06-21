#pragma once
#include "CTableEntity.h"
#include "CRecordEntity.h"
#include "TableDao.h"
#include "RecordDao.h"
#include "FileLogic.h"

class RecordLogic
{
public:
	bool Insert(const CString dbName, CTablEntity &te, CRecordEntity &re);
	bool SelectAll(CString dbName, CTablEntity &te, RECORDARR &data);
	bool Update(CString dbName, CTablEntity & te, RECORDARR & newData);
	bool Delete(CString dbName, CTablEntity &te, int uniqueID);
	bool Rewrite(CTablEntity &te, RECORDARR &data);
	void DetailedSelect(CString DBName, CTablEntity &te, vector<CString> compare, vector<CString> values, RECORDARR *data);
private:
	RecordDao m_daoRecord;
	TableDao m_daoTable;
	FileLogic m_fileLogic;
};