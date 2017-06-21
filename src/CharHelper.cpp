#include "stdafx.h"
#include "CharHelper.h"
#include<string.h>

CharHelper::CharHelper()
{
}


CharHelper::~CharHelper()
{
}

//将CString类型转化为char*类型
void CharHelper::ToChars(char* p, CString s, const int nSize) {

	//初始化指针p指向的字符串的空间
	memset(p, 0, nSize);
	//获得字符串s的指针(用宽字符类型来接收）
	wchar_t* pSrc = s.GetBuffer(s.GetLength()+1);
	//获得字符串pSrc的长度
	int nLen = ::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);		//设置cchWideChar参数为0（用以获取转换所需的接收缓冲区大小）
	//根据字节数来动态分配内存
	char *pBuf = new char[nLen];
	//将宽字符转换为多字节字符串
	::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, pBuf, nLen, NULL, NULL);

	if (nLen > nSize) {
		nLen = nSize;
	}

	for (int i = 0; i < nLen; i++) {
		*(p + i) = *(pBuf + i);
	}

	//释放缓存
	s.ReleaseBuffer();
	//释放动态分配的内存
	delete[] pBuf;
}

//将系统时间（SYSTEMTIME）类型转换成char*类型
void CharHelper::ToChars(char* p, SYSTEMTIME t, const int nSize) {
	char* time = (char*)&t;	//取地址赋值给指针
	for (int i = 0; i < nSize; i++) {
		*p++ = *time++;
	}
}

//将bool类型转化为char*类型
void CharHelper::ToChars(char* p, bool b, const int nSize) {
	char* bo = (char*)&b;
	for (int i = 0; i < nSize; i++) {
		*p++ = *bo++;
	}
}

//将int类型转化为char*类型
void CharHelper::ToChars(char* p, int in, const int nSize) {
	char* s = (char*)&in;
	for (int i = 0; i < nSize; i++)
	{
		*p++ = *s++;
	}
}

//将double类型转化为char*类型
void CharHelper::ToChars(char* p, double d, const int nSize) {
	char* s = (char*)&d;
	for (int i = 0; i < nSize; i++)
	{
		*p++ = *s++;
	}
}

//将char*类型转化为CString类型
CString CharHelper::ToString(char* p, const int nSize) {
	//拷贝字符数组
	char *pBuf = new char[nSize + 1];
	for (int i = 0; i < nSize; i++) {
		*(pBuf + i) = *(p + i);
	}
	pBuf[nSize] = NULL; //如果字符串不是以空字符中止，cchMultiByte参数设置为-1可能失败，可能成功

	//将多字节字符串转换为宽字符型
	int nLen = ::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, NULL, 0); // cchWideChar参数设置为0，函数不会执行转换，而是返回目标缓存lpWideChatStr所需的宽字符数
	wchar_t* WideBuf = new wchar_t[nLen+1];
	memset(WideBuf, 0, (nLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, (LPWSTR)WideBuf, nLen);

	//构造一个字符串对象
	CString str(WideBuf);

	//释放动态分配的内存
	delete[] WideBuf;
	delete[] pBuf;

	return str;
}

//拷贝字符数组
void CharHelper::Copy(char* p, char* pSrc, const int nSize) {
	for (int i = 0; i < nSize; i++)
	{
		*(p + i) = *(pSrc + i);
	}
}