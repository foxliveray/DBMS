// LsiderView.cpp : ��ߵ����οؼ���ʾ����ʵ��
//

#include "stdafx.h"
#include "DBMS.h"
#include "LsiderView.h"
#include"FieldView.h"
#include"FieldLogic.h"
#include"alterFieldView.h"
#include"TableLogic.h"
#include"TBView.h"
#include"CIntegrityEntity.h"
#include"IntegrityLogic.h"
#include"LoginView.h"
#include"RecordDlg.h"
#include"CRecordEntity.h"
#include"RecordLogic.h"
#include"MainFrm.h"
#include"MainView.h"
#include "UpdateRecordView.h"
// LsiderView

IMPLEMENT_DYNCREATE(LsiderView, CTreeView)

LsiderView::LsiderView()
{
	m_treectrl = &GetTreeCtrl();
}

LsiderView::~LsiderView()
{
}

BEGIN_MESSAGE_MAP(LsiderView, CTreeView)
	ON_WM_PAINT()
	ON_COMMAND(ID_DATABASE_CREATEDATABASE, &LsiderView::OnDatabaseCreatedatabase)
	ON_COMMAND(ID_FIELD_CREATFIELD, &LsiderView::OnFieldCreatfield)
	ON_COMMAND(ID_FIELD_MODIFYFIELD, &LsiderView::OnFieldModifyfield)
	ON_COMMAND(ID_TABLE_DROPTABLE32785, &LsiderView::OnTableDroptable32785)
	ON_COMMAND(ID_TABLE_CREATETABLE, &LsiderView::OnTableCreatetable)
	ON_COMMAND(ID_DATABASE_OPENDATABASE, &LsiderView::OnDatabaseOpendatabase)
	ON_COMMAND(ID_TABLE_OPENTABLE, &LsiderView::OnTableOpentable)
	ON_COMMAND(ID_FIELD_DROPFIELD, &LsiderView::OnFieldDropfield)
	//ON_COMMAND(ID_TEST_TESTLOGIN, &LsiderView::OnTestTestlogin)
	ON_COMMAND(ID_RECORD_INSERTRECORD, &LsiderView::OnRecordInsertrecord)
	ON_COMMAND(ID_RECORD_SELECTRECORD, &LsiderView::OnRecordSelectrecord)
	ON_COMMAND(ID_FIELD_SHOWFIELD, &LsiderView::OnFieldShowfield)
	ON_COMMAND(ID_DATABASE_MODIFYDATABASE, &LsiderView::OnDatabaseModifydatabase)
	ON_COMMAND(ID_DATABASE_DELETEDATABASE, &LsiderView::OnDatabaseDeletedatabase)
	ON_COMMAND(ID_TABLE_ALTERTABLE, &LsiderView::OnTableAltertable)
	ON_COMMAND(ID_RECORD_UPDATERECORD, &LsiderView::OnRecordUpdaterecord)
	ON_COMMAND(ID_DATABASE_BACKUPDATABASE, &LsiderView::OnDatabaseBackupdatabase)
	ON_COMMAND(ID_RECORD_DETAILEDSELECT, &LsiderView::OnRecordDetailedselect)
	ON_COMMAND(ID_SYSTEM_LOOKLOGFILE, &LsiderView::OnSystemLooklogfile)
END_MESSAGE_MAP()


// LsiderView ���

#ifdef _DEBUG
void LsiderView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void LsiderView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// LsiderView ��Ϣ�������



void LsiderView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	//������ʵ�����οؼ�������Ŀ�����

	//	Delete images from the list
	m_imageList.DeleteImageList();

	// Create icon list
	m_imageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 4, 1);

	//	Get tree control
	m_treectrl = &this->GetTreeCtrl();

	DWORD dwStyles = GetWindowLong(m_treectrl->m_hWnd, GWL_STYLE);
	dwStyles |= TVS_EDITLABELS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	SetWindowLong(m_treectrl->m_hWnd, GWL_STYLE, dwStyles);

	// Add images to the list
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));


	// Get the style of the tree control
	m_treectrl->SetImageList(&m_imageList, TVSIL_NORMAL);
	//��ʾ���е����ݿ��б�

	this->DisplayDBList();
}

void LsiderView::OnUpdate() {
	this->DisplayDBList();
}

