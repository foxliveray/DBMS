#pragma once
#include "CTableEntity.h"
#include "CRecordEntity.h"
#include "RecordLogic.h"

// SelectView �Ի���

class SelectView : public CDialogEx
{
	DECLARE_DYNAMIC(SelectView)

public:
	SelectView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectView();
	CListCtrl m_listCtrl;
	CEdit m_edit;
	CComboBox m_combox;

	int m_nRow;
	int m_nColumn;
	int m_compType;

	void setTable(CTablEntity &pTable);
	void setDBName(CString dbname);
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnKillfocusEdit1();
	virtual BOOL OnInitDialog();
	void setRecord(RECORDARR& rcd);
	RECORDARR* getRecord();

private:
	CTablEntity* curTable;
	CString DBName;
	RECORDARR* SelectedRcd;
};
