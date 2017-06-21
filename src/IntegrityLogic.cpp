#include "stdafx.h"
#include "IntegrityLogic.h"

IntegrityLogic::IntegrityLogic()
{
}

IntegrityLogic::~IntegrityLogic()
{
}

bool IntegrityLogic::createIntegrity(const CString dbName, const CString tbName, CIntegrityEntity & fd)
{
	try {
		//�жϸ��ļ��Ƿ���ڣ���������ڣ��ͻᴴ��һ�����ļ�
		CString strfieldpath = filelogic.GetIntegrityFile(dbName, tbName);
		if (FileHelper::IsVaildFile(strfieldpath) == false) {
			if (FileHelper::CreateFile(strfieldpath) == false) {
				return false;
			}
		}

		if (inteDao.GetIntegrity(strfieldpath, fd) == true) {
			return false;		//�Ѿ�����,�ֶ����ظ�
		}
		if (inteDao.CreateIntegrity(strfieldpath, fd, true) == false) {
			return false;
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to create integrity!"));
	}

	return true;
}

bool IntegrityLogic::isPrimaryKey(const CString dbname, const CString tbName, const CString fieldName)
{
	CString strFilepath = filelogic.GetIntegrityFile(dbname, tbName);
	if (FileHelper::IsVaildFile(strFilepath) == FALSE) {
		return false;
	}
	vector<CIntegrityEntity>res = inteDao.readIntegrityList(strFilepath);
	for (vector<CIntegrityEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		IntegrityBlock itg = ite->getBlock();
		CIntegrityEntity itye;
		itye.SetBlock(itg);
		CString fieldname = itye.getFieldName();
		if (fieldName.CompareNoCase(fieldname) == 0) {
			return itye.getIsPrimary();
		}
	}
	return false;
}

bool IntegrityLogic::isNotNullKey(const CString dbname, const CString tbName, const CString fieldName)
{
	CString strFilepath = filelogic.GetIntegrityFile(dbname, tbName);
	if (FileHelper::IsVaildFile(strFilepath) == FALSE) {
		return false;
	}
	vector<CIntegrityEntity>res = inteDao.readIntegrityList(strFilepath);
	for (vector<CIntegrityEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		IntegrityBlock itg = ite->getBlock();
		CIntegrityEntity itye;
		itye.SetBlock(itg);
		CString fieldname = itye.getFieldName();
		if (fieldName.CompareNoCase(fieldname) == 0) {
			return itye.getIsNotNull();
		}
	}
	return false;
}

bool IntegrityLogic::isDefaultKey(const CString dbname, const CString tbName, const CString fieldName)
{
	CString strFilepath = filelogic.GetIntegrityFile(dbname, tbName);
	if (FileHelper::IsVaildFile(strFilepath) == FALSE) {
		return false;
	}
	vector<CIntegrityEntity>res = inteDao.readIntegrityList(strFilepath);
	for (vector<CIntegrityEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		IntegrityBlock itg = ite->getBlock();
		CIntegrityEntity itye;
		itye.SetBlock(itg);
		CString fieldname = itye.getFieldName();
		if (fieldName.CompareNoCase(fieldname) == 0) {
			return itye.getIsDefault();
		}
	}
	return false;
}

CString IntegrityLogic::getDefaultValue(const CString dbname, const CString tbName, const CString fieldName)
{
	CString strFilepath = filelogic.GetIntegrityFile(dbname, tbName);
	vector<CIntegrityEntity>res = inteDao.readIntegrityList(strFilepath);
	for (vector<CIntegrityEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		IntegrityBlock itg = ite->getBlock();
		CIntegrityEntity itye;
		itye.SetBlock(itg);
		CString fieldname = itye.getFieldName();
		if (fieldName.CompareNoCase(fieldname) == 0) {
			return itye.getDefault();
		}
	}
	return CString();
}
bool IntegrityLogic::getInter(const CString dbName, const CString tbName, CString oldName, CString newName)
{
	try {
		return inteDao.ChangeFieldticName(filelogic.GetIntegrityFile(dbName, tbName), filelogic.GetIntegrityFile(dbName, _T("Index")), oldName, newName);
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get FIELD!"));
	}

	return false;
}