bool LsiderView::CreateDatabase(CString dbname)
{
	CDBEntity* m_dbEntity = new CDBEntity();
	m_dbEntity->setDBName(dbname);		//ȱʡ��Ĭ�ϣ������ݿ��������Star

	DBLogic dbLogic;
	try {
		//�ж����ݿ��Ƿ����
		if (dbLogic.GetDatabase(*m_dbEntity) == false) {
			//�ж��Ƿ�ɹ��������ݿ�
			if (dbLogic.CreateDatabase(*m_dbEntity) == false) {
				//������ʧ�ܣ��׳�һ���쳣
				throw new CAppException(_T("Failed to create database!"));
				return false;
			}
		}
		//�����ĵ��ı���
		CString strTitle;
		strTitle.Format(_T("Database(%s)"), m_dbEntity->getDBName());

	}
	catch (CAppException *e) {
		e->GetErrorMessage();
//		throw e;
		delete e;
	}

	return true;
	
}

bool LsiderView::CreateField(CString fieldName, int type, int length, int integrity)
{
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString tbName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hCurrItem);
	CString dbName = m_treectrl->GetItemText(hParentItem);
	HTREEITEM hParentParentItem = m_treectrl->GetParentItem(hParentItem);
	if (hParentParentItem != NULL || hParentItem == NULL) {
		MessageBox(L"��ѡ�������", L"��ʾ", MB_OK);
		return false;
	}
	UpdateData(FALSE);
	CFieldEntity* field = new CFieldEntity();
	field->setFieldName(fieldName);
	field->setFieldType(type);
	field->setIntegrity(integrity);
	field->setParam(length);
	/*TableDao tDao;
	FileLogic filelogic;
	tDao.AddFieldNum(filelogic.GetTableFile(tbName), tbName, *field);*/
	// get current table & resume its fields
	CTablEntity curTable = GetSelectedTable(hCurrItem);
	TableDao tDao;
	FileLogic fileLogic;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tDao.ResumeFieldsIntable(TdfPath, curTable);
	// get all old records
	RECORDARR records;
	RecordLogic recordLogic;
	recordLogic.SelectAll(dbName, curTable, records);

	FieldLogic fieldLogic;
	try {
		if (fieldLogic.getField(dbName, tbName, *field) == false) {
			if (fieldLogic.CreateField(dbName, tbName, *field) == false) {
				//������ʧ�ܣ��׳�һ���쳣
				throw new CAppException(_T("Failed to create field!"));
			}
		}
	}
	catch (CAppException *e) {
		e->GetErrorMessage();
		//		throw e;
		delete e;
	}

	// update table file
	IntegrityLogic integritylogic;
	curTable.addField(*field);
	CString tableFile = fileLogic.GetTableFile(dbName);
	if (tDao.AlterTable(tableFile, curTable) == false)
		return false;
	// update record file

	for (int i = 0; i < records.GetSize(); i++)
	{
		if (integritylogic.isDefaultKey(dbName, tbName, fieldName) == TRUE) {
			records.GetAt(i)->put(fieldName, integritylogic.getDefaultValue(dbName, tbName, fieldName));
		}
		else {
			records.GetAt(i)->put(fieldName, CString("0"));		//������
		}

	}
	recordLogic.Rewrite(curTable, records);

	FreshListControl(dbName, curTable);

	return true;
}

bool LsiderView::CreateTable(CString tbname) {
	CTablEntity* pTable = new CTablEntity();
	pTable->setTableName(tbname);
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString dbName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentParentItem = m_treectrl->GetParentItem(hCurrItem);
	if (hParentParentItem != NULL ) {
		MessageBox(L"��ѡ����ȷ�����ݿ⣡", L"��ʾ", MB_OK);
		return false;
	}
	else {
		TableLogic tbLogic;
		try {
			//�ж��Ƿ�ɹ������˱�
			if (tbLogic.CreateTable(GetTreeCtrl().GetItemText(m_treectrl->GetSelectedItem()), *pTable) == true)
			{
				//����ɹ������˱���ô�������Ϣ�ͻᱻ���浽������
				m_arrTable.Add(pTable);
			}
			else {
				delete pTable;
				pTable = NULL;
			}
		}
		catch (CException *e) {
			if (pTable != NULL)
			{
				delete pTable;
				pTable = NULL;
			}
			e->Delete();
			throw new CAppException(_T("Failed to create table."));
		}

	}

	return true;
}

