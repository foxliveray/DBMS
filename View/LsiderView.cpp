// LsiderView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "LsiderView.h"


// LsiderView

IMPLEMENT_DYNCREATE(LsiderView, CTreeView)

LsiderView::LsiderView()
{

}

LsiderView::~LsiderView()
{
}

BEGIN_MESSAGE_MAP(LsiderView, CTreeView)
END_MESSAGE_MAP()


// LsiderView 诊断

#ifdef _DEBUG
void LsiderView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void LsiderView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// LsiderView 消息处理程序
