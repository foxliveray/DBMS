#pragma once
#include <comutil.h>

class TimeHelper
{
public:
	static SYSTEMTIME ToSystemTime(CString strTime);
};