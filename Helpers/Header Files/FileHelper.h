//文件操作辅助类FileHelper定义文件
#pragma once

class FileHelper
{
public:
	static bool CreateFile(const CString fileName);       //创建文件
	static bool IsVaildFile(const CString fileName);      //判断文件是否合法

};
