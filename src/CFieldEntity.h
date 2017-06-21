#pragma once
#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
#include<afxtempl.h>
#include"DataStructure.h"
#include"global.h"
class CFieldEntity : public CObject
{
private:
	CString m_strName;//字段名
	int m_nType;//字段类型
	int m_nParam;//字段类型长度
	int m_nIntegrities;//字段完整性约束个数
	SYSTEMTIME m_tMTime;//最后一次修改时间
public:
	enum DataType
	{
		DT_NONE = -1,
		DT_INTEGER = 0,// Integer: 4byte  corresponding: int
		DT_VARCHAR = 1,// String: 256byte, corresponding: char[256]
		DT_BOOL = 2,// Boolean: 1byte, corresponding：bool
		DT_DOUBLE = 3,// Floating-point number: 2byte,  corresponding: double
		DT_DATETIME = 4// Data time: 16byte, corresponding: SYSTEMTIME type
	};
	CFieldEntity(const CFieldEntity & fieldEntity);
	CFieldEntity();
	CFieldEntity(CString, int, int, int);
	~CFieldEntity();

	CString getFieldName();
	void setFieldName(CString strName);
	CString getFieldType();
	void setFieldType(int type);
	void setParam(int num);
	int GetParam();
	void setIntegrity(int num);
	int getFieldParamNum();
	int getFieldIntegrity();
	SYSTEMTIME getTMTime();
	void setTMTime(SYSTEMTIME t);

	void SetBlock(FieldBlock fb);

	FieldBlock GetBlock();


};
typedef CTypedPtrArray<CPtrArray, CFieldEntity*> FIELDARRAY;