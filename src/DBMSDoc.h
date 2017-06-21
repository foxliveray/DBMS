#pragma once

#include "CDBEntity.h"
#include "DBView.h"
#include "DBLogic.h"
#include "AppException.h"
// DBMSDoc 文档

class DBMSDoc : public CDocument
{ 
	DECLARE_DYNCREATE(DBMSDoc)

public:
	DBMSDoc();
	virtual ~DBMSDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // 为文档 I/O 重写
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

private:
	CString m_strError;		//定义异常信息
	//CDBEntity m_DBEntity;		//定义一个数据库实体对象

public:
	CString GetError();					//获取异常信息
	void SetError(CString strError);	//设置异常信息
	DECLARE_MESSAGE_MAP()
};
