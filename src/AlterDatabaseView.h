#pragma once


// AlterDatabaseView �Ի���

class AlterDatabaseView : public CDialogEx
{
	DECLARE_DYNAMIC(AlterDatabaseView)

public:
	AlterDatabaseView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AlterDatabaseView();
	CString oldDBName;
	CString newDBName;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALTERDATABASEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
