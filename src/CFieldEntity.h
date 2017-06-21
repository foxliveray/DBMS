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
	CString m_strName;//�ֶ���
	int m_nType;//�ֶ�����
	int m_nParam;//�ֶ����ͳ���
	int m_nIntegrities;//�ֶ�������Լ������
	SYSTEMTIME m_tMTime;//���һ���޸�ʱ��
public:
	enum DataType
	{
		DT_NONE = -1,
		DT_INTEGER = 0,// Integer: 4byte  corresponding: int
		DT_VARCHAR = 1,// String: 256byte, corresponding: char[256]
		DT_BOOL = 2,// Boolean: 1byte, corresponding��bool
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