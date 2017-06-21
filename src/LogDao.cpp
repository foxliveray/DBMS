#include"stdafx.h"
#include "LogDao.h"
#include"CharHelper.h"
#include<Windows.h>
#include<afxwin.h>
LogDao::LogDao()
{
}

LogDao::~LogDao()
{
}

bool LogDao::VerifyLogin(CString username, CString pwd, CString strFilepath)
{
	vector<CLogEntity> list = ReadLogList(strFilepath);
	try {
		//����ƥ���ļ���
		CString strfieldName = username;
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		bool  Exist = false;
		LoginBlock lbk;
		CLogEntity le;

		file.SeekToBegin();
		while (file.Read(&lbk, sizeof(LoginBlock)) > 0) {
			CString strName = CharHelper::ToString(lbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//������ȫһ��
				CString pass = CharHelper::ToString(lbk.password, sizeof(VARCHAR));
				if (pass.CompareNoCase(pwd) == 0) {
					Exist = true;
				}
				else
					Exist = FALSE;
			}
		}
		file.Close();
		return Exist;
	}
	catch (CException *e) {
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}
}

bool LogDao::HasLogName(CString username, CString strFilepath)
{
	vector<CLogEntity> list = ReadLogList(strFilepath);
	try {
		//����ƥ���ļ���
		CString strfieldName = username;
		if (strfieldName.GetLength() == 0) {
			return false;
		}
		//��ֻ���ķ�ʽ���ļ�
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			return false;
		}

		//��ȡ���ݿ���Ϣ
		bool  Exist = false;
		LoginBlock lbk;
		CLogEntity le;

		file.SeekToBegin();
		while (file.Read(&lbk, sizeof(LoginBlock)) > 0) {
			CString strName = CharHelper::ToString(lbk.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strfieldName) == 0) {//������ȫһ��
				Exist = TRUE;
			}
		}
		file.Close();
		return Exist;
	}
	catch (CException *e) {
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to change the FIELD file!"));
	}
}

bool LogDao::Register(CString username, CString pwd, CString strFilepath)
{
	CLogEntity le(username, pwd);
	bool isExist = FileHelper::IsVaildFile(strFilepath);
	if (isExist == false) {
		FileHelper::CreateFileW(strFilepath);
	}
	bool isHasName = HasLogName(username, strFilepath);
	if (isHasName == true) {
		return false;
	}
	bool isok=WriteUser(username, pwd, strFilepath);
	return isok;
}

vector<CLogEntity> LogDao::ReadLogList(CString strFilepath)
{
	vector <CLogEntity> res;
	try {
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone)==FALSE) {
		}
		LoginBlock lb;

		file.SeekToBegin();
		while (file.Read(&lb, sizeof(LoginBlock)) > 0) {
			CLogEntity cldb;
			cldb.setBlock(lb);
			res.push_back(cldb);
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get all log data!"));
	}

	return res;
}
bool LogDao::WriteUser(CString username, CString pwd,const CString strFilepath) {
	CFile file;
	if (file.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
		return false;
	}

	//��ȡ���ݿ���Ϣ

	file.SeekToEnd();
	CLogEntity le(username, pwd);
	file.Write(&le.getBlock(), sizeof(LoginBlock));
	file.Close();
	return true;
}

bool LogDao::WriteLog(CString loginfo, CString strFilepath) {
	loginfo += "\r\n";
	CFile file;
	if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate) == FALSE) {
		return false;
	}

	file.SeekToEnd();
	int len = loginfo.GetLength() * 2;
	file.Write(loginfo, len);
	file.Close();

	return true;

}

bool LogDao::WriteCurUserName(CString strFilepath, CString username)
{
	//vector<CString> str;
	//str.push_back(username);
	CStdioFile file;
	if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite) == FALSE) {
		return false;
	}
	file.SeekToBegin();
	file.WriteString(username);
	file.Close();

	return true;
}

CString LogDao::ReadCurUserName(CString strFilepath) {
	CStdioFile file;
	if (file.Open(strFilepath, CFile::modeRead) == FALSE) {
		return NULL;
	}
	file.SeekToBegin();
	CString username;
	file.ReadString(username);

	file.Close();
	return username;
}

void LogDao::LookLogFile(CString strFilepath) {
	ShellExecuteW(NULL, CString("open"), strFilepath, NULL, NULL, SW_SHOWNORMAL);
}