bool LsiderView::CreateIntegriyies(CString fieldname, int primary, int notnull, int isdefault, CString value)
{
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString tbName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hCurrItem);
	CString dbName = m_treectrl->GetItemText(hParentItem);
	HTREEITEM hParentParentItem = m_treectrl->GetParentItem(hParentItem);
	if (hParentParentItem != NULL || hParentItem == NULL) {
		MessageBox(L"��ѡ�������", L"��ʾ", MB_OK);
		return false;
	}
	else {
		UpdateData(FALSE);
		CIntegrityEntity* itg = new CIntegrityEntity(fieldname, primary, notnull, isdefault, value);
		IntegrityLogic intelogic;
		try {
			if (intelogic.createIntegrity(dbName, tbName, *itg) == false) {
				//������ʧ�ܣ��׳�һ���쳣
				throw new CAppException(_T("Failed to create integrity!"));
			}
		}
		catch (CAppException *e) {
			e->GetErrorMessage();
			//		throw e;
			delete e;
		}
	}
	return true;
}
bool LsiderView::AlterFieldName(CString fieldName)
{
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString oldName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hCurrItem);
	CString tbName = m_treectrl->GetItemText(hParentItem);
	HTREEITEM hGrandParentItem = m_treectrl->GetParentItem(hParentItem);
	CString dbName = m_treectrl->GetItemText(hGrandParentItem);
	UpdateData(FALSE);

	FieldLogic fieldLogic;
	IntegrityLogic intelogic;
	try {
		if (fieldLogic.getField(dbName, tbName, oldName, fieldName) == false||intelogic.getInter(dbName, tbName, oldName, fieldName)==false) {
			throw new CAppException(_T("Failed to alter field name!"));
			return false;
		}
		else {
			m_treectrl->SetItemText(hCurrItem, fieldName);
		}
	}
	catch (CAppException *e) {
		e->GetErrorMessage();
		//		throw e;
		delete e;
	}
	return true;

}
bool LsiderView::AlterFieldType(int length)
{
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString oldName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hCurrItem);
	CString tbName = m_treectrl->GetItemText(hParentItem);
	HTREEITEM hGrandParentItem = m_treectrl->GetParentItem(hParentItem);
	CString dbName = m_treectrl->GetItemText(hGrandParentItem);
	UpdateData(FALSE);

	FieldLogic fieldLogic;
	try {
		if (fieldLogic.getField(dbName, tbName, oldName, length) == false) {
			throw new CAppException(_T("Failed to alter field name!"));
			return false;
		}
	}
	catch (CAppException *e) {
		e->GetErrorMessage();
		//		throw e;
		delete e;
	}
	return true;
}

void LsiderView::DisplayDBList()
{
	DBLogic dblogic;
	vector<CDBEntity> dblist = dblogic.GetDatabaseList();
	//ɾ����״ͼ�е����ݿ���ʾ
	HTREEITEM hNextItem;
	HTREEITEM hPreItem = m_treectrl->GetRootItem();		//��ø��ڵ�
	while (hPreItem != NULL)
	{
		hNextItem = m_treectrl->GetNextItem(hPreItem, TVGN_NEXT);		//��õ�ǰ���ڵ����һ���ڵ�
		m_treectrl->DeleteItem(hPreItem);
		hPreItem = hNextItem;
	}

	for (vector<CDBEntity>::iterator ite = dblist.begin(); ite != dblist.end(); ++ite)
	{
		HTREEITEM hRoot = m_treectrl->InsertItem(ite->getDBName(), 0, 0, TVI_ROOT, TVI_LAST);
		m_treectrl->SetItemData(hRoot, 0);
	}
}

