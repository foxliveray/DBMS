#pragma once
#include "AppException.h"
class FileHelper
{
public:
	static bool CreateFile(const CString fileName);       //创建文件
	static bool IsVaildFile(const CString fileName);      //判断文件是否合法
	bool DeleteFolder(CString &folderName);		//删除文件夹
	bool ModifyFolderName(CString &oldname, CString &newname);	//修改文件夹名
	bool ModifyFileName(CString &oldname, CString &newname);		//修改文件名
	void CopyDirectory(CString source, CString target);
};

