#pragma once


// MainView ��ͼ

class MainView : public CView
{
	DECLARE_DYNCREATE(MainView)

protected:
	MainView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MainView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


