#pragma once
#include"CFieldEntity.h"
#include "AppException.h"
class FieldDao
{

public:
	FieldDao(void);
	~FieldDao();
	//�����ֶ�
	bool CreateField(const CString strFilepath, CFieldEntity &db, bool bAppend);
	//���ļ��ж�ȡ�ֶ���Ϣ
	bool GetField(const CString strFilepath, CFieldEntity &db);
	//��ȡ�����ֶ�������Ϣ
	vector<CFieldEntity> ReadFieldList(CString strFilepath);
	bool ChangeFieldName(const CString strFilepath,const CString strIndexPaath, CString oldNamme, CString newName);
	bool ChangeFieldTType(const CString strFilepath, const CString strIndexPaath, CString oldNamme,int newType);
	bool DeleteField(const CString strFilepath, const CString strIndexPath, CString oldNamme);

};
