
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "DBMS.h"
#include "MainFrm.h"
#include "LsiderView.h"
#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//ON_COMMAND(ID_DATABASE_CREATEDATABASE, &CMainFrame::OnDatabaseCreatedatabase)
	//ON_COMMAND(ID_TABLE_CREATETABLE, &CMainFrame::OnTableCreatetable)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//����˽����ͼ��
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	/*
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
	TRACE0("δ�ܴ�����ͼ����\n");
	return -1;
	}*/

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	//m_strTitle = TEXT("Star-DBMS");			//�޸��˽���ı���
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	//����˷ָ�����ʵ�ִ���
	CRect rect;
	GetClientRect(&rect);

	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(LsiderView),
		CSize(200, 0), pContext))
	{
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(MainView),
		CSize(rect.Width() - 200, 0), pContext))
	{
		return FALSE;
	}

	m_lsiderview = (LsiderView*)m_wndSplitter.GetPane(0, 0);
	m_mainview = (MainView*)m_wndSplitter.GetPane(0, 1);

	return TRUE;

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


// MainFrm ��Ϣ�������