#pragma once


// RegisterView �Ի���

class RegisterView : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterView)

public:
	RegisterView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegisterView();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGREGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString username;
	CString password1;
	CString password2;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
