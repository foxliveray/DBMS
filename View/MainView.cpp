// MainView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "MainView.h"


// MainView

IMPLEMENT_DYNCREATE(MainView, CView)

MainView::MainView()
{

}

MainView::~MainView()
{
}

BEGIN_MESSAGE_MAP(MainView, CView)
END_MESSAGE_MAP()


// MainView 绘图

void MainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// MainView 诊断

#ifdef _DEBUG
void MainView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MainView 消息处理程序
