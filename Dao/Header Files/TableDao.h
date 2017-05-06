//表文件（定义，描述）操作类TableDao定义文件
#pragma once

class TableDao
{
public:
	bool CreateTable(const CString filePath, CTablEntity &te);   //创建表：添加表信息到表定义文件
	bool AddField(const CString filePath, CFieldEntity &fe);     //添加字段：添加字段信息到表描述文件
	bool AlterTable(const CString filePath, CTablEntity &te);    //修改表：修改表定义文件
	int GetTables(const CString filePath, TABLEARR &tArr);       //获取表信息：查询表定义文件
	bool GetFields(const CString filePath, CTablEntity &te);     //获取字段信息（即records）：查询表描述文件
};
