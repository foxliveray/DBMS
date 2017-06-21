// RegisterView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "RegisterView.h"
#include "afxdialogex.h"
#include"LogLogic.h"

// RegisterView �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IRegisterView ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {64A15763-2C61-43B6-B36A-B77072A615A5}
static const IID IID_IRegisterView =
{ 0x64A15763, 0x2C61, 0x43B6, { 0xB3, 0x6A, 0xB7, 0x70, 0x72, 0xA6, 0x15, 0xA5 } };

BEGIN_INTERFACE_MAP(RegisterView, CDialogEx)
	INTERFACE_PART(RegisterView, IID_IRegisterView, Dispatch)
END_INTERFACE_MAP()


// RegisterView ��Ϣ�������


void RegisterView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void RegisterView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (username == L"")
	{
		MessageBox(L"�û�������Ϊ�գ�", L"��ʾ", MB_OK);
	}
	else
	{
		if (password1.CompareNoCase(password2)==0)
		{
			LogLogic sysLogic;
			if (sysLogic.Register(username, password1))
			{
				MessageBox(L"ע��ɹ���", L"��ʾ", MB_OK);
				CDialogEx::OnOK();
			}
			else
				MessageBox(L"�û������ڣ�", L"��ʾ", MB_OK);
		}
		else
			MessageBox(L"�����������һ����", L"��ʾ", MB_OK);
	}
}
