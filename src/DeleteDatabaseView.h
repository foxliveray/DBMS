#pragma once


// DeleteDatabaseView �Ի���

class DeleteDatabaseView : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteDatabaseView)

public:
	DeleteDatabaseView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DeleteDatabaseView();
	CString dbname;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETEDATABASEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
