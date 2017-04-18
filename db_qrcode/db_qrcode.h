// db_qrcode.h:

#pragma once

#include <vector>

#ifdef DB_QRCODE_EXPORTS
#define DB_QRCODE_API extern "C" __declspec(dllexport)
#else
#define DB_QRCODE_API extern "C" __declspec(dllimport)
#endif

typedef enum
{
	DB_CREATE_TABLE,
	DB_DROP_TABLE,
	DB_INSERT,
	DB_DELETE,
	DB_UPDATE,
	DB_SELECT,
	DB_SELECT_ALL,
}DB_OPERATION;

typedef struct
{
	char serial[33];
	char info[100];
	char date[30];
}QRCODE_INFO;

typedef std::vector<QRCODE_INFO> QRCODE_RECORDS;

DB_QRCODE_API bool db_qrcode(DB_OPERATION opt, QRCODE_INFO* info = NULL,char* starttime = NULL, char* endtime = NULL, QRCODE_RECORDS* records = NULL);