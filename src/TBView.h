#pragma once
#include "CTableEntity.h"

// TBView �Ի���

class TBView : public CDialogEx
{
	DECLARE_DYNAMIC(TBView)

public:
	TBView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TBView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����
	CString tbName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
