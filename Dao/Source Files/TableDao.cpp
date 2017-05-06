//表文件（定义，描述）操作类TableDao实现文件
#include "stdafx.h"
#include "CTableEntity.h"
#include "CFieldEntity.h"
#include "TableDao.h"

//创建表：添加表信息到表定义文件
//输入参数：
// const CString filePath：表定义文件路径
// CTableEntity &te：表（结构）信息
bool TableDao::CreateTable(const CString filePath, CTablEntity &te)
{
	CFile tableFile;
	if (tableFile.Open(filePath, CFile::modeWrite | CFile::shareDenyWrite) == false)
		return false;

	tableFile.SeekToEnd();
	tableFile.Write(&te, sizeof(CTablEntity));

	tableFile.Close();
	return true;

	//异常处理：添加表格信息失败
}

//添加字段：添加字段信息到表描述文件
//输入参数：
// const CString filePath：表描述文件路径
// CFieldEntity &fe：字段信息
bool TableDao::AddField(const CString filePath, CFieldEntity &fe)
{
	CFile fieldFile;
	if (fieldFile.Open(filePath, CFile::modeWrite | CFile::shareDenyWrite) == false)
		return false;

	fieldFile.SeekToEnd();
	fieldFile.Write(&fe, sizeof(CFieldEntity));

	fieldFile.Close();
	return true;

	//异常处理：添加字段信息失败
}

//修改表：修改表定义文件
//输入参数：
// const CString filePath：表定义文件路径
// CTablEntity &te：表（结构）信息
bool TableDao::AlterTable(const CString filePath, CTablEntity &te)
{
	CFile tableFile;
	if (tableFile.Open(filePath, CFile::modeReadWrite | CFile::shareDenyWrite) == false)
		return false;

	tableFile.SeekToBegin();
	long offset = tableFile.GetPosition();

	bool flag = false;
	CTablEntity ct;
	CString tableName = te.getTableName();
	CString strName;
	while (tableFile.Read(&ct, sizeof(CTablEntity)) > 0)
	{
		strName = ct.getTableName();
		if (tableName.CompareNoCase(strName) == 0)
		{
			tableFile.Seek(offset, CFile::begin); //文件指针指向上一个记录（结束）的位置
			tableFile.Write(&te, sizeof(CTablEntity));
			flag = true;
			break;
		}
		offset = tableFile.GetPosition();
	}

	tableFile.Close();	
	return flag;

	//异常处理：修改表格失败
}

//获取表信息：查询表定义文件
//输入参数：
// const CString filePath：表定义文件路径
// TABLEARR &tArr：用于存储查询结果的数组
int TableDao::GetTables(const CString filePath, TABLEARR &tArr)
{
	CFile tableFile;
	if (tableFile.Open(filePath, CFile::modeRead | CFile::shareDenyNone) == false)
		return false;
	tableFile.SeekToBegin();
	
	int nCount = 0;
	CTablEntity cte;

	while (tableFile.Read(&cte, sizeof(CTablEntity)) > 0)
	{
		CTablEntity* table = new CTablEntity();
		table->copyTable(cte);
		tArr.Add(table);
		nCount++;
	}

	tableFile.Close();
	return nCount;

	//异常处理：查询表格失败
}

//获取字段信息：查询表描述文件
//输入参数：
// const CString filePath：表描述文件路径
// CTablEntity &te：用于存储查询结果的CTableEntity对象
bool TableDao::GetFields(const CString filePath, CTablEntity &te)
{
	CFile fieldFile;
	if (fieldFile.Open(filePath, CFile::modeRead | CFile::shareDenyNone) == false)
		return false;
	fieldFile.SeekToBegin();

	CFieldEntity cfe;

	while (fieldFile.Read(&cfe, sizeof(CFieldEntity)) > 0)
	{
		CFieldEntity* field = new CFieldEntity(cfe);
		te.addField(*field);//
	}

	fieldFile.Close();
	return true;

	//异常处理：查询字段失败
}
