#pragma once
#include"CDBEntity.h"

// DBView 对话框

class DBView : public CDialogEx
{
	DECLARE_DYNAMIC(DBView)

public:
	DBView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DBView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 数据库名称
	CString dbName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

};
