#include"stdafx.h"
#include "LogLogic.h"

LogLogic::LogLogic()
{
}

LogLogic::~LogLogic()
{
}

bool LogLogic::VerifyLogin(const CString username, const CString pwd)
{
	return logdao.VerifyLogin(username, pwd, flogic.GetLoginFile());
}

bool LogLogic::Register(const CString username, const CString pwd)
{
	return logdao.Register(username, pwd, flogic.GetLoginFile());
}

bool LogLogic::WriteLogs(CString loginfo) {
	CString str = _T("");
	str += logdao.ReadCurUserName(flogic.GetTempUsernameFile());
	str += CString("	") + loginfo;
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CTime t(time);
	CString currentTime = t.Format("%Y-%m-%d %H:%M:%S");
	str += CString("	") + currentTime;
	return logdao.WriteLog(str, flogic.GetLogFile());
}

void LogLogic::LookLogFile() {
	CString path = flogic.GetLogFile();
	logdao.LookLogFile(path);
}