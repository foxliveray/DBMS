#pragma once
class CharHelper
{
public:
	CharHelper();
	~CharHelper();
	//��CString����ת��Ϊchar*����
	static void ToChars(char* p, CString s, const int nSize);
	//��ϵͳʱ�䣨SYSTEMTIME������ת����char*����
	static void ToChars(char* p, SYSTEMTIME t, const int nSize);
	//��bool����ת��Ϊchar*����
	static void ToChars(char* p, bool b, const int nSize);
	//��int����ת��Ϊchar*����
	static void ToChars(char* p, int in, const int nSize);
	//��double����ת��Ϊchar*����
	static void ToChars(char* p, double d, const int nSize);
	//��char*����ת��ΪCString����
	static CString ToString(char* p, const int nSize);
	//�����ַ�����
	static void Copy(char* p, char* pSrc, const int nSize);
};

