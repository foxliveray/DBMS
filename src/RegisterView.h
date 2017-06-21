#pragma once


// RegisterView 对话框

class RegisterView : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterView)

public:
	RegisterView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RegisterView();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGREGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
