#pragma once
#include "afxwin.h"


// alterFieldView �Ի���

class alterFieldView : public CDialogEx
{
	DECLARE_DYNAMIC(alterFieldView)

public:
	alterFieldView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~alterFieldView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
