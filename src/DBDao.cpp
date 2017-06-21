#include "stdafx.h"
#include "DBDao.h"


//�������ݿ⣬�����ݿ���Ϣ���浽�ļ���
bool DBDao::Create(const CString strFilepath, CDBEntity &db, bool bAppend) {
	try {
		CFile file;
		if (bAppend == true) {
			if (file.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
				return false;
			}
		}
		else {
			if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
				return false;
			}
		}
		
		file.SeekToEnd();		//��ת���ļ��Ŀ�ͷ����д��
		file.Write(&db.GetBlock(), sizeof(DatabaseBlock));	//д�����ݿ�����Ϣ
		file.Close();

		return true;
	}
	catch (CException *e) {
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to create the database file!"));
	}

	return false;
}

//���ļ��ж�ȡ���ݿ���Ϣ
bool DBDao::GetDatabase(const CString strFilepath, CDBEntity &db) {
	try {
		//����ƥ���ļ���
		CString strDBName = db.getDBName();
		if (strDBName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath,CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		bool  Exist = false;
		DatabaseBlock sdb;

		file.SeekToBegin();
		while (file.Read(&sdb, sizeof(DatabaseBlock)) > 0) {
			CString strName = CharHelper::ToString(sdb.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strDBName) == 0) {//���ݿ�����ȫһ��
				db.SetBlock(sdb);
				Exist = true;
				break;
			}
		}
		file.Close();
		return Exist;
	}
	catch (CException *e) {
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to read the database file!"));
	}
}

//��ȡ�������ݿ�������Ϣ
vector<CDBEntity> DBDao::ReadDBList(CString strFilepath) {
	vector <CDBEntity> res;
	try {
		CFile file;
		file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone);	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
		DatabaseBlock sdb;

		file.SeekToBegin();
		while (file.Read(&sdb, sizeof(DatabaseBlock)) > 0) {
			CDBEntity db;
			db.SetBlock(sdb);
			res.push_back(db);
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get all database!"));
	}

	return res;
}

//ɾ��star.db�ļ��й��ڸ����ݿ�Ŀ���Ϣ
bool DBDao::DeleteDB(const CString strFilepath, CString &dbname) {
	vector <CDBEntity> res;
	if (dbname.GetLength() == 0) {
		return false;
	}
	res = ReadDBList(strFilepath);
	for (vector<CDBEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CDBEntity db = ite->GetBlock();
		CString strDBName = db.getDBName();
		if (strDBName.CompareNoCase(dbname)==0) {	//������ݿ���һ�£����vector������ɾ�������ݿ�����Ϣ
			res.erase(ite);
			break;
		}
	}

	try {
		CFile file;
		if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		for (vector<CDBEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
			CDBEntity db = ite->GetBlock();
			file.Write(&db.GetBlock(), sizeof(DatabaseBlock));
			file.SeekToEnd();
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to delete the database!"));
	}

	return true;
}

//�������ݿ���ɾ�����ڸ����ݿ��ȫ���ļ�
bool DBDao::DeleteDBFile(CString &dbName) {
	FileLogic m_logic;
	CString dbFilePath = m_logic.GetDBFolder(dbName);
	FileHelper f;
	if (!f.DeleteFolder(dbFilePath)) {
		return false;
	}
	else {
		return true;
	}
}

//�޸����ݿ���
bool DBDao::ModifyDB(CString strFilePath, CString &oldDBName, CString &newDBName) {
	vector <CDBEntity> res;
	FileLogic m_logic;
	if (oldDBName.GetLength() == 0 || newDBName.GetLength() == 0) {
		return false;
	}
	res = ReadDBList(strFilePath);
	for (vector<CDBEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CDBEntity db = ite->GetBlock();
		CString strDBName = db.getDBName();
		if (strDBName.CompareNoCase(oldDBName) == 0) {	//�����ǰ���ҵ����ݿ����������ݿ���һ�£�������޸�
			ite->setDBName(newDBName);
			CString  strDBFolder = m_logic.GetDBFolder(ite->getDBName());
			ite->setDBFilePath(strDBFolder);
			break;
		}
	}

	try {
		CFile file;
		if (file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		for (vector<CDBEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
			CDBEntity db = ite->GetBlock();
			file.Write(&db.GetBlock(), sizeof(DatabaseBlock));
			file.SeekToEnd();
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to modify the database!"));
	}

	return true;
}

bool DBDao::ModifyDBPath(CString &oldDBName, CString &newDBName) {
	FileLogic m_logic;
	CString oldDBPath = m_logic.GetDBFolder(oldDBName);
	int pos = oldDBPath.ReverseFind('\\');
	CString newDBPath = oldDBPath.Left(pos + 1);
	newDBPath = newDBPath + newDBName;

	//��ȡ�������ļ���·�����޸�.tb�ļ���
	CString oldTBFilePath = m_logic.GetTableFile(oldDBName);
	CString append = _T("");
	append.Format(_T("\\%s.tb"), newDBName);
	CString newTBFilePath = oldDBPath + append;
	FileHelper f;
	if (!f.ModifyFileName(oldTBFilePath, newTBFilePath) || !f.ModifyFolderName(oldDBPath, newDBPath)) {
		return false;
	}
	else {
		return true;
	}
}
bool DBDao::BackupDB(CString &dbName, CString &filepath, CString &destPath)
{
	FileHelper helper;
	helper.CopyDirectory(filepath, destPath);
	CDBEntity *db = new CDBEntity();
	db->setDBName(dbName);
	db->setDBFilePath(destPath + L"/db.back");
	if (helper.IsVaildFile(destPath + L"/db.back") == FALSE) {
		helper.CreateFileW(destPath + L"/db.back");
	}
	return Create(destPath + L"/db.back", *db, TRUE);
}