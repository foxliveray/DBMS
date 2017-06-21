#pragma once
#include "CTableEntity.h"
#include "TableDao.h"
#include "FileLogic.h"
#include "FileHelper.h"
#include "LogLogic.h"
class TableLogic
{
public:
	//����һ����
	bool CreateTable(const CString strDBName, CTablEntity &te);
	//��ѯ����Ϣ
	int GetTables(const CString strDBName, TABLEARR &arrTables);
	//��ȡ�����ݿ��ڵ����б�������Ϣ
	vector <CTablEntity> getTableList(const CString dbname);
	//�޸ı���
	bool ModifyTable(const CString &dbname, CString &oldTBName, CString &newTBName);
	//ɾ����
	bool DeleteTable(const CString &dbname, CString tbname);
private:
	TableDao m_dao;
	FileLogic m_fileLogic;	
};

