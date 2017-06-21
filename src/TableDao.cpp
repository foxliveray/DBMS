#include "stdafx.h"
#include "TableDao.h"

//������
bool TableDao::Create(const CString strFilePath, CTablEntity &te) {
	try {
		CFile file;
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}

		file.SeekToEnd();
		file.Write(&te.GetBlock(), sizeof(TableBlock));

		file.Close();
		return true;
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to add table information!"));
	}
}

//��ȡ����Ϣ
int TableDao::GetTables(const CString strFilepath, TABLEARR &arr) {
	try {
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		TableBlock tb;
		int nCount = 0;
		//��ȡ����Ϣ
		while (file.Read(&tb, sizeof(TableBlock)) > 0) {
			CTablEntity* pTable = new CTablEntity();
			pTable->SetBlock(tb);
			arr.Add(pTable);
			nCount++;
		}
		file.Close();
		return nCount;
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to query table information!"));
	}

	return 0;
}

//���ļ���ȡ���б�������Ϣ
vector <CTablEntity> TableDao::ReadTableList(CString &TbFilePath) {
	vector <CTablEntity> res;
	FileHelper f;
	try {
		CFile file;
		if (f.IsVaildFile(TbFilePath)) {
			file.Open(TbFilePath, CFile::modeRead | CFile::shareDenyNone);	//����ֹ�������̶�д�����ļ���������ļ��Ѿ������������Լ���ģʽ�򿪣��򴴽��ļ�ʧ�ܡ�
			TableBlock tb;

			file.SeekToBegin();
			while (file.Read(&tb, sizeof(TableBlock)) > 0) {
				CTablEntity ctb;
				ctb.SetBlock(tb);
				res.push_back(ctb);
			}
			file.Close();
		}
		else {
			AfxMessageBox(_T("�����ݿⲻ���ڱ�"), MB_OK);
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get all table!"));
	}

	return res;
}

//�޸ı���
bool TableDao::ModifyTBName(CString strFilePath, CString &oldTBName, CString &newTBName) {
	vector <CTablEntity> res;
	if (oldTBName.GetLength() == 0 || newTBName.GetLength() == 0) {
		return false;
	}
	res = ReadTableList(strFilePath);
	for (vector <CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CTablEntity tb = ite->GetBlock();
		CString tbName = tb.getTableName();
		if (tbName.CompareNoCase(oldTBName) == 0) {
			ite->setTableName(newTBName);
			break;
		}
	}

	try {
		CFile file;
		if (file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		for (vector<CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
			CTablEntity tb = ite->GetBlock();
			file.Write(&tb.GetBlock(), sizeof(TableBlock));
			file.SeekToEnd();
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to modify the table!"));
	}
}

//�޸ı��trd,tdf�ļ���
bool TableDao::ModifyTBFile(CString dbFolderPath, CString &oldTBName, CString &newTBName) {
	CString oldTrdFilePath = dbFolderPath + CString("\\") + oldTBName + CString(".trd");
	CString newTrdFilePath = dbFolderPath + CString("\\") + newTBName + CString(".trd");
	CString oldTdfFilePath = dbFolderPath + +CString("\\") + oldTBName + CString(".tdf");
	CString newTdfFilePath = dbFolderPath + +CString("\\") + newTBName + CString(".tdf");
	CString oldTicFilePath = dbFolderPath + +CString("\\") + oldTBName + CString(".tic");
	CString newTicFilePath = dbFolderPath + +CString("\\") + newTBName + CString(".tic");

	FileHelper f;
	if (f.IsVaildFile(oldTrdFilePath)) {
		if (!f.ModifyFileName(oldTrdFilePath, newTrdFilePath)) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("�ñ����ڼ�¼��"), MB_OK);
	}

	if (f.IsVaildFile(oldTdfFilePath)) {
		if (!f.ModifyFileName(oldTdfFilePath, newTdfFilePath)) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("�ñ�û���ֶΣ�"), MB_OK);
	}

	if (f.IsVaildFile(oldTicFilePath)) {
		if (!f.ModifyFileName(oldTicFilePath, newTicFilePath)) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("�ñ�û��������Լ���ļ���"), MB_OK);
	}

	return true;
}

