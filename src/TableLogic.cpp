#include "stdafx.h"
#include "TableLogic.h"

bool TableLogic::CreateTable(const CString strDBName, CTablEntity &te) {
	try {
		CString StrTableFile = m_fileLogic.GetTableFile(strDBName);
		if (FileHelper::IsVaildFile(StrTableFile) == false) {
			if (FileHelper::CreateFile(StrTableFile) == false) {
				return false;
			}
		}

		vector <CTablEntity> list = getTableList(strDBName);
		for (vector <CTablEntity>::iterator ite = list.begin(); ite != list.end(); ++ite) {
			if (te.getTableName().CompareNoCase(ite->getTableName()) == 0) {
				AfxMessageBox(_T("表名已存在！"), MB_OK);
				return false;
			}
		}

		//设置表描述文件路径
		te.setTableTdfPath(m_fileLogic.GetFieldFile(strDBName, te.getTableName()));
		// 设置记录文件路径
		te.setTableTrdPath(m_fileLogic.GetRecordFile(strDBName, te.getTableName()));

		if (m_dao.Create(StrTableFile, te) == false) {
			return false;
		}
		else {
			LogLogic logic;
			logic.WriteLogs(CString("Create Table:") + te.getTableName() + CString("on database:") + strDBName);
			return true;
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to create table."));
	}
}

//查询表信息
int TableLogic::GetTables(const CString strDBName, TABLEARR &arrTables) {
	int nCount = 0;
	try {
		//获取表描述文件
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);

		//查询表信息
		nCount = m_dao.GetTables(strTableFile, arrTables);

		//从表描述文件中一个接一个读取表结构
		for (int i = 0; i < nCount; i++) {
			CTablEntity* pTable = arrTables.GetAt(i);

		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get table information!"));
	}

	return nCount;
}

//获取该数据库内的所有表描述信息
vector <CTablEntity> TableLogic::getTableList(const CString dbname) {

	return m_dao.ReadTableList(m_fileLogic.GetTableFile(dbname));
}

//修改表名
bool TableLogic::ModifyTable(const CString &dbname, CString &oldTBName, CString &newTBName) {
	CString DBFolderPath = m_fileLogic.GetDBFolder(dbname);
	CString TBFilePath = m_fileLogic.GetTableFile(dbname);
	vector <CTablEntity> TBList = m_dao.ReadTableList(TBFilePath);
	bool bExist = false;
	for (vector <CTablEntity>::iterator ite = TBList.begin(); ite != TBList.end(); ++ite) {
		if (ite->getTableName().CompareNoCase(newTBName) == 0) {   //新的表名与原有表名相同，则修改失败
			bExist = true;
			AfxMessageBox(_T("新的表名已存在!"), MB_OK);
			break;
		}
	}

	if (bExist == true) {
		return false;
	}
	else {
		if (!m_dao.ModifyTBName(TBFilePath, oldTBName, newTBName) || !m_dao.ModifyTBFile(DBFolderPath, oldTBName, newTBName)) {
			return false;
		}
		else {
			LogLogic logic;
			logic.WriteLogs(CString("Alter table set table name from") + oldTBName + CString("to") + newTBName + CString(" on database: ") +dbname);
			return true;
		}
	}
}

//删除表
bool TableLogic::DeleteTable(const CString &dbname, CString tbname) {
	CString TBFilePath = m_fileLogic.GetTableFile(dbname);
	CString DBFolderPath = m_fileLogic.GetDBFolder(dbname);
	if (!m_dao.DeleteTable(TBFilePath, tbname) || !m_dao.DeleteTBFile(DBFolderPath, tbname)) {
		return false;
	}
	else {
		LogLogic logic;
		logic.WriteLogs(CString("deleted a table:") + tbname + CString("on database: ") + dbname);
		return true;
	}
}