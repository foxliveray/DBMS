// DeleteDatabaseView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "DeleteDatabaseView.h"
#include "afxdialogex.h"
#include "CDBEntity.h"

// DeleteDatabaseView �Ի���

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


// DeleteDatabaseView ��Ϣ�������


void DeleteDatabaseView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDBEntity DeleteDB;
	DeleteDB.setDBName(dbname);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void DeleteDatabaseView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
