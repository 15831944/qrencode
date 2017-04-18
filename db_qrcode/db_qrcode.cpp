// db_qrcode.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "db_qrcode.h"
#include "SQLiteWrapper_1.h"
#include <iostream>


DB_QRCODE_API bool db_qrcode(DB_OPERATION opt, QRCODE_INFO* qrcode,char* starttime, char* endtime, QRCODE_RECORDS* results)
{
	char stmt[512];
	switch(opt)
	{
	case DB_INSERT:
		sprintf(stmt, "INSERT INTO qrcodeinfo(serial,info,recorddate) VALUES('%s','%s',DATETIME('now','localtime'))",
			qrcode->serial, qrcode->info);
		break;
	case DB_DELETE:
		sprintf(stmt,"DELETE FROM qrcodeinfo",
			qrcode->serial);
		break;
	case DB_UPDATE:
			return false;
		break;
	case DB_SELECT:
		sprintf(stmt,"SELECT * FROM qrcodeinfo WHERE serial='%s'", qrcode->serial);
		break;
	case DB_SELECT_ALL:
		sprintf(stmt, "SELECT * FROM qrcodeinfo WHERE recorddate BETWEEN DATETIME('%s','localtime') AND DATETIME('%s','localtime','+1 day')", starttime, endtime);
		break;
	case DB_CREATE_TABLE:
		sprintf(stmt, "CREATE TABLE qrcodeinfo(serial TEXT NOT NULL PRIMARY KEY, info TEXT, recorddate DATETIME NOT NULL)");
		break;
	case DB_DROP_TABLE:
		sprintf(stmt, "DROP TABLE qrcodeinfo");
		break;
	}

	SQLiteWrapper sql(".\\database\\qrcode.db");
	if (opt == DB_SELECT)
	{
		ResultTable records;
		if (!sql.SelectStatement(stmt, records))
		{
#ifdef _DEBUG
			OutputDebugStringA(sql.GetLastError().c_str());
#endif
			return false;
		}

		StringArray* record = NULL;
		if (!(record = records.next()))
			return false;

		strcpy(qrcode->serial, (*record)[0].c_str());
		strcpy(qrcode->info, (*record)[1].c_str());
		strcpy(qrcode->date, (*record)[2].c_str());
	}
	else if (opt == DB_SELECT_ALL)
	{
		ResultTable records;
		if (!sql.SelectStatement(stmt, records))
		{
#ifdef _DEBUG
			OutputDebugStringA(sql.GetLastError().c_str());
#endif
		
			return false;
		}
		StringArray* record;
		QRCODE_INFO tmp;
		while ((record = records.next()))
		{
			strcpy(tmp.serial, (*record)[0].c_str());
			strcpy(tmp.info, (*record)[1].c_str());
			strcpy(tmp.date, (*record)[2].c_str());
			results->push_back(tmp);
		}
	}
	else
	{
		if (!sql.DirectStatement(stmt))
		{
#ifdef _DEBUG 
			OutputDebugStringA(sql.GetLastError().c_str());
#endif
			return false;
		}
	}

	return true;
}
