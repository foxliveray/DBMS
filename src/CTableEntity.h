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
	CString m_strName;//����
	int m_nRecordNum;//���¼��
	CString m_strTdfPath;//�����ֶ���Ϣ�ļ���ַ
	CString m_strTrdPath;//��¼�ļ�
	CString m_strTicPath;//�������ļ�
	CString m_strTidPath;//�����ļ�
	SYSTEMTIME m_tCrTime;//�������ʱ��
	SYSTEMTIME m_tMTime;//���һ�θ���ʱ��
	FIELDARRAY m_arrFields;	//�ֶ�����
public:
	//���졢��������
	CTablEntity();
	CTablEntity(TableBlock &tb);
	CTablEntity(CString name);
	CTablEntity(const CTablEntity &c);		//�������캯��
	CTablEntity& operator=(const CTablEntity &d);		//��ֵ���캯��
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

	//��ȡ������Ϣ
	TableBlock GetBlock();
	//���ñ�����Ϣ
	void SetBlock(TableBlock tb);
};

typedef CTypedPtrArray<CPtrArray, CTablEntity*> TABLEARR;