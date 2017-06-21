// DeleteTableView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "DeleteTableView.h"
#include "afxdialogex.h"
#include "CDBEntity.h"
#include "CTableEntity.h"


// DeleteTableView �Ի���

IMPLEMENT_DYNAMIC(DeleteTableView, CDialogEx)

DeleteTableView::DeleteTableView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DELETETABLEVIEW, pParent)
	, dbname(_T("")), tbname(_T(""))
{

}

DeleteTableView::~DeleteTableView()
{
}

void DeleteTableView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dbname);
	DDX_Text(pDX, IDC_EDIT2, tbname);
}


BEGIN_MESSAGE_MAP(DeleteTableView, CDialogEx)
	ON_BN_CLICKED(IDOK, &DeleteTableView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DeleteTableView::OnBnClickedCancel)
END_MESSAGE_MAP()


// DeleteTableView ��Ϣ�������


void DeleteTableView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDBEntity db;
	db.setDBName(dbname);
	CTablEntity tb;
	tb.setTableName(tbname);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void DeleteTableView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
