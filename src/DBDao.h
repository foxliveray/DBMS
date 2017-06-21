#pragma once
#include "CDBEntity.h"
#include "AppException.h"
#include "FileLogic.h"
#include "FileHelper.h"
class DBDao
{

public :
	//�������ݿ⣬�����ݿ���Ϣ���浽�ļ���
	bool Create(const CString strFilepath, CDBEntity &db, bool bAppend);
	//���ļ��ж�ȡ���ݿ���Ϣ
	bool GetDatabase(const CString strFilepath, CDBEntity &db);
	//��ȡ�������ݿ�������Ϣ
	vector<CDBEntity> ReadDBList(CString strFilepath);
	//ɾ��star.db�ļ��й��ڸ����ݿ�Ŀ���Ϣ
	bool DeleteDB(const CString strFilepath, CString &dbname);
	//�������ݿ���ɾ�����ڸ����ݿ��ȫ���ļ�
	bool DeleteDBFile(CString &dbName);
	//�޸����ݿ���
	bool ModifyDB(CString strFilePath, CString &oldDBName, CString &newDBName);
	//�޸����ݿ�·�������������ļ���
	bool ModifyDBPath(CString &oldDBName, CString &newDBName);
	bool BackupDB(CString & dbName, CString & filepath, CString & destPath);
};

