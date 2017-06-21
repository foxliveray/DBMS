// DBView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBView.h"
#include "afxdialogex.h"
#include"LsiderView.h"

// DBView �Ի���

IMPLEMENT_DYNAMIC(DBView, CDialogEx)

DBView::DBView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, dbName(_T(""))
{

}

DBView::~DBView()
{
}

void DBView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dbName);
}


BEGIN_MESSAGE_MAP(DBView, CDialogEx)
	ON_BN_CLICKED(IDOK, &DBView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DBView::OnBnClickedCancel)
END_MESSAGE_MAP()


// DBView ��Ϣ�������


void DBView::OnBnClickedOk()
{	
	UpdateData(TRUE);
	CDBEntity newdb;
	newdb.setDBName(dbName);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void DBView::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}



