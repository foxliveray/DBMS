#pragma once


// AlterTableView 对话框

class AlterTableView : public CDialogEx
{
	DECLARE_DYNAMIC(AlterTableView)

public:
	AlterTableView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AlterTableView();
	CString dbname;
	CString oldtbname;
	CString newtbname;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALTERTABLEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
