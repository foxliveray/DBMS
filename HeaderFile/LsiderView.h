#pragma once


// LsiderView ��ͼ

class LsiderView : public CTreeView
{
	DECLARE_DYNCREATE(LsiderView)

protected:
	LsiderView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


