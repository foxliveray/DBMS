
// DBMS.h : DBMS Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "LoginView.h"

// CDBMSApp:
// �йش����ʵ�֣������ DBMS.cpp
//

class CDBMSApp : public CWinApp
{
public:
	CDBMSApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDBMSApp theApp;
