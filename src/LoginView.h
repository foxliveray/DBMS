#pragma once


// LoginView 对话框

class LoginView : public CDialogEx
{
	DECLARE_DYNAMIC(LoginView)

public:
	LoginView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginView();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString user_name;
	CString password;
	afx_msg void OnBnClickedbtnregister();
	afx_msg void OnEnChangeEdit3();
};
