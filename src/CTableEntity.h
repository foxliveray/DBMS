#pragma once
#include<cstring>
#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
#include"CFieldEntity.h"
#include"DataStructure.h"
#include"global.h"
#include "CFieldEntity.h"
#include "CharHelper.h"
class CTablEntity : public CObject
{
private:
	CString m_strName;//表名
	int m_nRecordNum;//表记录数
	CString m_strTdfPath;//保存字段信息文件地址
	CString m_strTrdPath;//记录文件
	CString m_strTicPath;//完整性文件
	CString m_strTidPath;//索引文件
	SYSTEMTIME m_tCrTime;//创建表的时间
	SYSTEMTIME m_tMTime;//最后一次更改时间
	FIELDARRAY m_arrFields;	//字段数组
public:
	//构造、析构函数
	CTablEntity();
	CTablEntity(TableBlock &tb);
	CTablEntity(CString name);
	CTablEntity(const CTablEntity &c);		//拷贝构造函数
	CTablEntity& operator=(const CTablEntity &d);		//赋值构造函数
	~CTablEntity();

	void addField(CFieldEntity &fe);
	void deleteField(CFieldEntity &fe);
	CFieldEntity* getField(int nIndex);
	CString getTableName();
	void setTableName(CString strName);
	int getFieldNum();
	int getRecordNum();
	void addNewRecord();
	void deleteRecord();
	SYSTEMTIME getTCRTime();
	void setTCRTime(SYSTEMTIME t);
	SYSTEMTIME getTMTime();
	void setTMTime(SYSTEMTIME t);


	CString getTableTdfPath();
	void setTableTdfPath(CString filePath);
	CString getTableTrdPath();
	void setTableTrdPath(CString filePath);
	CString getTableTicPath();
	void setTableTicPath(CString filePath);
	CString getTableTidPath();
	void setTableTidPath(CString filePath);

	//获取表块的信息
	TableBlock GetBlock();
	//设置表块的信息
	void SetBlock(TableBlock tb);
};

typedef CTypedPtrArray<CPtrArray, CTablEntity*> TABLEARR;