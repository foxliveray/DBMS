#include "stdafx.h"
#include "DBDao.h"


//创建数据库，将数据库信息保存到文件中
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
		
		file.SeekToEnd();		//跳转至文件的开头进行写入
		file.Write(&db.GetBlock(), sizeof(DatabaseBlock));	//写入数据库块的信息
		file.Close();

		return true;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to create the database file!"));
	}

	return false;
}

//从文件中读取数据库信息
bool DBDao::GetDatabase(const CString strFilepath, CDBEntity &db) {
	try {
		//首先匹配文件名
		CString strDBName = db.getDBName();
		if (strDBName.GetLength() == 0) {
			return false;
		}
		//以只读的方式打开文件
		CFile file;
		if (file.Open(strFilepath,CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
			return false;
		}

		//读取数据库信息
		bool  Exist = false;
		DatabaseBlock sdb;

		file.SeekToBegin();
		while (file.Read(&sdb, sizeof(DatabaseBlock)) > 0) {
			CString strName = CharHelper::ToString(sdb.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strDBName) == 0) {//数据库名完全一致
				db.SetBlock(sdb);
				Exist = true;
				break;
			}
		}
		file.Close();
		return Exist;
	}
	catch (CException *e) {
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to read the database file!"));
	}
}

//读取所有数据库描述信息
vector<CDBEntity> DBDao::ReadDBList(CString strFilepath) {
	vector <CDBEntity> res;
	try {
		CFile file;
		file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone);	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
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

//删除star.db文件中关于该数据库的块信息
bool DBDao::DeleteDB(const CString strFilepath, CString &dbname) {
	vector <CDBEntity> res;
	if (dbname.GetLength() == 0) {
		return false;
	}
	res = ReadDBList(strFilepath);
	for (vector<CDBEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CDBEntity db = ite->GetBlock();
		CString strDBName = db.getDBName();
		if (strDBName.CompareNoCase(dbname)==0) {	//如果数据库名一致，则从vector数组中删除该数据库块的信息
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

//根据数据库名删除关于该数据库的全部文件
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

//修改数据库名
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
		if (strDBName.CompareNoCase(oldDBName) == 0) {	//如果当前查找的数据库名与老数据库名一致，则进行修改
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

	//获取表描述文件的路径来修改.tb文件名
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