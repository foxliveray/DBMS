#pragma once
#include"CDBEntity.h"

// DBView �Ի���

class DBView : public CDialogEx
{
	DECLARE_DYNAMIC(DBView)

public:
	DBView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DBView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ���ݿ�����
	CString dbName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

};
