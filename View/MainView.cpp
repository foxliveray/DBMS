// MainView.cpp : ʵ���ļ�
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


// MainView ��ͼ

void MainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ���ӻ��ƴ���
}


// MainView ���

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


// MainView ��Ϣ�������
