// TBView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "TBView.h"
#include "afxdialogex.h"


// TBView 对话框

IMPLEMENT_DYNAMIC(TBView, CDialogEx)

TBView::TBView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, tbName(_T(""))
{

}

TBView::~TBView()
{
}

void TBView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, tbName);
}


BEGIN_MESSAGE_MAP(TBView, CDialogEx)
	ON_BN_CLICKED(IDOK, &TBView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TBView::OnBnClickedCancel)
END_MESSAGE_MAP()


// TBView 消息处理程序


void TBView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (tbName == L"")
	{
		MessageBox(L"表名不能为空！", L"提示", MB_OK);
	}
	else {
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}

}


void TBView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CDialogEx::OnCancel();
}
