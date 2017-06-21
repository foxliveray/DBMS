#pragma once
class CharHelper
{
public:
	CharHelper();
	~CharHelper();
	//将CString类型转化为char*类型
	static void ToChars(char* p, CString s, const int nSize);
	//将系统时间（SYSTEMTIME）类型转换成char*类型
	static void ToChars(char* p, SYSTEMTIME t, const int nSize);
	//将bool类型转化为char*类型
	static void ToChars(char* p, bool b, const int nSize);
	//将int类型转化为char*类型
	static void ToChars(char* p, int in, const int nSize);
	//将double类型转化为char*类型
	static void ToChars(char* p, double d, const int nSize);
	//将char*类型转化为CString类型
	static CString ToString(char* p, const int nSize);
	//拷贝字符数组
	static void Copy(char* p, char* pSrc, const int nSize);
};

