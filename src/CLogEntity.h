#pragma once
#include"global.h"
#include"DataStructure.h"
class CLogEntity {
public:
	CLogEntity();
	CLogEntity(const CString logname,const CString logpassword);
	~CLogEntity();
	void setBlock(LoginBlock lb);
	LoginBlock getBlock();
private:
	CString name;
	CString password;
};