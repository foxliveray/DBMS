#pragma once


// DeleteTableView 对话框

class DeleteTableView : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteTableView)

public:
	DeleteTableView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DeleteTableView();
	CString dbname;
	CString tbname;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETETABLEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
