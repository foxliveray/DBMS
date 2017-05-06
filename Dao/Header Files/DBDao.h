//数据库文件操作类DBDao定义文件
#pragma once

class DBDao
{
public:
	bool CreateDB(const CString filePath, const CDBEntity db, bool bAppend = true);  //创建一个数据库
	bool GetDatabase(const CString filePath, CDBEntity &db);                         //获取一个数据库的信息
};