void LsiderView::DisplayTableList() {
	HTREEITEM m_hCurrDBItem = m_treectrl->GetSelectedItem();
	CString dbName = m_treectrl->GetItemText(m_hCurrDBItem);
	HTREEITEM hNextItem;
	HTREEITEM hChildItem = m_treectrl->GetChildItem(m_hCurrDBItem);
	while (hChildItem != NULL)
	{
		hNextItem = m_treectrl->GetNextItem(hChildItem, TVGN_NEXT);
		m_treectrl->DeleteItem(hChildItem);
		hChildItem = hNextItem;
	}

	TableLogic tbLogic;
	vector<CTablEntity> tbList = tbLogic.getTableList(dbName);
	for (int i = 0; i < tbList.size(); i++)
	{
		CString a=CharHelper::ToString(tbList[i].GetBlock().name, sizeof(VARCHAR));
		m_treectrl->SetItemData(m_treectrl->InsertItem(a, 1, 1, m_hCurrDBItem), 0);
	}
	m_treectrl->Expand(m_hCurrDBItem, TVE_EXPAND);

}
void LsiderView::DisplayFieldList() {
	HTREEITEM m_hCurrDBItem = m_treectrl->GetSelectedItem();
	CString tbName = m_treectrl->GetItemText(m_hCurrDBItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(m_hCurrDBItem);
	CString dbName = m_treectrl->GetItemText(hParentItem);
	
	HTREEITEM hNextItem;
	HTREEITEM hChildItem = m_treectrl->GetChildItem(m_hCurrDBItem);
	while (hChildItem != NULL)
	{
		hNextItem = m_treectrl->GetNextItem(hChildItem, TVGN_NEXT);
		m_treectrl->DeleteItem(hChildItem);
		hChildItem = hNextItem;
	}
	FieldLogic fdlogic;
	vector<CFieldEntity> fdlist = fdlogic.GetFieldList(dbName, tbName);

	for (int i = 0; i < fdlist.size(); i++)
	{
		CString a = CharHelper::ToString(fdlist[i].GetBlock().name, sizeof(VARCHAR));
		m_treectrl->SetItemData(m_treectrl->InsertItem(a, 1, 1, m_hCurrDBItem), 0);
	}
	m_treectrl->Expand(m_hCurrDBItem, TVE_EXPAND);
}

void LsiderView::OnDatabaseCreatedatabase()
{
	DBView dlg = new DBView;
	int nRes = dlg.DoModal();

	// TODO: �ڴ���������������
	if (nRes == IDOK) {
		if (CreateDatabase(dlg.dbName)) {
			this->DisplayDBList();
		}
	}
	
}



void LsiderView::OnFieldCreatfield()
{

	bool isok = true;
	FieldView dlg = new FieldView();
	int nRes = dlg.DoModal();
	int type = dlg.typenum;
	int integrity = 0;
	int num = dlg.var_length;
	if (nRes == IDOK) {
		if (dlg.isDefault == 1)
			integrity++;
		if (dlg.isPrimary == 1)
			integrity++;
		if (dlg.isNotNull == 1)
			integrity++;
		if (integrity != 0)
			isok = CreateIntegriyies(dlg.fieldName, dlg.isPrimary, dlg.isNotNull, dlg.isDefault, dlg.defaultvalue);
		if (isok) {
			if (CreateField(dlg.fieldName, type, dlg.var_length, integrity)) {
				DisplayFieldList();
			}
		}
	}

}


void LsiderView::OnFieldModifyfield()
{
	// TODO: �ڴ���������������
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString oldName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hCurrItem);
	CString tbName = m_treectrl->GetItemText(hParentItem);
	HTREEITEM hGrandParentItem = m_treectrl->GetParentItem(hParentItem);
	CString dbName = m_treectrl->GetItemText(hGrandParentItem);
	HTREEITEM hParentParentItem = m_treectrl->GetParentItem(hGrandParentItem);
	if (hParentParentItem != NULL || hGrandParentItem == NULL || hParentItem == NULL) {
		MessageBox(L"��ѡ����ȷ���ֶ����ƣ�", L"��ʾ", MB_OK);
	}
	else {
		FieldLogic logic;
		vector<CFieldEntity>list = logic.GetFieldList(dbName, tbName);
		int oldtype = 0;
		int length = 256;
		for (int i = 0; i < list.size(); i++)
		{
			CString a = CharHelper::ToString(list[i].GetBlock().name, sizeof(VARCHAR));
			if (a.CompareNoCase(oldName) == 0) {
				oldtype = list[i].GetBlock().type;
				length = list[i].GetBlock().param;
			}

		}
		alterFieldView dlg = new alterFieldView();
		dlg.typenum = oldtype;
		dlg.var_length = length;
		int nRes = dlg.DoModal();
		CString newField = dlg.newfieldname;
		if (nRes == IDOK) {
			if (dlg.changename == TRUE) {
				AlterFieldName(dlg.newfieldname);
			}
			if (dlg.changetype == TRUE) {
				int length = dlg.var_length;
				AlterFieldType(length);
			}
		}
	}
}


//�õ���ǰ��ѡ������ݿ���
CString LsiderView::GetSelectedDBName()
{
	if (m_hCurrDBItem) {
		return GetTreeCtrl().GetItemText(m_hCurrDBItem);
	}
	else {
		//�����ǰû��ѡ�����ݿ⣬�򷵻ص�һ�����ݿ���
		return GetTreeCtrl().GetItemText(m_treectrl->GetRootItem());
	}
}

void LsiderView::OnTableCreatetable()
{
	TBView dlg = new TBView;
	int  nRes=dlg.DoModal();
	// TODO: �ڴ���������������
	CString newtable = dlg.tbName;
	if (nRes == IDOK) {
		if (CreateTable(newtable)) {
			DisplayTableList();
		}
	}
}


void LsiderView::OnDatabaseOpendatabase()
{
	// TODO: �ڴ���������������
	DisplayTableList();
}


void LsiderView::OnTableOpentable()
{
	// TODO: �ڴ���������������
	DisplayFieldList();
}


