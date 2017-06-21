#pragma once
#include "CTableEntity.h"

// TBView 对话框

class TBView : public CDialogEx
{
	DECLARE_DYNAMIC(TBView)

public:
	TBView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TBView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 表名
	CString tbName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
