//ͳһ�����������ͣ����ݿ���Ϣ�飬����Ϣ�飬�ֶ���Ϣ��
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