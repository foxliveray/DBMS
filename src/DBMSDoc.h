#pragma once

#include "CDBEntity.h"
#include "DBView.h"
#include "DBLogic.h"
#include "AppException.h"
// DBMSDoc �ĵ�

class DBMSDoc : public CDocument
{ 
	DECLARE_DYNCREATE(DBMSDoc)

public:
	DBMSDoc();
	virtual ~DBMSDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

private:
	CString m_strError;		//�����쳣��Ϣ
	//CDBEntity m_DBEntity;		//����һ�����ݿ�ʵ�����

public:
	CString GetError();					//��ȡ�쳣��Ϣ
	void SetError(CString strError);	//�����쳣��Ϣ
	DECLARE_MESSAGE_MAP()
};
