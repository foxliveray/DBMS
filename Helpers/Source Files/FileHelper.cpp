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
