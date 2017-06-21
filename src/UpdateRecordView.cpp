// UpdateRecordView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "UpdateRecordView.h"
#include "afxdialogex.h"


// UpdateRecordView 对话框

IMPLEMENT_DYNAMIC(UpdateRecordView, CDialogEx)

UpdateRecordView::UpdateRecordView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

UpdateRecordView::~UpdateRecordView()
{
}

void UpdateRecordView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listctrl);
	DDX_Control(pDX, IDC_EDIT1, editctrl);
}

BOOL UpdateRecordView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Set style of list control
	DWORD dwStyle = ::GetWindowLong(listctrl.m_hWnd, GWL_STYLE);
	dwStyle |= LVS_REPORT;// Set style
	::SetWindowLong(listctrl.m_hWnd, GWL_STYLE, dwStyle);
	listctrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//Insert column
	CFieldEntity *oneField;
	for (int i = 0; i < curTable->getFieldNum(); i++)
	{
		oneField = curTable->getField(i);
		listctrl.InsertColumn(i, oneField->getFieldName(), LVCFMT_LEFT, 100);
	}
	oneField = NULL;

	//insert records
	CString value, fieldName;
	for (int row = 0; row < records->GetSize(); row++)
	{
		for (int col = 0; col < curTable->getFieldNum(); col++)
		{
			oneField = curTable->getField(col);
			fieldName = oneField->getFieldName();
			value = records->GetAt(row)->get(fieldName);
			if (col == 0)
				listctrl.InsertItem(row, value);
			else
				listctrl.SetItemText(row, col, value);
		}
	}

	// Hide the edit control
	editctrl.ShowWindow(SW_HIDE);

	return TRUE;
}


BEGIN_MESSAGE_MAP(UpdateRecordView, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &UpdateRecordView::OnNMClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &UpdateRecordView::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDOK, &UpdateRecordView::OnBnClickedOk)
END_MESSAGE_MAP()


void UpdateRecordView::setTable(CTablEntity &pTable)
{
	curTable = &pTable;
}

void UpdateRecordView::setNewRecords(RECORDARR &newData)
{
	records = &newData;
}

// UpdateRecordView 消息处理程序


void UpdateRecordView::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_dwItem = pNMListView->iItem;  // The selected row
	m_nSubItem = pNMListView->iSubItem;  // The selected column
	DWORD dwCount = listctrl.GetItemCount();  // The number of the data item in the list

	// If the selected line number greater than 0, the column number greater than 1,
	// and no more than the number of data items in the list, respond to the events
	if (m_dwItem >= 0 && m_nSubItem >= 0 && m_dwItem < records->GetSize() && m_nSubItem < curTable->getFieldNum())
	{

		// Get the size of the selected cell
		CRect rtEdit, rtClient;
		listctrl.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		listctrl.GetSubItemRect(m_dwItem, m_nSubItem, LVIR_LABEL, rtEdit);
		rtEdit.MoveToX(rtEdit.left + rtClient.left + 2);
		rtEdit.MoveToY(rtEdit.top + rtClient.top);
		rtEdit.bottom += 4;

		// Get the content of the selected cells
		CString strItemText = listctrl.GetItemText(m_dwItem, m_nSubItem);
		int nLength = strItemText.GetLength();
		// Set the content of the edit control
		editctrl.SetWindowText(strItemText);
		editctrl.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, rtEdit.Width(), rtEdit.Height(), SWP_SHOWWINDOW);
		editctrl.SetSel(nLength, nLength);
		editctrl.SetFocus();
	}
}


void UpdateRecordView::OnEnKillfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码

	// Get the value of the edit control
	CString strValue;
	editctrl.GetWindowText(strValue);

	// Assign the value of the edit control to list item
	listctrl.SetItemText(m_dwItem, m_nSubItem, strValue);

	// Hide the edit control
	editctrl.ShowWindow(SW_HIDE);
}


void UpdateRecordView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CFieldEntity *oneField;
	CString fieldName;
	CString value;

	for (int row = 0; row < records->GetSize(); row++)
	{
		for (int col = 0; col < curTable->getFieldNum(); col++)
		{
			oneField = curTable->getField(col);
			fieldName = oneField->getFieldName();
			value = listctrl.GetItemText(row, col);

			if (value != records->GetAt(row)->get(fieldName))
				records->GetAt(row)->put(fieldName, value);
		}
	}

	CDialogEx::OnOK();
}
