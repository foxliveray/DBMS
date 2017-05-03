#pragma once


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
};


