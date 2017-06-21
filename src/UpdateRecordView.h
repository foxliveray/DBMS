#pragma once
#include "CTableEntity.h"
#include "CFieldEntity.h"
#include "CRecordEntity.h"
#include "RecordLogic.h"

// UpdateRecordView 对话框

class UpdateRecordView : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateRecordView)

public:
	UpdateRecordView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UpdateRecordView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	CListCtrl listctrl;
	CEdit editctrl;

	void setTable(CTablEntity &pTable);
	void setNewRecords(RECORDARR& newData);

	virtual BOOL OnInitDialog();

private:
	CTablEntity* curTable;
	DWORD m_dwItem;		// Row
	int m_nSubItem;		// Column
	RECORDARR* records;

public:
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnBnClickedOk();
};