//ɾ����
bool TableDao::DeleteTable(CString strFilePath, CString &tbname) {
	vector <CTablEntity> res;
	if (tbname.GetLength() == 0) {
		return false;
	}
	res = ReadTableList(strFilePath);
	for (vector <CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CTablEntity tb = ite->GetBlock();
		CString tbName = tb.getTableName();
		if (tbName.CompareNoCase(tbname) == 0) {		//�������һ�£����vector������ɾ���ñ�����Ϣ
			res.erase(ite);
			break;
		}
	}

	try {
		CFile file;
		if (file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		for (vector<CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
			CTablEntity tb = ite->GetBlock();
			file.Write(&tb.GetBlock(), sizeof(TableBlock));
			file.SeekToEnd();
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to delete the table!"));
	}
}

//ɾ���ñ������ļ�
bool TableDao::DeleteTBFile(CString dbFolderPath, CString &tbname) {
	CString trdFilePath = dbFolderPath + CString("\\") + tbname + CString(".trd");
	CString tdfFilePath = dbFolderPath + CString("\\") + tbname + CString(".tdf");
	CString ticFilePath = dbFolderPath + CString("\\") + tbname + CString(".tic");
	FileHelper f;
	if (f.IsVaildFile(trdFilePath)) {
		if (DeleteFile(trdFilePath) == 0) {	//δ�ܳɹ�ɾ��������ֵΪ0
			return false;
		}
	}
	else {
		AfxMessageBox(_T("�ñ����ڼ�¼��"), MB_OK);
	}

	if (f.IsVaildFile(tdfFilePath)) {
		if (DeleteFile(tdfFilePath) == 0) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("�ñ�û���ֶΣ�"), MB_OK);
	}

	if (f.IsVaildFile(ticFilePath)) {
		if (DeleteFile(ticFilePath) == 0) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("�ñ�û��������Լ���ļ���"), MB_OK);
	}

	return true;
}

bool TableDao::AddFieldNum(CString strFilePath, CString &oldTBName, CFieldEntity &fe)
{
	vector <CTablEntity> res;
	res = ReadTableList(strFilePath);
	for (vector <CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CTablEntity tb = ite->GetBlock();
		CString tbName = tb.getTableName();
		if (tbName.CompareNoCase(oldTBName) == 0) {
			ite->addField(fe);
			break;
		}
	}

	try {
		CFile file;
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		for (vector<CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
			CTablEntity tb = ite->GetBlock();
			file.Write(&tb, sizeof(TableBlock));
			file.SeekToEnd();
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to modify the table!"));
	}
	return true;
}

bool TableDao::MinusFieldNum(CString strFilePath, CString &oldTBName, CFieldEntity &fe)
{
	vector <CTablEntity> res;
	res = ReadTableList(strFilePath);
	for (vector <CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CTablEntity tb = ite->GetBlock();
		CString tbName = tb.getTableName();
		if (tbName.CompareNoCase(oldTBName) == 0) {
			ite->deleteField(fe);
			break;
		}
	}

	try {
		CFile file;
		if (file.Open(strFilePath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		for (vector<CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
			CTablEntity tb = ite->GetBlock();
			file.Write(&tb, sizeof(TableBlock));
			file.SeekToEnd();
		}
		file.Close();
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to modify the table!"));
	}
	return true;
}
//�޸ı��޸ı����ļ�
//���������
// const CString filePath�������ļ�·��
// CTablEntity &te�������Ϣ
bool TableDao::AlterTable(const CString filePath, CTablEntity &te)
{
	try
	{
		CFile tableFile;
		if (tableFile.Open(filePath, CFile::modeReadWrite | CFile::shareDenyWrite) == FALSE)
			return false;

		tableFile.SeekToBegin();
		long offset = tableFile.GetPosition();

		bool flag = false;
		TableBlock tb;
		CString tableName = te.getTableName();
		CString strName;
		while (tableFile.Read(&tb, sizeof(TableBlock)) > 0)
		{
			strName = CharHelper::ToString(tb.name, sizeof(VARCHAR));
			if (tableName.CompareNoCase(strName) == 0)
			{
				tableFile.Seek(offset, CFile::begin); //�ļ�ָ��ָ����һ����¼����������λ��
				tableFile.Write(&te.GetBlock(), sizeof(TableBlock));
				flag = true;
				break;
			}
			offset = tableFile.GetPosition();
		}

		tableFile.Close();

		return flag;
	} //�쳣�����޸ı����Ϣʧ��
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("�޸ı����Ϣʧ�ܣ�"));
	}
	catch (...)
	{
		throw new CAppException(_T("�޸ı����Ϣʧ�ܣ�"));
	}

	return false;
}

bool TableDao::ResumeFieldsIntable(const CString filePath, CTablEntity &te)
{
	try
	{
		CFile file;
		if (file.Open(filePath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {
			return false;
		}
		file.SeekToBegin();

		FieldBlock fbk;
		while (file.Read(&fbk, sizeof(FieldBlock)) > 0 && fbk.name != "")
		{
			CFieldEntity oneField;
			oneField.SetBlock(fbk);
			te.addField(oneField);
		}
		file.Close();

		return true;
	}
	catch (CException *e)
	{
		//ɾ���쳣��Ϣ
		e->Delete();
		//�׳�һ��������쳣
		throw new CAppException(_T("Failed to resume the fields of the table!"));
	}

	return false;
}