void LsiderView::OnFieldDropfield()
{
	// TODO: �ڴ���������������
	HTREEITEM hCurrItem = m_treectrl->GetSelectedItem();
	CString oldName = m_treectrl->GetItemText(hCurrItem);
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hCurrItem);
	CString tbName = m_treectrl->GetItemText(hParentItem);
	HTREEITEM hGrandParentItem = m_treectrl->GetParentItem(hParentItem);
	CString dbName = m_treectrl->GetItemText(hGrandParentItem);
	HTREEITEM hParentParentItem = m_treectrl->GetParentItem(hGrandParentItem);

	if (hParentParentItem != NULL || hGrandParentItem == NULL || hParentItem == NULL) {
		MessageBox(L"��ѡ����ȷ���ֶ����ƣ�", L"��ʾ", MB_OK);
	}
	else {
		UpdateData(FALSE);
		CFieldEntity* field = new CFieldEntity();
		field->setFieldName(oldName);
		FileLogic filelogic;
		//tDao.MinusFieldNum(filelogic.GetTableFile(tbName), tbName, *field);
		// get selected item
		HTREEITEM selectItem;
		if ((selectItem = GetSelectItem()) == NULL)
			return;
		// get current table & resume its fields
		CTablEntity curTable = GetSelectedTable(selectItem);
		TableDao tDao;
		FileLogic fileLogic;
		FileLogic f;
		CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
		tDao.ResumeFieldsIntable(TdfPath, curTable);
		// get all old records
		RECORDARR records;
		RecordLogic recordLogic;
		recordLogic.SelectAll(dbName, curTable, records);

		FieldLogic fieldLogic;
		try {
			if (fieldLogic.getField(dbName, tbName, oldName) == false) {
				throw new CAppException(_T("Failed to delete field!"));
			}
			else {
				m_treectrl->DeleteItem(hCurrItem);
			}
		}
		catch (CAppException *e) {
			e->GetErrorMessage();
			//		throw e;
			delete e;
		}

		// update table file
		curTable.deleteField(*field);
		CString tableFile = fileLogic.GetTableFile(dbName);
		if (tDao.AlterTable(tableFile, curTable) == false)
			return;
		// update record file

		for (int i = 0; i < records.GetSize(); i++)
		{
			records.GetAt(i)->deleteField(oldName);
		}
		recordLogic.Rewrite(curTable, records);

		FreshListControl(dbName, curTable);
	}
	
}

/*
void LsiderView::OnTestTestlogin()
{
	// TODO: �ڴ���������������
	LoginView dlg;
	dlg.DoModal();
}*/


void LsiderView::OnRecordInsertrecord()
{
	// TODO: �ڴ���������������

	HTREEITEM selectItem;
	if ((selectItem = GetSelectItem()) == NULL)
		return;

	CTablEntity curTable = GetSelectedTable(selectItem);
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(selectItem));
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);
	CString tbName = m_treectrl->GetItemText(selectItem);

	IntegrityLogic integrity;
	RecordDlg dlg = new RecordDlg;
	dlg.setTable(curTable);
	int res = dlg.DoModal();
	bool isok = true;
	CString fieldName;
	if (res == IDOK)
	{
		CRecordEntity newRecord = dlg.GetNewRecord();
		CRecordEntity freshRecord;
		if (m_treectrl->ItemHasChildren(selectItem)) {
			HTREEITEM hChildItem = m_treectrl->GetChildItem(selectItem);

			while (hChildItem != NULL)
			{
				fieldName = m_treectrl->GetItemText(hChildItem);
				isok = checkall(dbName, tbName, fieldName, newRecord.get(fieldName));
				if (isok == false) {
					return;
				}
				if (newRecord.get(fieldName) == _T("")) {
					if (integrity.isDefaultKey(dbName, tbName, fieldName) == TRUE) {
						freshRecord.put(fieldName, integrity.getDefaultValue(dbName, tbName, fieldName));
					}
				}
				else
					freshRecord.put(fieldName, newRecord.get(fieldName));
				hChildItem = m_treectrl->GetNextSiblingItem(hChildItem);
			}
		}
		if (isok == true) {
			RecordLogic recordLogic;
			recordLogic.Insert(dbName, curTable, freshRecord);
		}
	}
	
	FreshListControl(dbName, curTable);
}

CTablEntity LsiderView::GetSelectedTable(HTREEITEM hselectItem)
{
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(hselectItem));

	TableLogic tbLogic;
	vector<CTablEntity> tables = tbLogic.getTableList(dbName);
	CTablEntity *p_curTable = NULL;

	for (int i = 0; i < tables.size(); i++)
	{
		if (tables.at(i).getTableName() == m_treectrl->GetItemText(hselectItem))
		{
			p_curTable = &tables.at(i);
			break;
		}
	}

	curtb_inTreeCtrl = *p_curTable;
	curDBName = dbName;

	return *p_curTable;
}

