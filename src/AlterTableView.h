#pragma once


// AlterTableView �Ի���

class AlterTableView : public CDialogEx
{
	DECLARE_DYNAMIC(AlterTableView)

public:
	AlterTableView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AlterTableView();
	CString dbname;
	CString oldtbname;
	CString newtbname;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALTERTABLEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
