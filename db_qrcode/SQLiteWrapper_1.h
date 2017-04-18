//SQLiteWrapper.h:

#pragma once

#include "sqlite3.h"

#include <vector>
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////
class SQLiteStatement
{
	friend class SQLiteWrapper;
private:
	SQLiteStatement(string const& statement, sqlite3* db);

public:
	~SQLiteStatement();

public:
	bool Bind(int index, int value);
	bool Bind(int index, double value);
	bool Bind(int index, string const& value);
	bool BindNull(int index);

	bool Execute();

	bool NextRow();
	
	int ValueInt(int index);
	double ValueDouble(int index);
	string ValueString(int index);

private:
	sqlite3_stmt* m_stmt;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////

typedef vector<string> StringArray;
typedef vector<StringArray> StringMutrix;

class ResultTable
{
	friend class SQLiteWrapper;
public:
	ResultTable() : m_recordIndex(0) {}

	StringArray* next()
	{
		if (m_recordIndex < m_Records.size())
			return &(m_Records[m_recordIndex++]);
		return NULL;
	}
	StringMutrix m_Records;
private:
	void reset()
	{
		m_Records.clear();
		m_recordIndex = 0;
	}
	unsigned int m_recordIndex;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SQLiteWrapper
{
public:
	SQLiteWrapper(string const& filename);
	~SQLiteWrapper();

public:
	bool DirectStatement(string const& stmt);
	bool SelectStatement(string const& stmt, ResultTable& res);
	SQLiteStatement* Statement(string const& stmt);

	string GetLastError();

private:
	static int SelectCallback(void *pParam, int nColumn, char** column_value, char** column_key);

private:
	sqlite3* m_db;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////