HTREEITEM LsiderView::GetSelectItem()
{
	HTREEITEM hSelectItem = m_treectrl->GetSelectedItem();
	HTREEITEM hParentItem = m_treectrl->GetParentItem(hSelectItem);
	if (hParentItem == NULL) //select a db
	{
		MessageBox(_T("��ȷ�ϴ������ݿⲢѡ����һ�����һ��.=)"), _T("Oooops"), MB_ICONWARNING | MB_OK);
		return NULL;
	}
	if (m_treectrl->GetParentItem(hParentItem) != NULL) //select a field
		hSelectItem = hParentItem;

	return hSelectItem;
}

void LsiderView::GetListControl()
{
	//Get list control
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	MainView *pView = (MainView*)pMainFrame->m_mainview;
	pView->setListStyle();
	m_listctrl = pView->m_listCtrl;
}

void LsiderView::FreshListControl(CString dbname, CTablEntity & curtable)
{
	RECORDARR records;
	RecordLogic recordLogic;
	recordLogic.SelectAll(dbname, curtable, records);
	CFieldEntity *oneField;
	CString value, fieldName;
	GetListControl(); // get list control
					  // clear list control
	m_listctrl->DeleteAllItems();
	while (m_listctrl->DeleteColumn(0));
	// insert column name
	for (int col = 0; col < curtable.getFieldNum(); col++)
	{
		oneField = curtable.getField(col);
		fieldName = oneField->getFieldName();
		m_listctrl->InsertColumn(col, fieldName, LVCFMT_LEFT, 100);
	}
	// insert item
	for (int row = 0; row < records.GetSize(); row++)
	{
		for (int col = 0; col < curtable.getFieldNum(); col++)
		{
			oneField = curtable.getField(col);
			fieldName = oneField->getFieldName();
			value = records.GetAt(row)->get(fieldName);
			if (col == 0)
				m_listctrl->InsertItem(row, value);
			else
				m_listctrl->SetItemText(row, col, value);
		}
	}
}

void LsiderView::OnRecordSelectrecord()
{
	// TODO: �ڴ���������������

	HTREEITEM selectItem;
	if ((selectItem = GetSelectItem()) == NULL)
		return;

	CTablEntity curTable = GetSelectedTable(selectItem);
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(selectItem));
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);

	FreshListControl(dbName, curTable);
}

void LsiderView::OnRecordUpdaterecord()
{
	// TODO: �ڴ���������������

	HTREEITEM selectItem;
	if ((selectItem = GetSelectItem()) == NULL)
		return;

	CTablEntity curTable = GetSelectedTable(selectItem);
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(selectItem));
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);

	RecordLogic rLogic;
	RECORDARR newRecords;
	rLogic.SelectAll(dbName, curTable, newRecords);

	UpdateRecordView dlg = new UpdateRecordView;
	dlg.setTable(curTable);
	dlg.setNewRecords(newRecords);
	int res = dlg.DoModal();

	if (res == IDOK)
	{
		//integrity constraint
		bool isok = true;
		CString fieldName;
		for (int j = 0; j < curTable.getRecordNum(); j++)
		{
			for (int i = 0; i < curTable.getFieldNum(); i++)
			{
				//check primary key integrity and not null integrity
				fieldName = curTable.getField(i)->getFieldName();
				isok = updatecheckall(j,dbName, curTable.getTableName(), fieldName, newRecords.GetAt(j)->get(fieldName));
				if (isok == false)
					return;
			}
		}

		rLogic.Update(dbName, curTable, newRecords);
	}

	FreshListControl(dbName, curTable);
}


void LsiderView::OnFieldShowfield()
{
	// TODO: �ڴ���������������
	AfxMessageBox(_T("test"), MB_OK);
}

//�޸����ݿ���
void LsiderView::AlterDatabase(CString olddbname, CString newdbname) {
	DBLogic m_logic;
	if (!m_logic.ModifyDatabase(olddbname, newdbname)) {
		AfxMessageBox(_T("�޸����ݿ������ɹ�!"), MB_OK);
	}
	else {
		AfxMessageBox(_T("�޸����ݿ����ɹ���"), MB_OK);
	}

}
void LsiderView::OnDatabaseModifydatabase()
{
	// TODO: �ڴ���������������
	AlterDatabaseView dlg = new AlterDatabaseView;
	int nRes = dlg.DoModal();
	if (nRes == IDOK) {
		AlterDatabase(dlg.oldDBName, dlg.newDBName);
	}
	this->DisplayDBList();
}

