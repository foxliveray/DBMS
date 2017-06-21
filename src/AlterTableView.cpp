// AlterTableView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "AlterTableView.h"
#include "afxdialogex.h"
#include "CTableEntity.h"
#include "CDBEntity.h"

// AlterTableView �Ի���

IMPLEMENT_DYNAMIC(AlterTableView, CDialogEx)

AlterTableView::AlterTableView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALTERTABLEVIEW, pParent)
	, dbname(_T("")), oldtbname(_T("")), newtbname(_T(""))
{

}

AlterTableView::~AlterTableView()
{
}

void AlterTableView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dbname);
	DDX_Text(pDX, IDC_EDIT2, oldtbname);
	DDX_Text(pDX, IDC_EDIT3, newtbname);
}


BEGIN_MESSAGE_MAP(AlterTableView, CDialogEx)
	ON_BN_CLICKED(IDOK, &AlterTableView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AlterTableView::OnBnClickedCancel)
END_MESSAGE_MAP()


// AlterTableView ��Ϣ�������


void AlterTableView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDBEntity db;
	db.setDBName(dbname);
	CTablEntity oldtb;
	oldtb.setTableName(oldtbname);
	CTablEntity newtb;
	newtb.setTableName(newtbname);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void AlterTableView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
