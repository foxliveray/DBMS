// alterFieldView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "alterFieldView.h"
#include "afxdialogex.h"


// alterFieldView 对话框

IMPLEMENT_DYNAMIC(alterFieldView, CDialogEx)

alterFieldView::alterFieldView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, newfieldname(_T(""))
	, var_length(0)
{

}

alterFieldView::~alterFieldView()
{
}

void alterFieldView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, newfieldname);
	DDX_Control(pDX, IDC_COMBO1, newtype);
	DDX_Control(pDX, IDC_CHECK1, CHECK);
	DDX_Control(pDX, IDC_CHECK2, CHECK2);
	DDX_Text(pDX, IDC_EDIT2, var_length);
}


BEGIN_MESSAGE_MAP(alterFieldView, CDialogEx)
	ON_BN_CLICKED(IDOK, &alterFieldView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &alterFieldView::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &alterFieldView::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &alterFieldView::OnBnClickedCheck2)
END_MESSAGE_MAP()


// alterFieldView 消息处理程序


void alterFieldView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (changetype == 1) {
		typenum = newtype.GetCurSel();
	}
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void alterFieldView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL alterFieldView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE);
	newtype.InsertString(0, _T("INT"));
	newtype.InsertString(1, _T("VARCHAR"));
	newtype.InsertString(2, _T("BOOL"));
	newtype.InsertString(3, _T("DOUBLE"));
	newtype.InsertString(4, _T("DATATIME"));
	newtype.SetCurSel(typenum);
	if (typenum != 1) {
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void alterFieldView::OnBnClickedCheck1()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	changename = pBtn->GetCheck();
	if (changename == 1) {
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void alterFieldView::OnBnClickedCheck2()
{
	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_CHECK2);
	changetype = pBtn2->GetCheck();
	if (changetype == 1) {
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	}
	// TODO: 在此添加控件通知处理程序代码
}
