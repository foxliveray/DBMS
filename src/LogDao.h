#pragma once
#include "FileHelper.h"
#include "global.h"
#include"CLogEntity.h"
class LogDao {

public:
	LogDao();
	~LogDao();
	bool VerifyLogin(CString username, CString pwd, CString strFilepath);
	bool HasLogName(CString username,CString strFilepath);
	bool Register(CString username, CString pwd, CString strFilepath);
	vector<CLogEntity> ReadLogList(CString strFilepath);
	bool WriteUser(CString username, CString pwd, const CString strFilepath);
	bool WriteLog(CString loginfo, CString strFilepath);
	bool WriteCurUserName(CString strFilepath, CString username);
	CString ReadCurUserName(CString strFilepath);
	void LookLogFile(CString strFilepath);
};