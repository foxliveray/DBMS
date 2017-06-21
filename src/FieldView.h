#pragma once
#include "afxwin.h"
#include"CFieldEntity.h"

// FieldView 对话框

class FieldView : public CDialogEx
{
	DECLARE_DYNAMIC(FieldView)

public:
	FieldView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FieldView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox type;
	// 字段名称
	CString fieldName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CString str_type;
	int typenum;
	CString defaultvalue;
	int isDefault;
	int isPrimary;
	int isNotNull;
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck1();
	void OnCbnSelchangeCombo1();
	int var_length;
};
