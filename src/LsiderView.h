#pragma once
#include "DBMSDoc.h"
#include"CFieldEntity.h"
#include "CTableEntity.h"
#include "TableLogic.h"
#include "AlterDatabaseView.h"
#include "DeleteDatabaseView.h"
#include "AlterTableView.h"
#include "DeleteTableView.h"
#include "SelectView.h"
// LsiderView 视图

class LsiderView : public CTreeView
{
	DECLARE_DYNCREATE(LsiderView)

protected:
	LsiderView();           // 动态创建所使用的受保护的构造函数
	virtual ~LsiderView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate();
	bool CreateDatabase(CString dbname);
	bool CreateField(CString fieldName, int type, int length, int integrity);
	//bool  CreateField(CString fieldName, int type, int integrity);
	bool  CreateTable(CString tbname);
	//bool CreateIntegriyies(CString fieldname, int primary, int notnull, int isdefault, CString value);
	void AlterDatabase(CString olddbname, CString newdbname);
	void DeleteDatabase(CString dbname);
	void AlterTable(CString dbname, CString oldtbname, CString newtbname);
	void DeleteTable(CString dbname, CString tbname);
	bool CreateIntegriyies(CString fieldname, int primary, int notnull, int isdefault, CString value);
	bool AlterFieldName(CString fieldName);
	bool AlterFieldType(int newtype);
	void DisplayDBList();	//显示数据库目录
	void LsiderView::DisplayFieldList();
	CString GetSelectedDBName();//得到当前被选择的数据库名

public:
	HTREEITEM m_hCurrDBItem;
	HTREEITEM m_hCurrTBItem;
	TABLEARR m_arrTable;	// Table array
	CTablEntity curtb_inTreeCtrl;
	CString curDBName;

private:
	CImageList m_imageList;
	CTreeCtrl *m_treectrl;
	CListCtrl *m_listctrl;

public:
	afx_msg
		void DisplayTableList();
	void OnDatabaseCreatedatabase();
	afx_msg void OnFieldCreatfield();
	afx_msg void OnFieldModifyfield();
	afx_msg void OnTableDroptable32785();
	afx_msg void OnTableCreatetable();
	afx_msg void OnDatabaseOpendatabase();
	afx_msg void OnTableOpentable();
	afx_msg void OnFieldDropfield();
	//afx_msg void OnTestTestlogin();
	afx_msg void OnRecordInsertrecord();
	CTablEntity GetSelectedTable(HTREEITEM hselectItem);
	HTREEITEM GetSelectItem();
	void GetListControl();
	void FreshListControl(CString dbname, CTablEntity &curtable);
	afx_msg void OnRecordSelectrecord();
	afx_msg void OnFieldShowfield();
	afx_msg void OnDatabaseModifydatabase();
	afx_msg void OnDatabaseDeletedatabase();
	afx_msg void OnTableAltertable();
	bool checkPrimaryKey(const CString NAME, const CString newvalue);
	bool checkPrimaryKey2(int num, const CString NAME, const CString newvalue);
	bool checkall(const CString dbName, const CString tbName, const CString fieldName, const CString newvalue);
	bool updatecheckall(int number, const CString dbName, const CString tbName, const CString fieldName, const CString newvalue);
	afx_msg void OnRecordUpdaterecord();
	afx_msg
	void OnDatabaseBackupdatabase();
	afx_msg void OnRecordDetailedselect();
	afx_msg void OnSystemLooklogfile();
};


