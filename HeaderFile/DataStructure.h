//统一定义数据类型：数据库信息块，表信息块，字段信息块
#pragma once
#include <afx.h>

struct DatabaseBlock
{
	bool type;
	char* name;
	char* filepath;
	SYSTEMTIME crtime;
};

struct TableBlock
{
	char* name;
	int record_num;
	int field_num;
	char* tdf;
	char* trd;
	SYSTEMTIME crtime;
	SYSTEMTIME mtime;
};

struct FieldBlock
{
	char* name;
	int type;
	int param;
	SYSTEMTIME mtime;
	int integrities;
};