#pragma once
#include "CTableEntity.h"
#include "AppException.h"
#include "global.h"
#include "FileHelper.h"
#include "CFieldEntity.h"

class TableDao
{
public:
	//������
	bool Create(const CString strFilePath, CTablEntity &te);
	//��ȡ����Ϣ
	int GetTables(const CString strFilepath, TABLEARR &arr);
	//���ļ���ȡ���б�������Ϣ
	vector <CTablEntity> ReadTableList(CString &TbFilePath);
	//�޸ı���
	bool ModifyTBName(CString strFilePath, CString &oldTBName, CString &newTBName);
	//�޸ı��trd,tdf�ļ���
	bool ModifyTBFile(CString dbFolderPath,CString &oldTBName, CString &newTBName);
	//ɾ����
	bool DeleteTable(CString strFilePath, CString &tbname);
	//ɾ���ñ������ļ�
	bool DeleteTBFile(CString dbFolderPath, CString &tbname);
	//�޸ı��޸ı����ļ�
	bool AlterTable(const CString filePath, CTablEntity &te);
	bool ResumeFieldsIntable(const CString filePath, CTablEntity &te);
	bool AddFieldNum(CString strFilePath, CString &oldTBName, CFieldEntity &fe);
	bool MinusFieldNum(CString strFilePath, CString &oldTBName, CFieldEntity &fe);
};