//ɾ�����ݿ�
void LsiderView::DeleteDatabase(CString dbname) {
	DBLogic m_logic;
	if (!m_logic.DeleteDatabase(dbname)) {
		AfxMessageBox(_T("ɾ�����ݿ�ʧ��!"), MB_OK);
	}
	else {
		AfxMessageBox(_T("ɾ�����ݿ�ɹ�!"), MB_OK);
	}
}

void LsiderView::OnDatabaseDeletedatabase()
{
	// TODO: �ڴ���������������
	DeleteDatabaseView dlg = new DeleteDatabaseView;
	int nRes = dlg.DoModal();
	if (nRes == IDOK) {
		DeleteDatabase(dlg.dbname);
	}
	this->DisplayDBList();
}

void LsiderView::DeleteTable(CString dbname, CString tbname) {
	TableLogic m_logic;
	if (!m_logic.DeleteTable(dbname, tbname)) {
		AfxMessageBox(_T("ɾ����ʧ��", MB_OK));
	}
	else {
		AfxMessageBox(_T("ɾ����ɹ�", MB_OK));
	}
}

void LsiderView::OnTableDroptable32785()
{
	// TODO: �ڴ���������������
	DeleteTableView dlg = new DeleteTableView;
	int nRes = dlg.DoModal();
	if (nRes == IDOK) {
		DeleteTable(dlg.dbname, dlg.tbname);
	}
	this->DisplayTableList();
}

void LsiderView::AlterTable(CString dbname, CString oldtbname, CString newtbname) {
	TableLogic m_logic;
	if (!m_logic.ModifyTable(dbname, oldtbname, newtbname)) {
		AfxMessageBox(_T("�޸ı�ʧ��!"), MB_OK);
	}
	else {
		AfxMessageBox(_T("�޸ı�ɹ�!"), MB_OK);
	}
}

void LsiderView::OnTableAltertable()
{
	// TODO: �ڴ���������������
	AlterTableView dlg = new AlterTableView;
	int nRes = dlg.DoModal();
	if (nRes == IDOK) {
		AlterTable(dlg.dbname, dlg.oldtbname, dlg.newtbname);
	}
	this->DisplayTableList();
}

bool LsiderView::checkPrimaryKey(const CString NAME, const CString newvalue) {
	HTREEITEM selectItem;
	if ((selectItem = GetSelectItem()) == NULL)
		return false;
	int nCol = 0;
	bool find = false;
	CTablEntity curTable = GetSelectedTable(selectItem);
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(selectItem));
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);
	RECORDARR allRecords;
	RecordLogic recordLogic;
	recordLogic.SelectAll(dbName, curTable, allRecords); //return false?
	CRecordEntity* oneRecord;
	for (int i = 0; i < allRecords.GetSize(); i++)
	{
		oneRecord = allRecords.GetAt(i);
		CString re = oneRecord->get(NAME);
		if (re.CompareNoCase(newvalue) == 0) {
			AfxMessageBox(_T("����ֵ�����ظ�!"), MB_OK);
			return false;
			break;
		}
	}
	return true;
}
bool LsiderView::checkPrimaryKey2(int num,const CString NAME, const CString newvalue) {
	HTREEITEM selectItem;
	if ((selectItem = GetSelectItem()) == NULL)
		return false;
	int nCol = 0;
	bool find = false;
	CTablEntity curTable = GetSelectedTable(selectItem);
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(selectItem));
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);
	RECORDARR allRecords;
	RecordLogic recordLogic;
	recordLogic.SelectAll(dbName, curTable, allRecords); //return false?
	CRecordEntity* oneRecord;
	for (int i = 0; i < allRecords.GetSize()&&i!=num; i++)
	{
		oneRecord = allRecords.GetAt(i);
		CString re = oneRecord->get(NAME);
		if (re.CompareNoCase(newvalue) == 0) {
			AfxMessageBox(_T("����ֵ�����ظ�!"), MB_OK);
			return false;
			break;
		}
	}
	return true;
}
bool LsiderView::checkall(const CString dbName, const CString tbName, const CString fieldName, const CString newvalue) {
	IntegrityLogic integrity;
	if (integrity.isPrimaryKey(dbName, tbName, fieldName) == TRUE) {
		if (checkPrimaryKey(fieldName, newvalue) == false)
			return false;
		if (newvalue == _T("")) {
			return false;
		}
	}
	if (integrity.isPrimaryKey(dbName, tbName, fieldName) == TRUE) {
		if (integrity.isDefaultKey(dbName, tbName, fieldName) == TRUE&&newvalue == _T("")) {
			CString fresh = integrity.getDefaultValue(dbName, tbName, fieldName);
			if (checkPrimaryKey(fieldName, fresh) == false) {
				return false;
			}
		}

	}
	if (integrity.isNotNullKey(dbName, tbName, fieldName) == TRUE) {
		if (newvalue == _T("")) {
			AfxMessageBox(_T("��ֵ����Ϊ��!"), MB_OK);
			return false;
		}
	}
	return true;
}


