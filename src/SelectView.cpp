// SelectView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "SelectView.h"
#include "afxdialogex.h"

#define EQUAL 0
#define GREATER 1
#define LESSER 2
// SelectView �Ի���

IMPLEMENT_DYNAMIC(SelectView, CDialogEx)

SelectView::SelectView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECTVIEW, pParent)
{

}

SelectView::~SelectView()
{
}

void SelectView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(SelectView, CDialogEx)
	ON_BN_CLICKED(IDOK, &SelectView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SelectView::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &SelectView::OnNMClickList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SelectView::OnCbnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &SelectView::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// SelectView ��Ϣ�������


void SelectView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vector<CString> compare;
	vector<CString> values;
	int fieldNum = curTable->getFieldNum();
	for (int i = 0; i<fieldNum; i++)
	{
		compare.push_back(m_listCtrl.GetItemText(i, 1));
		values.push_back(m_listCtrl.GetItemText(i, 2));
	}
	RecordLogic rcdLogic;
	//RECORDARR* Records = NULL;
	rcdLogic.DetailedSelect(DBName, *curTable, compare, values, SelectedRcd);
	//setRecord(Records);
	CDialogEx::OnOK();
}


void SelectView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void SelectView::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtrl.GetItemCount();

	if (m_nRow >= 0 && m_nRow <= nCount)
	{
		// ���ý��տ��б��Ӧλ��
		CRect rtEdit, rtClient;
		m_listCtrl.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		m_listCtrl.GetSubItemRect(m_nRow, m_nColumn, LVIR_LABEL, rtEdit);
		/*rtEdit.left += rtClient.left + 0;
		rtEdit.top += rtClient.top + 0;
		rtEdit.bottom += 0;*/
		rtEdit.MoveToX(rtEdit.left + rtClient.left + 2);
		rtEdit.MoveToY(rtEdit.top + rtClient.top);
		rtEdit.bottom += 4;

		if (m_nColumn == 2)
		{
			CString strTemp = m_listCtrl.GetItemText(m_nRow, m_nColumn);
			int nLength = strTemp.GetLength();
			m_edit.SetWindowText(strTemp);
			m_edit.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, rtEdit.Width(), rtEdit.Height(), SWP_SHOWWINDOW);
			m_edit.SetSel(nLength, nLength);
			m_edit.ShowWindow(TRUE);
			m_edit.SetFocus();
		}
		else if (m_nColumn == 1)
		{
			m_combox.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, rtEdit.Width(), rtEdit.Height(), SWP_SHOWWINDOW);
			//m_edit.SetSel(nLength, nLength);
			m_combox.ShowWindow(TRUE);
			m_combox.SetFocus();
		}



	}
	*pResult = 0;
}


void SelectView::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_compType = m_combox.GetCurSel();
	CString value;
	switch (m_compType)
	{
	case EQUAL:value = L"="; break;
	case GREATER:value = L">"; break;
	case LESSER:value = L"<"; break;
	default: break;
	}
	m_combox.ShowWindow(SW_HIDE);
	m_listCtrl.SetItemText(m_nRow, m_nColumn, value);
}


void SelectView::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// ���û����������ͬ�����б���
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


BOOL SelectView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ��listCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);   // ��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK;                              // �����ʾ��ʽλ
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;                          // ������
	m_listCtrl.SetExtendedStyle(dwStyle);                 // ������չ���

	m_listCtrl.InsertColumn(0, CString("�ֶ���"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(1, CString("�Ƚ�"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(2, CString("ֵ"), LVCFMT_LEFT, 100);


	CFieldEntity *oneField;
	int fieldNum = curTable->getFieldNum();
	for (int i = 0; i < fieldNum; i++)
	{
		oneField = curTable->getField(i);
		m_listCtrl.InsertItem(i, oneField->getFieldName());
		m_listCtrl.SetItemText(i, 1, L"=");
	}
	oneField = NULL;

	m_combox.InsertString(0, L"=");
	m_combox.InsertString(1, L">");
	m_combox.InsertString(2, L"<");

	m_edit.ShowWindow(FALSE);
	m_combox.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void SelectView::setTable(CTablEntity &pTable)
{
	curTable = &pTable;
}

void SelectView::setDBName(CString dbname) {
	DBName = dbname;
}

RECORDARR* SelectView::getRecord() {
	return SelectedRcd;
}

void SelectView::setRecord(RECORDARR& rcd) {
	SelectedRcd = &rcd;
}