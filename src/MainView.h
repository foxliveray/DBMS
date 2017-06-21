#pragma once
#include"global.h"
#include"DBView.h"
#include"DataStructure.h"
#include"CDBEntity.h"
#include"FieldView.h"
// MainView 视图

class MainView : public CListView
{
	DECLARE_DYNCREATE(MainView)

protected:
	MainView();           // 动态创建所使用的受保护的构造函数
	virtual ~MainView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl *m_listCtrl;
	CTreeCtrl *m_treeCtrl;//
	void setListStyle();

private:
	CTreeCtrl* GetTreeControl();
public:
	afx_msg void OnRecordDeleterecord();
};


