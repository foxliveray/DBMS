
//统一定义数据类型：数据库信息块，表信息块，字段信息块
#pragma once
#include <afx.h>
#pragma  once

typedef int INTEGER;			// Integer
typedef bool BOOLE;				// Boolean type
typedef double DOUBLE;			// Floating-point number
typedef char VARCHAR[256];		// String type
typedef SYSTEMTIME DATETIME;	// Date time type

struct DatabaseBlock {
	BOOLE type;			// Database type：true is system database，false is custom database.
	VARCHAR name;		// Database name
	VARCHAR filepath;	// Database file path
	DATETIME crtime;	// Creation time
};

// Table information structure
struct TableBlock
{
	VARCHAR name;		// Name
	INTEGER record_num;	// Record number
	INTEGER field_num;	// Field number
	VARCHAR tdf;		// Path of the table definition file
	VARCHAR trd;		// Path of the record file
	VARCHAR tic;
	VARCHAR tid;
	DATETIME crtime;	// Table creation time
	DATETIME mtime;		// Last modification time
};

// The definition of field block
struct FieldBlock
{
	VARCHAR name;		// Name
	INTEGER type;		// Type
	INTEGER param;		// Parameter
	DATETIME mtime;		// Last modification time
	INTEGER integrities;// Integrity constraints information
};

struct IntegrityBlock
{
	VARCHAR name;
	INTEGER isNotNull;
	INTEGER isPrimary;
	INTEGER isDefault;
	VARCHAR defaultValue;
};
struct LoginBlock {
	VARCHAR name;
	VARCHAR password;
};