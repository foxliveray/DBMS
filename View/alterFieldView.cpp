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
}


BEGIN_MESSAGE_MAP(alterFieldView, CDialogEx)
	ON_BN_CLICKED(IDOK, &alterFieldView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &alterFieldView::OnBnClickedCancel)
END_MESSAGE_MAP()


// alterFieldView 消息处理程序


void alterFieldView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	changename = pBtn->GetCheck();
	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_CHECK2);
	changetype= pBtn2->GetCheck();
	if (changename == 1) {
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	}
	if (changetype == 1) {
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	}
	UpdateData(TRUE);
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
	newtype.InsertString(0, _T("INT"));
	newtype.InsertString(1, _T("VARCHAR"));
	newtype.InsertString(2, _T("BOOL"));
	newtype.InsertString(3, _T("DOUBLE"));
	newtype.InsertString(4, _T("DATATIME"));
	newtype.SetCurSel(0);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);

	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
