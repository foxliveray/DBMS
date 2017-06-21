#include "stdafx.h"
#include "AppException.h"

CAppException::CAppException(void)
{
	Error = _T("");
	Code = 0;
}

CAppException::CAppException(CString strError)
{
	Error = strError;
	Code = 404;
}


CAppException::~CAppException()
{
}

CString CAppException::GetErrorMessage()
{
	return Error;
}
