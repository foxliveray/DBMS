#pragma once
#include "CTableEntity.h"
#include "AppException.h"
#include "global.h"
#include "FileHelper.h"
#include "CFieldEntity.h"

class TableDao
{
public:
	//创建表
	bool Create(const CString strFilePath, CTablEntity &te);
	//获取表信息
	int GetTables(const CString strFilepath, TABLEARR &arr);
	//从文件获取所有表描述信息
	vector <CTablEntity> ReadTableList(CString &TbFilePath);
	//修改表名
	bool ModifyTBName(CString strFilePath, CString &oldTBName, CString &newTBName);
	//修改表的trd,tdf文件名
	bool ModifyTBFile(CString dbFolderPath,CString &oldTBName, CString &newTBName);
	//删除表
	bool DeleteTable(CString strFilePath, CString &tbname);
	//删除该表的相关文件
	bool DeleteTBFile(CString dbFolderPath, CString &tbname);
	//修改表：修改表定义文件
	bool AlterTable(const CString filePath, CTablEntity &te);
	bool ResumeFieldsIntable(const CString filePath, CTablEntity &te);
	bool AddFieldNum(CString strFilePath, CString &oldTBName, CFieldEntity &fe);
	bool MinusFieldNum(CString strFilePath, CString &oldTBName, CFieldEntity &fe);
};