bool LsiderView::updatecheckall(int number,const CString dbName, const CString tbName, const CString fieldName, const CString newvalue) {
	IntegrityLogic integrity;
	if (integrity.isPrimaryKey(dbName, tbName, fieldName) == TRUE) {
		if (checkPrimaryKey2(number,fieldName, newvalue) == false)
			return false;
	}
	if (integrity.isNotNullKey(dbName, tbName, fieldName) == TRUE) {
		if (newvalue == _T("")) {		
				AfxMessageBox(_T("��ֵ����Ϊ��!"), MB_OK);
				return false;
		}
	}
	return true;
}


void LsiderView::OnDatabaseBackupdatabase()
{
	// TODO: �ڴ���������������
	CString m_FileDir;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	BOOL bRet = FALSE;
	TCHAR szFolder[MAX_PATH];
	//szFolder[0] = _T('/0');
	memset(szFolder, '\0', sizeof(szFolder));
	if (pidl)
	{
		if (SHGetPathFromIDList(pidl, szFolder))
			bRet = TRUE;
		IMalloc *pMalloc = NULL;
		if (SUCCEEDED(SHGetMalloc(&pMalloc)) && pMalloc)
		{
			pMalloc->Free(pidl);
			pMalloc->Release();
		}
	}
	m_FileDir = szFolder;//ѡ����ļ���·��
	if (m_FileDir != L"")
	{
		DBLogic dbLogic;
		if (dbLogic.BackupDatabase(GetSelectedDBName(), m_FileDir))
			MessageBox(L"���ݳɹ���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		else
			MessageBox(L"����ʧ�ܣ�", L"��ʾ", MB_OK | MB_ICONWARNING);
	}

}


void LsiderView::OnRecordDetailedselect()
{
	// TODO: �ڴ���������������
	HTREEITEM selectItem;
	if ((selectItem = GetSelectItem()) == NULL)
		return;

	CTablEntity curTable = GetSelectedTable(selectItem);
	CString dbName = m_treectrl->GetItemText(m_treectrl->GetParentItem(selectItem));
	TableDao tbDao;
	FileLogic f;
	CString TdfPath = f.GetFieldFile(dbName, curTable.getTableName());
	tbDao.ResumeFieldsIntable(TdfPath, curTable);
	SelectView dlg = new SelectView;
	dlg.setDBName(dbName);
	dlg.setTable(curTable);
	RECORDARR allRecords;
	dlg.setRecord(allRecords);
	int nRes = dlg.DoModal();
	if (nRes == IDOK) {
		//Get list control
		CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
		MainView *pView = (MainView*)pMainFrame->m_mainview;
		pView->setListStyle();
		m_listctrl = pView->m_listCtrl;

		m_listctrl->DeleteAllItems();
		while (m_listctrl->DeleteColumn(0));
		if (m_treectrl->ItemHasChildren(selectItem))
		{
			HTREEITEM hChildItem = m_treectrl->GetChildItem(selectItem);
			int nCol = 0, nItem = 0;
			CString fieldName;

			while (hChildItem != NULL)
			{
				fieldName = m_treectrl->GetItemText(hChildItem);
				m_listctrl->InsertColumn(nCol, fieldName, LVCFMT_LEFT, 100);
				//make a loop to insert all the records under one field name
				CRecordEntity* oneRecord;
				
				//RECORDARR* allRecords = dlg.getRecord();
				for (int i = 0; i < allRecords.GetSize(); i++)
				{
					oneRecord = allRecords.GetAt(i);
					if (nCol == 0)
						m_listctrl->InsertItem(i, oneRecord->get(fieldName));
					else
						m_listctrl->SetItemText(i, nCol, oneRecord->get(fieldName));
				}
				hChildItem = m_treectrl->GetNextSiblingItem(hChildItem);
				nCol++;
			}
		}
	}
}


void LsiderView::OnSystemLooklogfile()
{
	// TODO: �ڴ���������������
	LogLogic logic;
	logic.LookLogFile();
}
