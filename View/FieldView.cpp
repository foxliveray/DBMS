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
}


BEGIN_MESSAGE_MAP(FieldView, CDialogEx)
	ON_BN_CLICKED(IDOK, &FieldView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &FieldView::OnBnClickedCancel)
END_MESSAGE_MAP()


// FieldView 消息处理程序




void FieldView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFieldEntity newfield;
	if (fieldName.GetLength() > 0)
	{
		newfield.setFieldName(fieldName);

		if (str_type.CollateNoCase(_T("INT")) == 0)
		{
			newfield.setFieldType(CFieldEntity::DT_INTEGER);
		}
		else if (str_type.CollateNoCase(_T("BOOL")) == 0)
		{
			newfield.setFieldType(CFieldEntity::DT_BOOL);
		}
		else if (str_type.CollateNoCase(_T("DOUBLE")) == 0)
		{
			newfield.setFieldType(CFieldEntity::DT_DOUBLE);
		}
		else if (str_type.CollateNoCase(_T("VARCHAR")) == 0)
		{
			newfield.setFieldType(CFieldEntity::DT_VARCHAR);
			newfield.setParam(256);
		}
		else if (str_type.CollateNoCase(_T("DATATIME")) == 0)
		{
			newfield.setFieldType(CFieldEntity::DT_DATETIME);
		}
		CDialogEx::OnOK();
	}
	UpdateData(FALSE);
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

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



