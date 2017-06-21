// DBMSDoc.cpp : 实现文件
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


// DBMSDoc 诊断

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
// DBMSDoc 序列化

void DBMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}
#endif


// DBMSDoc 命令

//获取异常信息
CString DBMSDoc::GetError() {

		//	Remove white space characters
	m_strError.TrimLeft();
	m_strError.TrimRight();

	return m_strError;

}

//设置异常信息
void DBMSDoc::SetError(CString strError) {
	m_strError = strError;
}
