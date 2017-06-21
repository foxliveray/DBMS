#pragma once
#include "afxwin.h"


// alterFieldView 对话框

class alterFieldView : public CDialogEx
{
	DECLARE_DYNAMIC(alterFieldView)

public:
	alterFieldView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~alterFieldView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString newfieldname;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CComboBox newtype;
	virtual BOOL OnInitDialog();
	CButton CHECK;
	CButton CHECK2;
	bool changename;
	bool changetype;
	int typenum;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	int var_length;
};
