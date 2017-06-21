#pragma once
#include "CTableEntity.h"
#include "CRecordEntity.h"

class RecordDao
{
public:
	bool Insert(CString strFilepath, CTablEntity &te, CRecordEntity &re);
	int SelectAll(CString strFilepath, CTablEntity &te, RECORDARR &data);
	bool Update(CString dbName, CTablEntity & te, RECORDARR & newData);
	bool Delete(CString strFilepath, CTablEntity &te, int uniqueID);
	bool Rewrite(CTablEntity &te, RECORDARR &data);

private:
	bool Write(CFile &recordFile, CTablEntity &te, CRecordEntity &re);
	bool Read(CFile &recordFile, CTablEntity &te, CRecordEntity & re);
	template<typename T>
	bool readmode(CFile &rfile, CString &fieldName, CRecordEntity &cre);

};