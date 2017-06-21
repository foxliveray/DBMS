// LoginView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "LoginView.h"
#include "afxdialogex.h"
#include"LogLogic.h"
#include"RegisterView.h"
// LoginView 对话框

IMPLEMENT_DYNAMIC(LoginView, CDialogEx)

LoginView::LoginView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGIN, pParent)
	, user_name(_T("root"))
	, password(_T(""))
{

	EnableAutomation();

}

LoginView::~LoginView()
{
}

void LoginView::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void LoginView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, user_name);
	DDX_Text(pDX, IDC_EDIT3, password);
}


BEGIN_MESSAGE_MAP(LoginView, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoginView::OnBnClickedOk)
	ON_BN_CLICKED(IDC_btnregister, &LoginView::OnBnClickedbtnregister)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(LoginView, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ILoginView 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {D149A772-0C55-4071-8D27-F82F6A66AFFB}
static const IID IID_ILoginView =
{ 0xD149A772, 0xC55, 0x4071, { 0x8D, 0x27, 0xF8, 0x2F, 0x6A, 0x66, 0xAF, 0xFB } };

BEGIN_INTERFACE_MAP(LoginView, CDialogEx)
	INTERFACE_PART(LoginView, IID_ILoginView, Dispatch)
END_INTERFACE_MAP()


// LoginView 消息处理程序


void LoginView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LogLogic lg;
	if (lg.VerifyLogin(user_name, password)) {
		FileLogic f;
		CString path = f.GetTempUsernameFile();
		LogDao m_logdao;
		m_logdao.WriteCurUserName(path, user_name);
		CDialogEx::OnOK();
	}
	else
		MessageBox(L"用户名或者密码错误！",L"提示",MB_OK);
}


void LoginView::OnBnClickedbtnregister()
{
	// TODO: 在此添加控件通知处理程序代码
	RegisterView rv;
	rv.DoModal();
}

