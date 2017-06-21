#include "stdafx.h"
#include "TableDao.h"

//创建表
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

//获取表信息
int TableDao::GetTables(const CString strFilepath, TABLEARR &arr) {
	try {
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE) {
			return false;
		}
		file.SeekToBegin();
		TableBlock tb;
		int nCount = 0;
		//读取表信息
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

//从文件获取所有表描述信息
vector <CTablEntity> TableDao::ReadTableList(CString &TbFilePath) {
	vector <CTablEntity> res;
	FileHelper f;
	try {
		CFile file;
		if (f.IsVaildFile(TbFilePath)) {
			file.Open(TbFilePath, CFile::modeRead | CFile::shareDenyNone);	//不禁止其它进程读写访问文件，但如果文件已经被其它进程以兼容模式打开，则创建文件失败。
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
			AfxMessageBox(_T("该数据库不存在表！"), MB_OK);
		}
	}
	catch (CException *e) {
		e->Delete();
		throw new CAppException(_T("Failed to get all table!"));
	}

	return res;
}

//修改表名
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

//修改表的trd,tdf文件名
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
		AfxMessageBox(_T("该表不存在记录！"), MB_OK);
	}

	if (f.IsVaildFile(oldTdfFilePath)) {
		if (!f.ModifyFileName(oldTdfFilePath, newTdfFilePath)) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("该表没有字段！"), MB_OK);
	}

	if (f.IsVaildFile(oldTicFilePath)) {
		if (!f.ModifyFileName(oldTicFilePath, newTicFilePath)) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("该表没有完整性约束文件！"), MB_OK);
	}

	return true;
}

//删除表
bool TableDao::DeleteTable(CString strFilePath, CString &tbname) {
	vector <CTablEntity> res;
	if (tbname.GetLength() == 0) {
		return false;
	}
	res = ReadTableList(strFilePath);
	for (vector <CTablEntity>::iterator ite = res.begin(); ite != res.end(); ++ite) {
		CTablEntity tb = ite->GetBlock();
		CString tbName = tb.getTableName();
		if (tbName.CompareNoCase(tbname) == 0) {		//如果表名一致，则从vector数组中删除该表块的信息
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

//删除该表的相关文件
bool TableDao::DeleteTBFile(CString dbFolderPath, CString &tbname) {
	CString trdFilePath = dbFolderPath + CString("\\") + tbname + CString(".trd");
	CString tdfFilePath = dbFolderPath + CString("\\") + tbname + CString(".tdf");
	CString ticFilePath = dbFolderPath + CString("\\") + tbname + CString(".tic");
	FileHelper f;
	if (f.IsVaildFile(trdFilePath)) {
		if (DeleteFile(trdFilePath) == 0) {	//未能成功删除，返回值为0
			return false;
		}
	}
	else {
		AfxMessageBox(_T("该表不存在记录！"), MB_OK);
	}

	if (f.IsVaildFile(tdfFilePath)) {
		if (DeleteFile(tdfFilePath) == 0) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("该表没有字段！"), MB_OK);
	}

	if (f.IsVaildFile(ticFilePath)) {
		if (DeleteFile(ticFilePath) == 0) {
			return false;
		}
	}
	else {
		AfxMessageBox(_T("该表没有完整性约束文件！"), MB_OK);
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
//修改表：修改表定义文件
//输入参数：
// const CString filePath：表定义文件路径
// CTablEntity &te：表格信息
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
				tableFile.Seek(offset, CFile::begin); //文件指针指向上一个记录（结束）的位置
				tableFile.Write(&te.GetBlock(), sizeof(TableBlock));
				flag = true;
				break;
			}
			offset = tableFile.GetPosition();
		}

		tableFile.Close();

		return flag;
	} //异常处理：修改表格信息失败
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("修改表格信息失败！"));
	}
	catch (...)
	{
		throw new CAppException(_T("修改表格信息失败！"));
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
		//删除异常信息
		e->Delete();
		//抛出一个常规的异常
		throw new CAppException(_T("Failed to resume the fields of the table!"));
	}

	return false;
}