// LoginView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "LoginView.h"
#include "afxdialogex.h"
#include"LogLogic.h"
#include"RegisterView.h"
// LoginView �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ILoginView ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {D149A772-0C55-4071-8D27-F82F6A66AFFB}
static const IID IID_ILoginView =
{ 0xD149A772, 0xC55, 0x4071, { 0x8D, 0x27, 0xF8, 0x2F, 0x6A, 0x66, 0xAF, 0xFB } };

BEGIN_INTERFACE_MAP(LoginView, CDialogEx)
	INTERFACE_PART(LoginView, IID_ILoginView, Dispatch)
END_INTERFACE_MAP()


// LoginView ��Ϣ�������


void LoginView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(L"�û��������������",L"��ʾ",MB_OK);
}


void LoginView::OnBnClickedbtnregister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RegisterView rv;
	rv.DoModal();
}

