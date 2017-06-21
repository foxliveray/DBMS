#pragma once
#include"global.h"
#include"DataStructure.h"
#include"CLogEntity.h"
#include"LogDao.h"
#include"FileLogic.h"
class LogLogic {
public:
	LogLogic();
	~LogLogic();
	bool VerifyLogin(const CString username, const CString pwd);
	bool Register(const CString username, const CString pwd);
	bool WriteLogs(CString loginfo);
	void LookLogFile();
private:
	LogDao logdao;
	FileLogic flogic;
};