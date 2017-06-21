#pragma once
#include<cstring>
#include<winbase.h>
#include<cstringt.h>
#include <afx.h>
class CAppException
{
public:
	CAppException(void);
	CAppException(CString strError);
	~CAppException();
	CString GetErrorMessage();

private:
	CString Error;
	int Code;
};

