#include "stdafx.h"
#include "DBLogic.h"


DBLogic::DBLogic()
{
}


DBLogic::~DBLogic()
{
}

//�������ݿ�
bool DBLogic::CreateDatabase(CDBEntity &db) {
	try {
		//�жϸ��ļ��Ƿ���ڣ���������ڣ��ͻᴴ��һ�����ļ�
		CString strDBFile = m_logic.GetDBFile();
		if (FileHelper::IsVaildFile(strDBFile) == false) {
			if (FileHelper::CreateFile(strDBFile) == false) {
				return false;
			}
		}

		if (m_dao.GetDatabase(strDBFile, db) == true) {
			AfxMessageBox(_T("���ݿ����Ѿ����ڣ�"), MB_OK);
			return false;		//�Ѿ����ڣ����Բ���Ҫ�����µ����ݿ�
		}
		if (db.getDBName().GetLength() == 0) {
			AfxMessageBox(_T("���ݿ�������Ϊ�գ�"), MB_OK);
			return false;
		}
		//�������ݿ�
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

//��ѯ���ݿ�
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

//�õ��������ݿ�����Ϣ
vector<CDBEntity> DBLogic::GetDatabaseList() {
	vector<CDBEntity> list;
	list = m_dao.ReadDBList(m_logic.GetDBFile());
	return list;
}

//ɾ�����ݿ���Ϣ��������Ϣ
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
		if (ite->getDBName().CompareNoCase(newDBName)==0) {	//�޸ĳɵ������ݿ����Ѵ���
			bExist = true;
			AfxMessageBox(_T("�����ݿ����Ѵ���!"), MB_OK);
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
	//д��־
	if (m_dao.BackupDB(dbName, m_logic.GetDBFolder(dbName), destPath) == TRUE) {
		LogLogic logic;
		logic.WriteLogs(CString("Backup database:") + dbName);
		return TRUE;
	}
	return FALSE;
}
