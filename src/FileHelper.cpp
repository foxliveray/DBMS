#include "stdafx.h"
#include "FileHelper.h"
#include <fileapi.h>


//创建文件
bool FileHelper::CreateFile(const CString fileName)
{
	try {
		//创建文件夹
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

		//创建文件
		CFile newFile;
		if (!newFile.Open(fileName, CFile::modeCreate))
			return false;
		newFile.Close();

		return true;
	}
	//异常处理：创建文件失败
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to create file!"));
	}
	return false;

}

//判断文件是否合法
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

//删除文件夹以及文件夹下的文件
bool FileHelper::DeleteFolder(CString &folderName) {
	//CFileFind finder;
	//CString path;
	//path.Format(_T("%s\\*.*"), folderName);			//找目录下的第一个文件
	//BOOL bFound = finder.FindFile(path);
	//while (bFound) {			//如果找到了第一个文件，则继续寻找
	//	if (finder.IsDirectory() && finder.IsDots()) {		//表明这是一个目录，然后去除“."和".."目录
	//		DeleteFolder(finder.GetFilePath());		//递归下一层文件夹
	//		RemoveDirectory(finder.GetFilePath());		//删除文件夹
	//	}
	//	else {
	//		DeleteFile(finder.GetFilePath());		//删除文件
	//	}
	//	bFound = finder.FindNextFile();		//找下一个文件
	//}
	//if (!RemoveDirectory(folderName)) {
	//	return false;
	//}

	//return true;

	CFileFind ff;
	BOOL bFound;
	bFound = ff.FindFile(folderName + "\\*.*");		//找目录下的第一个文件
	while (bFound)
	{
		bFound = ff.FindNextFile();		//如果找到了第一个文件，则继续寻找
		CString sFilePath = ff.GetFilePath();

		if (ff.IsDirectory())
		{
			if (!ff.IsDots())			//表明这是一个目录，然后去除“."和".."目录
			{
				DeleteFolder(sFilePath);		//递归下一层文件夹
			}
		}
		else
		{
			if (ff.IsReadOnly())
			{
				SetFileAttributes(sFilePath, FILE_ATTRIBUTE_NORMAL);
			}
			DeleteFile(sFilePath);		//删除文件
		}
	}
	ff.Close();
	//上面已经把文件夹下面的文件全部删除了，如果需要把文件夹也删除掉则加上一下代码  
	SetFileAttributes(folderName, FILE_ATTRIBUTE_NORMAL);  //设置文件夹的属性  
	RemoveDirectory(folderName);  //删除文件夹  

	return true;
}

//修改文件夹名
bool FileHelper::ModifyFolderName(CString &oldname, CString &newname)
{
	//将文件从一个文件夹拷贝到另一个文件夹中，同时删除源文件夹中的内容

	if (MoveFile(oldname, newname)==0) {			//不成功移动，则返回0
		return false;
	}
	else {
		return true;
	}
}

//修改文件名
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
	CreateDirectory(target, NULL); //创建目标文件夹   
								   //AfxMessageBox("创建文件夹"+target);   
	CFileFind finder;
	CString path;
	path.Format(L"%s/*.*", source);
	bool bWorking = finder.FindFile(path);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory() && !finder.IsDots())
		{ //是文件夹 而且 名称不含 . 或 ..   
			CopyDirectory(finder.GetFilePath(), target + "/" + finder.GetFileName()); //递归创建文件夹+"/"+finder.GetFileName()   
		}
		else
		{ //是文件 则直接复制    
			CopyFile(finder.GetFilePath(), target + "/" + finder.GetFileName(), FALSE);
		}
	}
}