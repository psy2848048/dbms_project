#include "Table.h"
#include "column.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "ClockChecker.h"
#include <cstring>

using namespace std;

Table::Table(void){
	column_list.clear();
}

Table::~Table(void){
}

// input each data to the column
void Table::_UnitInsert(string value, int col_num, int size){
	tempElement temp;
	temp.value = assignVarChar(value, size);
	column_list.at(col_num).tempStoreOriginal.push_back(temp);
}

void Table::makeDic(vector<char*>& input, vector<tempElement>& realDic, int col_num, char type){
	// realDic : column_list.at(?).Dic
	long long index = 0;
	char* compare = input.at(0);
	tempElement _temp;
	_temp.index = index;
	_temp.value = input.at(0);
	realDic.push_back(_temp);

	switch (type){
	case 'I':
		for (size_t i=1; i < input.size(); i++){
			if (_atoi64(compare) != _atoi64(input[i])){
				index++;
				tempElement temp;
				temp.index = index;
				temp.value = input[i];
				compare = input[i];
				realDic.push_back(temp);
			}
		}
		break;
	case 'F':
		for (size_t i=1; i < input.size(); i++){
			if ((float)atof(compare) != (float)atof(input[i])){
				index++;
				tempElement temp;
				temp.index = index;
				temp.value = input[i];
				compare = input[i];
				realDic.push_back(temp);
			}
		}
		break;
	case 'C':
		for (size_t i=1; i < input.size(); i++){
			if (strcmp(compare, input[i]) != 0){
				index++;
				tempElement temp;
				temp.index = index;
				temp.value = input[i];
				compare = input[i];
				realDic.push_back(temp);
			}
		}
		break;
	}
	
	input.clear();
}

long long binarySearch(char* searchValue, vector<tempElement>& reference, char type){
	long long first = 0;
	long long last = reference.size() -1;
	long long middle = (first+last)/2;
	switch (type){
	case 'C':
		while(first <= last){
			int index = strcmp(reference[middle].value, searchValue);
			if (index < 0) first = middle + 1;
			else if (index == 0) break;
			else last = middle -1;

			middle = (first + last) /2;
		}
		if (first > last){
			cout << "There is no value" << endl;
			return -1;
		}
		return reference[middle].index;
	case 'I':
		while(first <= last){
			if (_atoi64(reference[middle].value) < _atoi64(searchValue)) first = middle + 1;
			else if (_atoi64(reference[middle].value) == _atoi64(searchValue)) break;
			else last = middle -1;

			middle = (first + last) /2;
		}
		if (first > last){
			cout << "There is no value" << endl;
			return -1;
		}
		return reference[middle].index;
	case 'F':
		while(first <= last){
			if ((float)atof(reference[middle].value) < (float)atof(searchValue)) first = middle + 1;
			else if ((float)atof(reference[middle].value) == (float)atof(searchValue)) break;
			else last = middle -1;

			middle = (first + last) /2;
		}
		if (first > last){
			cout << "There is no value" << endl;
			return -1;
		}
		return reference[middle].index;
	}
}

void Table::DicToStore(vector<tempElement>& temp, vector<tempElement>& realDic, vector<columnElement>& store, char type){
	for(long long it = 0; it < temp.size() ; ++it){
		columnElement realData;
		realData.index = it;
		realData.valueIndex = binarySearch(temp[it].value, realDic, type);
		store.push_back(realData);
	}
}

bool comparisonFunc_char(const char *c1, const char *c2){
    return strcmp(c1, c2) < 0;
}

bool comparisonFunc_int(const char *c1, const char *c2){
    return (_atoi64(c1) < _atoi64(c2));
}

bool comparisonFunc_float(const char *c1, const char *c2){
    return ((float)atof(c1) < (float)atof(c2));
}

void Table::insert(int col_num, vector<char> type){
	// Later, insert exception for 1 item -> "pass the sort part"
	vector<vector<char*> > sorted;
	sorted.clear();
	sorted.resize(col_num);
	ClockChecker cck;

	for (long long i=0; i< col_num; ++i){
		for (long long j = 0; j < column_list.at(i).tempStoreOriginal.size(); ++j){
			sorted.at(i).push_back(column_list.at(i).tempStoreOriginal.at(j).value);
		}
	}
	cck.SetStartClock();
	for (int i=0; i < type.size(); ++i){
		switch (type.at(i)){
		case 'I':
			sort(sorted.at(i).begin(), sorted.at(i).end(), comparisonFunc_int);
			break;
		case 'F':
			sort(sorted.at(i).begin(), sorted.at(i).end(), comparisonFunc_float);
			break;
		case 'C':
			sort(sorted.at(i).begin(), sorted.at(i).end(), comparisonFunc_char);
			break;
		}
	}
	cck.SetEndClock();
	cout << "Sorting time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" <<endl;

	cck.SetStartClock();
	for (int i=0; i < col_num; ++i) makeDic(sorted.at(i), column_list.at(i).Dic, i, type.at(i));
	cck.SetEndClock();
	cout << "Dictionary making : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;

	cck.SetStartClock();
	for (int i=0; i< col_num; ++i){
		DicToStore(column_list.at(i).tempStoreOriginal, column_list.at(i).Dic, column_list.at(i).columndata, type[i]);
		column_list.at(i).type = type[i];
	}
	cck.SetEndClock();

	cout << "Dictionary to Column : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;
	return;
}



char* Table::assignVarChar(string f, int _size){
	int char_Size = strlen((const char*)f.c_str());
	char* ret_val;
	if (char_Size < _size) {
		ret_val = new char[char_Size+1];
		strcpy(ret_val, f.c_str());
	}
	else {
		ret_val = new char[_size+1];
		strncpy(ret_val, f.c_str(), _size);
		ret_val[_size] = '\0';
	}
	return ret_val;
}
