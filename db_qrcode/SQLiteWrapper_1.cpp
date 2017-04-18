//SQLiteWrapper.cpp:

#include "stdafx.h"
#include "SQLiteWrapper_1.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
SQLiteStatement::SQLiteStatement(string const& statement, sqlite3* db)
{
	if (sqlite3_prepare(db, statement.c_str(), -1, &m_stmt, 0) != SQLITE_OK)
	{
		throw sqlite3_errmsg(db);
	}

	if (!m_stmt)
	{
		throw "stmt is null";
	}
}

SQLiteStatement::~SQLiteStatement()
{
	if (m_stmt)
	{
		sqlite3_finalize(m_stmt);
	}
}

bool SQLiteStatement::Bind(int index, int value)
{
	if (sqlite3_bind_int(m_stmt, index+1, value) != SQLITE_OK)
		return false;

	return true;
}
bool SQLiteStatement::Bind(int index, double value)
{
	if (sqlite3_bind_double(m_stmt, index+1, value) != SQLITE_OK)
		return false;

	return true;
}
bool SQLiteStatement::Bind(int index, string const& value)
{
	if (sqlite3_bind_text(m_stmt, index+1, value.c_str(), value.length(), SQLITE_TRANSIENT) != SQLITE_OK)
		return false;

	return true;
}
bool SQLiteStatement::BindNull(int index)
{
	if (sqlite3_bind_null(m_stmt, index+1) != SQLITE_OK)
		return false;

	return true;
}

bool SQLiteStatement::Execute()
{
	if (sqlite3_step(m_stmt) != SQLITE_DONE)
		return false;

	sqlite3_reset(m_stmt);
	return true;
}

bool SQLiteStatement::NextRow()
{
	int ret = sqlite3_step(m_stmt);

	if (ret == SQLITE_ROW)
		return true;
	
	if (ret == SQLITE_DONE)
	{
		sqlite3_reset(m_stmt);
	}

	return false;
}

int SQLiteStatement::ValueInt(int index)
{
	return sqlite3_column_int(m_stmt, index);
}

double SQLiteStatement::ValueDouble(int index)
{
	return sqlite3_column_double(m_stmt, index);
}

string SQLiteStatement::ValueString(int index)
{
	return reinterpret_cast<const char*>(sqlite3_column_text(m_stmt, index));
}
//////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
SQLiteWrapper::SQLiteWrapper(string const& filename)
: m_db(NULL)
{
	if (sqlite3_open(filename.c_str(), &m_db) != SQLITE_OK)
		return;
}

SQLiteWrapper::~SQLiteWrapper()
{
	if (m_db)
	{
		sqlite3_close(m_db);
	}
}

bool SQLiteWrapper::DirectStatement(string const& stmt)
{	
	if (sqlite3_exec(m_db, stmt.c_str(), 0, 0, NULL) != SQLITE_OK)
		return false;

	return true;
}

bool SQLiteWrapper::SelectStatement(string const& stmt, ResultTable& res)
{
	res.reset();

	if (sqlite3_exec(m_db, stmt.c_str(), SelectCallback, static_cast<void*>(&res), NULL) != SQLITE_OK)
		return false;

	return true;
}

int SQLiteWrapper::SelectCallback(void *pParam, int nColumn, char** column_value, char** column_key)
{
	ResultTable* res = reinterpret_cast<ResultTable*>(pParam);

	//if (res->m_Records.size() == 0)
	//{
	//	StringArray table_header;
	//	for (int i = 0; i < nColumn; i++)
	//	{
	//		table_header.push_back(column_key[i]);
	//	}
	//	res->m_Records.push_back(table_header);
	//}

	StringArray record;
	for (int i = 0; i < nColumn; i++)
	{
		if (column_value[i])
			record.push_back(column_value[i]);
		else
			record.push_back("<null>");
	}
	res->m_Records.push_back(record);

	return 0;
}

SQLiteStatement* SQLiteWrapper::Statement(string const& stmt)
{
	try
	{
		return new SQLiteStatement(stmt, m_db);
	}
	catch (const char* e)
	{

#ifdef _DEBUG
		OutputDebugStringA(e);
#endif
		return NULL;
	}
}

string SQLiteWrapper::GetLastError()
{
	return sqlite3_errmsg(m_db);
}
//////////////////////////////////////////////////////////////////////////////////////////////