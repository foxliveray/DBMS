#include "stdafx.h"
#include "CharHelper.h"
#include<string.h>

CharHelper::CharHelper()
{
}


CharHelper::~CharHelper()
{
}

//��CString����ת��Ϊchar*����
void CharHelper::ToChars(char* p, CString s, const int nSize) {

	//��ʼ��ָ��pָ����ַ����Ŀռ�
	memset(p, 0, nSize);
	//����ַ���s��ָ��(�ÿ��ַ����������գ�
	wchar_t* pSrc = s.GetBuffer(s.GetLength()+1);
	//����ַ���pSrc�ĳ���
	int nLen = ::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);		//����cchWideChar����Ϊ0�����Ի�ȡת������Ľ��ջ�������С��
	//�����ֽ�������̬�����ڴ�
	char *pBuf = new char[nLen];
	//�����ַ�ת��Ϊ���ֽ��ַ���
	::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, pBuf, nLen, NULL, NULL);

	if (nLen > nSize) {
		nLen = nSize;
	}

	for (int i = 0; i < nLen; i++) {
		*(p + i) = *(pBuf + i);
	}

	//�ͷŻ���
	s.ReleaseBuffer();
	//�ͷŶ�̬������ڴ�
	delete[] pBuf;
}

//��ϵͳʱ�䣨SYSTEMTIME������ת����char*����
void CharHelper::ToChars(char* p, SYSTEMTIME t, const int nSize) {
	char* time = (char*)&t;	//ȡ��ַ��ֵ��ָ��
	for (int i = 0; i < nSize; i++) {
		*p++ = *time++;
	}
}

//��bool����ת��Ϊchar*����
void CharHelper::ToChars(char* p, bool b, const int nSize) {
	char* bo = (char*)&b;
	for (int i = 0; i < nSize; i++) {
		*p++ = *bo++;
	}
}

//��int����ת��Ϊchar*����
void CharHelper::ToChars(char* p, int in, const int nSize) {
	char* s = (char*)&in;
	for (int i = 0; i < nSize; i++)
	{
		*p++ = *s++;
	}
}

//��double����ת��Ϊchar*����
void CharHelper::ToChars(char* p, double d, const int nSize) {
	char* s = (char*)&d;
	for (int i = 0; i < nSize; i++)
	{
		*p++ = *s++;
	}
}

//��char*����ת��ΪCString����
CString CharHelper::ToString(char* p, const int nSize) {
	//�����ַ�����
	char *pBuf = new char[nSize + 1];
	for (int i = 0; i < nSize; i++) {
		*(pBuf + i) = *(p + i);
	}
	pBuf[nSize] = NULL; //����ַ��������Կ��ַ���ֹ��cchMultiByte��������Ϊ-1����ʧ�ܣ����ܳɹ�

	//�����ֽ��ַ���ת��Ϊ���ַ���
	int nLen = ::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, NULL, 0); // cchWideChar��������Ϊ0����������ִ��ת�������Ƿ���Ŀ�껺��lpWideChatStr����Ŀ��ַ���
	wchar_t* WideBuf = new wchar_t[nLen+1];
	memset(WideBuf, 0, (nLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, (LPWSTR)WideBuf, nLen);

	//����һ���ַ�������
	CString str(WideBuf);

	//�ͷŶ�̬������ڴ�
	delete[] WideBuf;
	delete[] pBuf;

	return str;
}

//�����ַ�����
void CharHelper::Copy(char* p, char* pSrc, const int nSize) {
	for (int i = 0; i < nSize; i++)
	{
		*(p + i) = *(pSrc + i);
	}
}