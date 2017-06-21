#pragma once


// AlterDatabaseView 对话框

class AlterDatabaseView : public CDialogEx
{
	DECLARE_DYNAMIC(AlterDatabaseView)

public:
	AlterDatabaseView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AlterDatabaseView();
	CString oldDBName;
	CString newDBName;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALTERDATABASEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
