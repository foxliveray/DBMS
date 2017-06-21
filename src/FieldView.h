#pragma once
#include "afxwin.h"
#include"CFieldEntity.h"

// FieldView �Ի���

class FieldView : public CDialogEx
{
	DECLARE_DYNAMIC(FieldView)

public:
	FieldView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FieldView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox type;
	// �ֶ�����
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
