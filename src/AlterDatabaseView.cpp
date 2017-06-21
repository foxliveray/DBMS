// AlterDatabaseView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "AlterDatabaseView.h"
#include "afxdialogex.h"
#include "CDBEntity.h"


// AlterDatabaseView �Ի���

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


// AlterDatabaseView ��Ϣ�������


void AlterDatabaseView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
