#include "stdafx.h"
#include "DBLogic.h"


DBLogic::DBLogic()
{
}


DBLogic::~DBLogic()
{
}

//创建数据库
bool DBLogic::CreateDatabase(CDBEntity &db) {
	try {
		//判断该文件是否存在，如果不存在，就会创建一个新文件
		CString strDBFile = m_logic.GetDBFile();
		if (FileHelper::IsVaildFile(strDBFile) == false) {
			if (FileHelper::CreateFile(strDBFile) == false) {
				return false;
			}
		}

		if (m_dao.GetDatabase(strDBFile, db) == true) {
			AfxMessageBox(_T("数据库名已经存在！"), MB_OK);
			return false;		//已经存在，所以不需要创建新的数据库
		}
		if (db.getDBName().GetLength() == 0) {
			AfxMessageBox(_T("数据库名不能为空！"), MB_OK);
			return false;
		}
		//创建数据库
		CString  strDBFolder = m_logic.GetDBFolder(db.getDBName());
		db.setDBFilePath(strDBFolder);
		if (m_dao.Create(strDBFile, db, true) == false) {
			return false;
		}
		else {
			LogLogic logic;
			CString dbname = db.getDBName();
			logic.WriteLogs(CString("Create Database:") + dbname);
			return true;
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to create database!"));
	}

	return true;
}

//查询数据库
bool DBLogic::GetDatabase(CDBEntity &db) {
	try {
		return m_dao.GetDatabase(m_logic.GetDBFolder(db.getDBName()), db);
		LogLogic logic;
		CString dbname = db.getDBName();
		logic.WriteLogs(CString("Get Database	infomation:") + dbname);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get database!"));
	}

	return false;
}

//得到所有数据库块的信息
vector<CDBEntity> DBLogic::GetDatabaseList() {
	vector<CDBEntity> list;
	list = m_dao.ReadDBList(m_logic.GetDBFile());
	return list;
}

//删除数据库信息及其子信息
bool DBLogic::DeleteDatabase(CString &dbname) {
	CString DBPath = m_logic.GetDBFile();
	if (!m_dao.DeleteDB(DBPath, dbname) || !m_dao.DeleteDBFile(dbname)) {
		return false;
	}
	else {
		LogLogic logic;
		logic.WriteLogs(CString("deleted database:") + dbname);
		return true;
	}
}

bool DBLogic::ModifyDatabase(CString &oldDBName, CString &newDBName) {
	vector <CDBEntity> DBlist = m_dao.ReadDBList(m_logic.GetDBFile());
	bool bExist = false;
	for (vector <CDBEntity>::iterator ite = DBlist.begin(); ite != DBlist.end(); ++ite) {
		if (ite->getDBName().CompareNoCase(newDBName)==0) {	//修改成的新数据库名已存在
			bExist = true;
			AfxMessageBox(_T("新数据库名已存在!"), MB_OK);
			break;
		}
	}

	if (bExist == true) {
		return false;
	}
	else {
		if (!m_dao.ModifyDB(m_logic.GetDBFile(), oldDBName, newDBName) || !m_dao.ModifyDBPath(oldDBName, newDBName)) {
			return false;
		}
		else {
			LogLogic logic;
			logic.WriteLogs(CString("modified database name from") + oldDBName + CString("to") + newDBName);
			return true;
		}
	}
}
bool DBLogic::BackupDatabase(CString &dbName, CString &destPath)
{
	//写日志
	if (m_dao.BackupDB(dbName, m_logic.GetDBFolder(dbName), destPath) == TRUE) {
		LogLogic logic;
		logic.WriteLogs(CString("Backup database:") + dbName);
		return TRUE;
	}
	return FALSE;
}
