#pragma once
#include <vector>
#include <iostream>
#include "column.h"

using namespace std;

class Table{
public:
	vector<column> column_list;
	Table(void);
	~Table(void);
	void _UnitInsert(string value, int col_num, int size);
	char* assignVarChar(string f, int _size);
	void insert(int col_num, vector<char> type);
	void makeDic(vector<char*>& input, vector<tempElement>& realDic, int col_num, char type);
	void DicToStore(vector<tempElement>& temp, vector<tempElement>& dic, vector<columnElement>& store, char type);
};
