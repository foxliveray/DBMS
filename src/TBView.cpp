// TBView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "TBView.h"
#include "afxdialogex.h"


// TBView �Ի���

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


// TBView ��Ϣ�������


void TBView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (tbName == L"")
	{
		MessageBox(L"��������Ϊ�գ�", L"��ʾ", MB_OK);
	}
	else {
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}

}


void TBView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CDialogEx::OnCancel();
}
