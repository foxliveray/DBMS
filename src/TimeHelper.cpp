#include "stdafx.h"
#include "TimeHelper.h"

SYSTEMTIME TimeHelper::ToSystemTime(CString strTime)
{
	SYSTEMTIME st;
	memset(&st, 0, sizeof(SYSTEMTIME));

	if (strTime.GetLength() > 0)
	{
		int year = _wtoi(strTime.Left(4));
		int month = _wtoi(strTime.Mid(5, 2));
		int day = _wtoi(strTime.Mid(8, 2));
		int hour = _wtoi(strTime.Mid(11, 2));
		int minute = _wtoi(strTime.Mid(14, 2));
		int second = _wtoi(strTime.Mid(17, 2));
		int millisecond = _wtoi(strTime.Mid(20, 3));

		st.wYear = year;
		st.wMonth = month;
		st.wDay = day;
		st.wHour = hour;
		st.wMinute = minute;
		st.wSecond = second;
		st.wMilliseconds = millisecond;
	}

	return st;
}