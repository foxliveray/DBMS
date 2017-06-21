// DeleteDatabaseView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "DeleteDatabaseView.h"
#include "afxdialogex.h"
#include "CDBEntity.h"

// DeleteDatabaseView 对话框

IMPLEMENT_DYNAMIC(DeleteDatabaseView, CDialogEx)

DeleteDatabaseView::DeleteDatabaseView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DELETEDATABASEVIEW, pParent)
	, dbname(_T(""))
{

}

DeleteDatabaseView::~DeleteDatabaseView()
{
}

void DeleteDatabaseView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dbname);
}


BEGIN_MESSAGE_MAP(DeleteDatabaseView, CDialogEx)
	ON_BN_CLICKED(IDOK, &DeleteDatabaseView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DeleteDatabaseView::OnBnClickedCancel)
END_MESSAGE_MAP()


// DeleteDatabaseView 消息处理程序


void DeleteDatabaseView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDBEntity DeleteDB;
	DeleteDB.setDBName(dbname);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void DeleteDatabaseView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
