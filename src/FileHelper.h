#pragma once
#include "AppException.h"
class FileHelper
{
public:
	static bool CreateFile(const CString fileName);       //�����ļ�
	static bool IsVaildFile(const CString fileName);      //�ж��ļ��Ƿ�Ϸ�
	bool DeleteFolder(CString &folderName);		//ɾ���ļ���
	bool ModifyFolderName(CString &oldname, CString &newname);	//�޸��ļ�����
	bool ModifyFileName(CString &oldname, CString &newname);		//�޸��ļ���
	void CopyDirectory(CString source, CString target);
};

