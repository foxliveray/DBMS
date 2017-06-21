// FieldView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "FieldView.h"
#include "afxdialogex.h"


// FieldView 对话框

IMPLEMENT_DYNAMIC(FieldView, CDialogEx)

FieldView::FieldView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, fieldName(_T(""))
	, str_type(_T(""))
	, defaultvalue(_T(""))
	, var_length(256)
{

}

FieldView::~FieldView()
{
}

void FieldView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, type);
	DDX_Text(pDX, IDC_EDIT1, fieldName);
	DDX_CBString(pDX, IDC_COMBO1, str_type);
	DDX_Text(pDX, IDC_EDIT2, defaultvalue);
	DDX_Text(pDX, IDC_EDIT4, var_length);
}


BEGIN_MESSAGE_MAP(FieldView, CDialogEx)
	ON_BN_CLICKED(IDOK, &FieldView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &FieldView::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK3, &FieldView::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &FieldView::OnBnClickedCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &FieldView::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// FieldView 消息处理程序




void FieldView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (fieldName == L"")
	{
		MessageBox(L"表名不能为空！", L"提示", MB_OK);
	}
	else {
		typenum = type.GetCurSel();
		CButton* pBtn1 = (CButton*)GetDlgItem(IDC_CHECK3);
		isDefault = pBtn1->GetCheck();
		CButton* pBtn2 = (CButton*)GetDlgItem(IDC_CHECK2);
		isNotNull = pBtn2->GetCheck();
		CButton* pBtn3 = (CButton*)GetDlgItem(IDC_CHECK1);
		isPrimary = pBtn3->GetCheck();
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}

}


void FieldView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL FieldView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	type.InsertString(0, _T("INT"));
	type.InsertString(1, _T("VARCHAR"));
	type.InsertString(2, _T("BOOL"));
	type.InsertString(3, _T("DOUBLE"));
	type.InsertString(4, _T("DATATIME"));
	type.SetCurSel(0);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}





void FieldView::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK3);
	isDefault = pBtn->GetCheck();
	if (isDefault == 1) {
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	}
}


void FieldView::OnBnClickedCheck1()
{
	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_CHECK3);
	isDefault = pBtn1->GetCheck();
	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_CHECK2);
	isNotNull = pBtn2->GetCheck();
	CButton* pBtn3 = (CButton*)GetDlgItem(IDC_CHECK1);
	isPrimary = pBtn3->GetCheck();
	if (isPrimary == 1) {
		pBtn2->SetCheck(TRUE);
	}
}


void FieldView::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	typenum = type.GetCurSel();
	switch (typenum) {
	case 1:
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
		break;
	default:
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	}
}
