#pragma once
#include"CFieldEntity.h"
#include "AppException.h"
class FieldDao
{

public:
	FieldDao(void);
	~FieldDao();
	//创建字段
	bool CreateField(const CString strFilepath, CFieldEntity &db, bool bAppend);
	//从文件中读取字段信息
	bool GetField(const CString strFilepath, CFieldEntity &db);
	//读取所有字段描述信息
	vector<CFieldEntity> ReadFieldList(CString strFilepath);
	bool ChangeFieldName(const CString strFilepath,const CString strIndexPaath, CString oldNamme, CString newName);
	bool ChangeFieldTType(const CString strFilepath, const CString strIndexPaath, CString oldNamme,int newType);
	bool DeleteField(const CString strFilepath, const CString strIndexPath, CString oldNamme);

};
