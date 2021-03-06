#include "stdafx.h"
#include "FieldLogic.h"

FieldLogic::FieldLogic()
{
}

FieldLogic::~FieldLogic()
{
}

bool FieldLogic::CreateField(const CString dbName, const CString tbName, CFieldEntity & fd)
{
	try {
		//判断该文件是否存在，如果不存在，就会创建一个新文件
		CString strfieldpath = filelogic.GetFieldFile(dbName, tbName);
		if (FileHelper::IsVaildFile(strfieldpath) == false) {
			if (FileHelper::CreateFile(strfieldpath) == false) {
				return false;
			}
		}

		if (fieldDao.GetField(strfieldpath,fd) == true) {
			return false;		//已经存在,字段名重复
		}
		if (fieldDao.CreateField(strfieldpath, fd, true) == false) {
			return false;
		}
		else {
			LogLogic logic;
			logic.WriteLogs(CString("created field: ") + fd.getFieldName() + CString("on database: ") + dbName + CString(" table: ") + tbName);
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to create FIELD!"));
	}

	return true;
}

bool FieldLogic::getField(const CString dbName, const CString tbName, CFieldEntity & fd)
{
	try {
		return fieldDao.GetField(filelogic.GetFieldFile(dbName,tbName), fd);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get FIELD!"));
	}

	return false;
}

bool FieldLogic::getField(const CString dbName, const CString tbName, CString oldName, CString newName)
{
	try {
		LogLogic logic;
		logic.WriteLogs(CString("Change field name from") + oldName + CString("to") + newName +CString("on database:") + dbName + CString("Table") +tbName);
		return fieldDao.ChangeFieldName(filelogic.GetFieldFile(dbName, tbName), filelogic.GetFieldFile(dbName, _T("Index")), oldName,newName);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get FIELD!"));
	}

	return false;
}

bool FieldLogic::getField(const CString dbName, const CString tbName, CString oldName, int newtype)
{
	try {
		LogLogic logic;
		logic.WriteLogs(CString("Change field type") + oldName + CString("on database:") + dbName + CString("Table") + tbName);
		return fieldDao.ChangeFieldTType(filelogic.GetFieldFile(dbName, tbName), filelogic.GetFieldFile(dbName, _T("Index")), oldName, newtype);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get FIELD!"));
	}
	return false;
}

bool FieldLogic::getField(const CString dbName, const CString tbName, CString oldName)
{
	try {
		LogLogic logic;
		logic.WriteLogs(CString("Deleted field: ") + oldName + CString("on database: ") + dbName + CString(" table: ") + tbName);
		return fieldDao.DeleteField(filelogic.GetFieldFile(dbName, tbName), filelogic.GetFieldFile(dbName, _T("Index")), oldName);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get FIELD!"));
	}
	return false;
}

vector<CFieldEntity> FieldLogic::GetFieldList(const CString dbName, const CString tbName)
{
	vector<CFieldEntity> list;
	list = fieldDao.ReadFieldList(filelogic.GetFieldFile(dbName, tbName));
	return list;
}


