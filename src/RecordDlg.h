#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include"CTableEntity.h"
#include"CRecordEntity.h"
#include"CFieldEntity.h"

// RecordDlg �Ի���

class RecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecordDlg)

public:
	RecordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RecordDlg();

	virtual void OnFinalRelease();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERTRECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CListCtrl listctrl;
	CEdit m_editValue;

	void setTable(CTablEntity& pTable);
	CRecordEntity GetNewRecord();

private:
	CTablEntity* curTable;
	DWORD m_dwItem;		// Row
	int m_nSubItem;		// Column
	CRecordEntity newRecord;

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
};
