// DBMSDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBMSDoc.h"


// DBMSDoc

IMPLEMENT_DYNCREATE(DBMSDoc, CDocument)



BOOL DBMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
		
	return TRUE;
}

DBMSDoc::DBMSDoc()
{
	m_strError = _T("");
}

DBMSDoc::~DBMSDoc()
{
}


BEGIN_MESSAGE_MAP(DBMSDoc, CDocument)
END_MESSAGE_MAP()


// DBMSDoc ���

#ifdef _DEBUG
void DBMSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void DBMSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// DBMSDoc ���л�

void DBMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}
#endif


// DBMSDoc ����

//��ȡ�쳣��Ϣ
CString DBMSDoc::GetError() {

		//	Remove white space characters
	m_strError.TrimLeft();
	m_strError.TrimRight();

	return m_strError;

}

//�����쳣��Ϣ
void DBMSDoc::SetError(CString strError) {
	m_strError = strError;
}
