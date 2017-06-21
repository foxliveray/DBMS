// RecordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "RecordDlg.h"
#include "afxdialogex.h"


// RecordDlg �Ի���

IMPLEMENT_DYNAMIC(RecordDlg, CDialogEx)

RecordDlg::RecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSERTRECORD, pParent)
{

	EnableAutomation();

}

RecordDlg::~RecordDlg()
{
}

void RecordDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void RecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listctrl);
	DDX_Control(pDX, IDC_EDIT1, m_editValue);
}


BEGIN_MESSAGE_MAP(RecordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RecordDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &RecordDlg::OnNMClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &RecordDlg::OnEnKillfocusEdit1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(RecordDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IRecordDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {836A4DE0-9A2A-411C-B9DC-D46565D3053A}
static const IID IID_IRecordDlg =
{ 0x836A4DE0, 0x9A2A, 0x411C, { 0xB9, 0xDC, 0xD4, 0x65, 0x65, 0xD3, 0x5, 0x3A } };

BEGIN_INTERFACE_MAP(RecordDlg, CDialogEx)
	INTERFACE_PART(RecordDlg, IID_IRecordDlg, Dispatch)
END_INTERFACE_MAP()


// RecordDlg ��Ϣ�������


void RecordDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount = listctrl.GetItemCount();

	CString strField;
	CString strValue;
	// Get the value of each row in the list
	for (int i = 0; i < nCount; i++)
	{
		// Field name
		strField = listctrl.GetItemText(i, 0);

		// Value
		strValue = listctrl.GetItemText(i, 2);

		newRecord.put(strField, strValue);
	}

	CDialogEx::OnOK();
}

void RecordDlg::setTable(CTablEntity & pTable)
{
	curTable = &pTable;
}

CRecordEntity RecordDlg::GetNewRecord()
{
	return newRecord;
}


BOOL RecordDlg::OnInitDialog()
{
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CDialogEx::OnInitDialog();
	DWORD dwStyle = ::GetWindowLong(listctrl.m_hWnd, GWL_STYLE);
	dwStyle |= LVS_REPORT;// Set style
	::SetWindowLong(listctrl.m_hWnd, GWL_STYLE, dwStyle);
	listctrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	listctrl.InsertColumn(0, _T("Field Name"), LVCFMT_LEFT, 100);
	listctrl.InsertColumn(1, _T("Field Type"), LVCFMT_LEFT, 100);
	listctrl.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 100);

	int fieldNum = curTable->getFieldNum();
	for (int i = 0; i < fieldNum; i++)
	{
		CFieldEntity* pfield = curTable->getField(i);
		listctrl.InsertItem(i, pfield->getFieldName());
		listctrl.SetItemText(i, 1, pfield->getFieldType());
	}

	// Hide the edit control
	m_editValue.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}





void RecordDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_dwItem = pNMListView->iItem;  // The selected row
	m_nSubItem = pNMListView->iSubItem;  // The selected column
	DWORD dwCount = listctrl.GetItemCount();  // The number of the data item in the list

											  // If the selected line number greater than 0, the column number greater than 1,
											  // and no more than the number of data items in the list, respond to the events
	if (m_dwItem >= 0 && m_nSubItem == 2 && m_dwItem <= dwCount)
	{
		CFieldEntity* pField = curTable->getField(m_dwItem);

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
		m_editValue.SetWindowText(strItemText);
		m_editValue.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, rtEdit.Width(), rtEdit.Height(), SWP_SHOWWINDOW);
		m_editValue.SetSel(nLength, nLength);
		m_editValue.SetFocus();
	}
}


void RecordDlg::OnEnKillfocusEdit1()
{
	// Get the value of the edit control
	CString strValue;
	m_editValue.GetWindowText(strValue);

	// Assign the value of the edit control to list item
	listctrl.SetItemText(m_dwItem, m_nSubItem, strValue);

	// Hide the edit control
	m_editValue.ShowWindow(SW_HIDE);
}
