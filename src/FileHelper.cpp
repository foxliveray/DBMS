#include "stdafx.h"
#include "FileHelper.h"
#include <fileapi.h>


//�����ļ�
bool FileHelper::CreateFile(const CString fileName)
{
	try {
		//�����ļ���
		for (int i = 0; i < fileName.GetLength(); i++)
		{
			if ((fileName.GetAt(i) == _T('/') || fileName.GetAt(i) == _T('\\')) && i != 2)
			{
				CString fileDirectory;
				fileDirectory = fileName.Left(i);
				if (!CreateDirectory(fileDirectory, NULL) && GetLastError() != 183)
					return false;
			}
		}

		//�����ļ�
		CFile newFile;
		if (!newFile.Open(fileName, CFile::modeCreate))
			return false;
		newFile.Close();

		return true;
	}
	//�쳣���������ļ�ʧ��
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to create file!"));
	}
	return false;

}

//�ж��ļ��Ƿ�Ϸ�
bool FileHelper::IsVaildFile(const CString fileName)
{
	try {
		CFileFind finder;
		bool isFileExist = finder.FindFile(fileName);
		return isFileExist;
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to open file"));
	}

	return false;
}

//ɾ���ļ����Լ��ļ����µ��ļ�
bool FileHelper::DeleteFolder(CString &folderName) {
	//CFileFind finder;
	//CString path;
	//path.Format(_T("%s\\*.*"), folderName);			//��Ŀ¼�µĵ�һ���ļ�
	//BOOL bFound = finder.FindFile(path);
	//while (bFound) {			//����ҵ��˵�һ���ļ��������Ѱ��
	//	if (finder.IsDirectory() && finder.IsDots()) {		//��������һ��Ŀ¼��Ȼ��ȥ����."��".."Ŀ¼
	//		DeleteFolder(finder.GetFilePath());		//�ݹ���һ���ļ���
	//		RemoveDirectory(finder.GetFilePath());		//ɾ���ļ���
	//	}
	//	else {
	//		DeleteFile(finder.GetFilePath());		//ɾ���ļ�
	//	}
	//	bFound = finder.FindNextFile();		//����һ���ļ�
	//}
	//if (!RemoveDirectory(folderName)) {
	//	return false;
	//}

	//return true;

	CFileFind ff;
	BOOL bFound;
	bFound = ff.FindFile(folderName + "\\*.*");		//��Ŀ¼�µĵ�һ���ļ�
	while (bFound)
	{
		bFound = ff.FindNextFile();		//����ҵ��˵�һ���ļ��������Ѱ��
		CString sFilePath = ff.GetFilePath();

		if (ff.IsDirectory())
		{
			if (!ff.IsDots())			//��������һ��Ŀ¼��Ȼ��ȥ����."��".."Ŀ¼
			{
				DeleteFolder(sFilePath);		//�ݹ���һ���ļ���
			}
		}
		else
		{
			if (ff.IsReadOnly())
			{
				SetFileAttributes(sFilePath, FILE_ATTRIBUTE_NORMAL);
			}
			DeleteFile(sFilePath);		//ɾ���ļ�
		}
	}
	ff.Close();
	//�����Ѿ����ļ���������ļ�ȫ��ɾ���ˣ������Ҫ���ļ���Ҳɾ���������һ�´���  
	SetFileAttributes(folderName, FILE_ATTRIBUTE_NORMAL);  //�����ļ��е�����  
	RemoveDirectory(folderName);  //ɾ���ļ���  

	return true;
}

//�޸��ļ�����
bool FileHelper::ModifyFolderName(CString &oldname, CString &newname)
{
	//���ļ���һ���ļ��п�������һ���ļ����У�ͬʱɾ��Դ�ļ����е�����

	if (MoveFile(oldname, newname)==0) {			//���ɹ��ƶ����򷵻�0
		return false;
	}
	else {
		return true;
	}
}

//�޸��ļ���
bool FileHelper::ModifyFileName(CString &oldname, CString &newname) {
	try {
		CFile::Rename(oldname, newname);
	}
	catch (CException *e) {
		e->Delete();
		return false;
	}
	return true;
}
void FileHelper::CopyDirectory(CString source, CString target)
{
	CreateDirectory(target, NULL); //����Ŀ���ļ���   
								   //AfxMessageBox("�����ļ���"+target);   
	CFileFind finder;
	CString path;
	path.Format(L"%s/*.*", source);
	bool bWorking = finder.FindFile(path);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory() && !finder.IsDots())
		{ //���ļ��� ���� ���Ʋ��� . �� ..   
			CopyDirectory(finder.GetFilePath(), target + "/" + finder.GetFileName()); //�ݹ鴴���ļ���+"/"+finder.GetFileName()   
		}
		else
		{ //���ļ� ��ֱ�Ӹ���    
			CopyFile(finder.GetFilePath(), target + "/" + finder.GetFileName(), FALSE);
		}
	}
}