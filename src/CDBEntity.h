#pragma once
#include<cstring>
#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
#include"DataStructure.h"
#include"global.h"
#include "CharHelper.h"
class CDBEntity : public CObject
{
private:
	CString m_strName;//���ݿ���
	bool m_bType;//���ݿ�����
	CString m_strFilepath;//���·��
	SYSTEMTIME m_tCtTime;//����ʱ��
public:
	//���졢��������
	CDBEntity(DatabaseBlock &db);
	CDBEntity(const CString strName);
	CDBEntity(void);
	~CDBEntity(void);
	CDBEntity(const CDBEntity &c);	//�������캯��
	CDBEntity& operator =(const CDBEntity &d);		//��ֵ���캯��


	CString getDBName();
	void setDBName(CString strName);
	bool getDBType();
	void setDBType(bool type);
	CString getDBFilePath();
	void setDBFilePath(CString filePath);
	void setSystemTime(SYSTEMTIME t);
	SYSTEMTIME getSystenTime();

	//��ȡ���ݿ�����Ϣ
	DatabaseBlock GetBlock(void);
	//�������ݿ����Ϣ
	void SetBlock(DatabaseBlock db);
};