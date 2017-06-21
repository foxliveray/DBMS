// SelectView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "SelectView.h"
#include "afxdialogex.h"

#define EQUAL 0
#define GREATER 1
#define LESSER 2
// SelectView 对话框

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


// SelectView 消息处理程序


void SelectView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void SelectView::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtrl.GetItemCount();

	if (m_nRow >= 0 && m_nRow <= nCount)
	{
		// 设置接收框到列表对应位置
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// 把用户输入的内容同步到列表上
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


BOOL SelectView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化listCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);   // 获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK;                              // 清除显示方式位
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // 选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;                          // 网格线
	m_listCtrl.SetExtendedStyle(dwStyle);                 // 设置扩展风格

	m_listCtrl.InsertColumn(0, CString("字段名"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(1, CString("比较"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(2, CString("值"), LVCFMT_LEFT, 100);


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
				  // 异常: OCX 属性页应返回 FALSE
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