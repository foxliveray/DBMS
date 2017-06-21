// RegisterView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "RegisterView.h"
#include "afxdialogex.h"
#include"LogLogic.h"

// RegisterView 对话框

IMPLEMENT_DYNAMIC(RegisterView, CDialogEx)

RegisterView::RegisterView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGREGISTER, pParent)
	, username(_T(""))
	, password1(_T(""))
	, password2(_T(""))
{

	EnableAutomation();

}

RegisterView::~RegisterView()
{
}

void RegisterView::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void RegisterView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, username);
	DDX_Text(pDX, IDC_EDIT3, password1);
	DDX_Text(pDX, IDC_EDIT4, password2);
}


BEGIN_MESSAGE_MAP(RegisterView, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &RegisterView::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &RegisterView::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(RegisterView, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IRegisterView 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {64A15763-2C61-43B6-B36A-B77072A615A5}
static const IID IID_IRegisterView =
{ 0x64A15763, 0x2C61, 0x43B6, { 0xB3, 0x6A, 0xB7, 0x70, 0x72, 0xA6, 0x15, 0xA5 } };

BEGIN_INTERFACE_MAP(RegisterView, CDialogEx)
	INTERFACE_PART(RegisterView, IID_IRegisterView, Dispatch)
END_INTERFACE_MAP()


// RegisterView 消息处理程序


void RegisterView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void RegisterView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (username == L"")
	{
		MessageBox(L"用户名不能为空！", L"提示", MB_OK);
	}
	else
	{
		if (password1.CompareNoCase(password2)==0)
		{
			LogLogic sysLogic;
			if (sysLogic.Register(username, password1))
			{
				MessageBox(L"注册成功！", L"提示", MB_OK);
				CDialogEx::OnOK();
			}
			else
				MessageBox(L"用户名存在！", L"提示", MB_OK);
		}
		else
			MessageBox(L"两次密码必须一样！", L"提示", MB_OK);
	}
}
