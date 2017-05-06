//文件操作辅助类FileHelper实现文件
#include "stdafx.h"
#include <fileapi.h>
#include "FileHelper.h"

//创建文件
bool FileHelper::CreateFile(const CString fileName)
{
	//创建文件夹
	for (int i = 0; i < fileName.GetLength(); i++)
	{
		if (fileName.GetAt(i) == _T('/') || fileName.GetAt(i) == _T('\\'))
		{
			CString fileDirectory;
			fileDirectory = fileName.Left(i);
			if (!CreateDirectory(fileDirectory, NULL))
				return false;
		}
	}

	//创建文件
	CFile newFile;
	if (!newFile.Open(fileName, CFile::modeCreate))
		return false;
	newFile.Close();

	return true;

	//异常处理：创建文件失败
}

//判断文件是否合法
bool FileHelper::IsVaildFile(const CString fileName)
{
	CFileFind finder;
	bool isFileExist = finder.FindFile(fileName);
	return isFileExist;
}
