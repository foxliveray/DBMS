// AlterDatabaseView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "AlterDatabaseView.h"
#include "afxdialogex.h"
#include "CDBEntity.h"


// AlterDatabaseView 对话框

IMPLEMENT_DYNAMIC(AlterDatabaseView, CDialogEx)

AlterDatabaseView::AlterDatabaseView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALTERDATABASEVIEW, pParent)
	, oldDBName(_T("")), newDBName(_T(""))
{

}

AlterDatabaseView::~AlterDatabaseView()
{
}

void AlterDatabaseView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, oldDBName);
	DDX_Text(pDX, IDC_EDIT2, newDBName);
}


BEGIN_MESSAGE_MAP(AlterDatabaseView, CDialogEx)
	ON_BN_CLICKED(IDOK, &AlterDatabaseView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AlterDatabaseView::OnBnClickedCancel)
END_MESSAGE_MAP()


// AlterDatabaseView 消息处理程序


void AlterDatabaseView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDBEntity oldDB;
	oldDB.setDBName(oldDBName);
	CDBEntity newDB;
	newDB.setDBName(newDBName);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void AlterDatabaseView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
