// MainView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "MainFrm.h"
#include "MainView.h"
#include "CRecordEntity.h"
#include "RecordLogic.h"
#include "CFieldEntity.h"

// MainView

IMPLEMENT_DYNCREATE(MainView, CListView)

MainView::MainView()
{
	m_listCtrl = &GetListCtrl();
}

MainView::~MainView()
{
}



BEGIN_MESSAGE_MAP(MainView, CListView)
	
	ON_COMMAND(ID_RECORD_DELETERECORD, &MainView::OnRecordDeleterecord)
END_MESSAGE_MAP()


// MainView 绘图

void MainView::setListStyle()
{
	//set the style of report(CListCtrl)
	DWORD dwStyle = ::GetWindowLong(m_listCtrl->m_hWnd, GWL_STYLE);
	dwStyle |= LVS_REPORT;// Set style
	::SetWindowLong(m_listCtrl->m_hWnd, GWL_STYLE, dwStyle);
	m_listCtrl->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

void MainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码

}



// MainView 诊断

#ifdef _DEBUG
void MainView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MainView 消息处理程序

//
CTreeCtrl* MainView::GetTreeControl()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	MainView *pView = (MainView*)pMainFrame->m_mainview;
	return pView->m_treeCtrl;
}


void MainView::OnRecordDeleterecord()
{
	// TODO: 在此添加命令处理程序代码

	//get selected row
	int selectRow = m_listCtrl->GetSelectionMark();

	if (selectRow == -1)
	{
		MessageBox(_T("请确认选中了一个记录.=)"), _T("Oooops"), MB_ICONWARNING | MB_OK);
		return;
	}

	//get selected record
	CRecordEntity selectRecord;
	int fieldNum = m_listCtrl->GetHeaderCtrl()->GetItemCount();
	CString fieldName, value;
	HDITEM   hdi;
	TCHAR     lpBuffer[256];
	LPCTSTR   lpszmyString;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	for (int col = 0; col < fieldNum; col++)
	{
		m_listCtrl->GetHeaderCtrl()->GetItem(col, &hdi);
		fieldName = hdi.pszText;

		value = m_listCtrl->GetItemText(selectRow, col);

		selectRecord.put(fieldName, value);
	}

	// Get current table(in tree control) and current db name
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	LsiderView *pView = (LsiderView*)pMainFrame->m_lsiderview;
	CTablEntity curTable = pView->curtb_inTreeCtrl;
	CString dbName = pView->curDBName;
	// Resume fields in table
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);

	//check info
	CString checkInfo = _T("");
	for (int i = 0; i < curTable.getFieldNum(); i++)
	{
		checkInfo += curTable.getField(i)->getFieldName();
		checkInfo += ": ";
		checkInfo += selectRecord.get(curTable.getField(i)->getFieldName());
		checkInfo += "\n";
	}

	int res = MessageBox(_T("请确认删除该记录.=)\n" + checkInfo),
		_T("Have a check!"), MB_ICONWARNING | MB_OKCANCEL);
	if (res == IDOK)
	{
		RecordLogic rLogic;
		rLogic.Delete(dbName, curTable, selectRow);
	}

	//update records - delete version
	RECORDARR records;
	RecordLogic recordLogic;
	recordLogic.SelectAll(dbName, curTable, records);
	CFieldEntity *oneField;
	//clear list control
	m_listCtrl->DeleteAllItems();
	while (m_listCtrl->DeleteColumn(0));
	//insert column name
	for (int col = 0; col < curTable.getFieldNum(); col++)
	{
		oneField = curTable.getField(col);
		fieldName = oneField->getFieldName();
		m_listCtrl->InsertColumn(col, fieldName, LVCFMT_LEFT, 100);
	}
	//insert item
	for (int row = 0; row < records.GetSize(); row++)
	{
		for (int col = 0; col < curTable.getFieldNum(); col++)
		{
			oneField = curTable.getField(col);
			fieldName = oneField->getFieldName();
			value = records.GetAt(row)->get(fieldName);
			if (col == 0)
				m_listCtrl->InsertItem(row, value);
			else
				m_listCtrl->SetItemText(row, col, value);
		}
	}
}
