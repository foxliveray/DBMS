#pragma once


// DeleteTableView �Ի���

class DeleteTableView : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteTableView)

public:
	DeleteTableView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DeleteTableView();
	CString dbname;
	CString tbname;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETETABLEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
