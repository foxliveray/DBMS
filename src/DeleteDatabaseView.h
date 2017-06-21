#pragma once


// DeleteDatabaseView 对话框

class DeleteDatabaseView : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteDatabaseView)

public:
	DeleteDatabaseView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DeleteDatabaseView();
	CString dbname;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETEDATABASEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
