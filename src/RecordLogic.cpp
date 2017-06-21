#include "stdafx.h"
#include "FileHelper.h"
#include "RecordLogic.h"
#include "FileLogic.h"
#include "FieldLogic.h"
#include "LogLogic.h"

bool RecordLogic::Insert(const CString dbName, CTablEntity &te, CRecordEntity &re)
{
	try
	{
		CString trdPath = m_fileLogic.GetRecordFile(dbName, te.getTableName());

		if (FileHelper::IsVaildFile(trdPath) == false)
			if (FileHelper::CreateFile(trdPath) == false)
				return false;

		if (m_daoRecord.Insert(trdPath, te, re) == false)
			return false;

		te.addNewRecord();

		CString tableFile = m_fileLogic.GetTableFile(dbName);
		if (m_daoTable.AlterTable(tableFile, te) == false)
			return false;
		else {
			LogLogic logic;
			logic.WriteLogs(CString("Insert an record") + CString("from database: ") + dbName + CString(" table: ") +te.getTableName());
			return true;
		}

	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("²åÈë¼ÇÂ¼Ê§°Ü£¡"));
	}

	return false;
}

bool RecordLogic::SelectAll(CString dbName, CTablEntity &te, RECORDARR &data)
{
	CString trdPath = m_fileLogic.GetRecordFile(dbName, te.getTableName());
	try
	{
		if (m_daoRecord.SelectAll(trdPath, te, data) == false)
			return false;
		else {
			LogLogic logic;
			logic.WriteLogs(CString("Select all records") + CString("from database: ") + dbName + CString(" table: ") + te.getTableName());
			return true;
		}

	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("²éÑ¯¼ÇÂ¼Ê§°Ü£¡"));
	}

	return false;
}

bool RecordLogic::Update(CString dbName, CTablEntity &te, RECORDARR &newData)
{
	CString trdPath = m_fileLogic.GetRecordFile(dbName, te.getTableName());

	try
	{
		if (m_daoRecord.Update(trdPath, te, newData) == false)
			return false;

		return true;
	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("¸üÐÂ¼ÇÂ¼Ê§°Ü£¡"));
	}
}

bool RecordLogic::Delete(CString dbName, CTablEntity &te, int uniqueID)
{
	CString trdPath = m_fileLogic.GetRecordFile(dbName, te.getTableName());

	try
	{
		if (m_daoRecord.Delete(trdPath, te, uniqueID) == false)
			return false;
		else {
			LogLogic logic;
			logic.WriteLogs(CString("Delete a record") + CString("from database: ") + dbName + CString(" table: ") + te.getTableName());
			return true;
		}

	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("É¾³ý¼ÇÂ¼Ê§°Ü£¡"));
	}
}

bool RecordLogic::Rewrite(CTablEntity &te, RECORDARR &data)
{
	try
	{
		if (m_daoRecord.Rewrite(te, data) == false)
			return false;

		return true;
	}
	catch (CException *e)
	{
		e->Delete();
		throw new CAppException(_T("Ë¢ÐÂ¼ÇÂ¼Ê§°Ü£¡"));
	}
}

void RecordLogic::DetailedSelect(CString DBName, CTablEntity &te, vector<CString> compare, vector<CString> values, RECORDARR *data) {
	CString trdPath = m_fileLogic.GetRecordFile(DBName, te.getTableName());
	RECORDARR AllData;
	m_daoRecord.SelectAll(trdPath, te, AllData);
	CRecordEntity* oneRecord;
	vector<CFieldEntity> list;
	FieldLogic logic;
	FileLogic f;
	CString tbName = te.getTableName();
	list = logic.GetFieldList(DBName, tbName);

	for (int i = 0; i < AllData.GetSize(); i++)
	{
		oneRecord = AllData.GetAt(i);
		bool condition = true;
		for (int i = 0; i < compare.size(); i++)
		{
			if (values[i] != L"")
			{
				if (compare[i] == L"="&&oneRecord->get(list[i].getFieldName()) != values[i])
				{
					condition = false; break;
				}
				else if (compare[i] == L">"&&oneRecord->get(list[i].getFieldName()) <= values[i])
				{
					condition = false; break;
				}
				else if (compare[i] == L"<"&&oneRecord->get(list[i].getFieldName()) >= values[i])
				{
					condition = false; break;
				}
			}
			else if (values[i] == L"")
			{
				condition = false;
			}

			if (condition)
				data->Add(oneRecord);
		}
	}
}