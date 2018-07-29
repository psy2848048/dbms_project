#include "Plan.h"
#include "Table.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "ClockChecker.h"

using namespace std;

void _selection_EQ(Table* output, Table* input, vector<SelectCond> conds, vector<int> projCols, vector<long long>& index_list, char type){
	switch (type){
	case 'I':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atoi(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) == conds[0].intConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'F':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atof(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) == conds[0].floatConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'C':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (strcmp(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value, (conds[0].strConst).c_str()) == 0){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	}
}

void _selection_NEQ(Table* output, Table* input, vector<SelectCond> conds, vector<int> projCols, vector<long long>& index_list, char type){
	switch (type){
	case 'I':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atoi(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) != conds[0].intConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'F':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atof(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) != conds[0].floatConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'C':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (strcmp(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value, (conds[0].strConst).c_str()) != 0){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	}
}

void _selection_LT(Table* output, Table* input, vector<SelectCond> conds, vector<int> projCols, vector<long long>& index_list, char type){
	switch (type){
	case 'I':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atoi(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) < conds[0].intConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'F':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atof(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) < conds[0].floatConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'C':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (strcmp(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value, (conds[0].strConst).c_str()) < 0){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	}
}

void _selection_LEQ(Table* output, Table* input, vector<SelectCond> conds, vector<int> projCols, vector<long long>& index_list, char type){
	switch (type){
	case 'I':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atoi(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) <= conds[0].intConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'F':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atof(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) <= conds[0].floatConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'C':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (strcmp(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value, (conds[0].strConst).c_str()) <= 0){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	}
}

void _selection_GT(Table* output, Table* input, vector<SelectCond> conds, vector<int> projCols, vector<long long>& index_list, char type){
	switch (type){
	case 'I':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atoi(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) > conds[0].intConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'F':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atof(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) > conds[0].floatConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'C':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (strcmp(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value, (conds[0].strConst).c_str()) > 0){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	}
}

void _selection_GEQ(Table* output, Table* input, vector<SelectCond> conds, vector<int> projCols, vector<long long>& index_list, char type){
	switch (type){
	case 'I':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atoi(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) <= conds[0].intConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'F':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (atof(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value) <= conds[0].floatConst){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	case 'C':
		for (size_t i=0; i < input->column_list.at(conds[0].idxCol).columndata.size(); ++i){
			if (strcmp(input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(i).valueIndex).value, (conds[0].strConst).c_str()) >= 0){
				index_list.push_back(input->column_list.at(conds[0].idxCol).columndata.at(i).index);
			}
		}
		break;
	}
}

void Operator::selection(
        Table* output,
        Table* input, 
        vector<SelectCond> conds, 
        vector<int> projCols) {

	char type = input->column_list.at(conds[0].idxCol).type;
	vector<long long> index_list;
	ClockChecker cck;
	cck.SetStartClock();
	switch (conds[0].op){
	case EQ:
		_selection_EQ(output, input, conds, projCols, index_list, type);
		break;
	case NEQ:
		_selection_NEQ(output, input, conds, projCols, index_list, type);
		break;
	case LT:
		_selection_LT(output, input, conds, projCols, index_list, type);
		break;
	case LEQ:
		_selection_LEQ(output, input, conds, projCols, index_list, type);
		break;
	case GT:
		_selection_GT(output, input, conds, projCols, index_list, type);
		break;
	case GEQ:
		_selection_GEQ(output, input, conds, projCols, index_list, type);
		break;
	}
	output->column_list.resize(projCols.size());
	for (size_t j=0; j < index_list.size(); ++j){
		for (size_t i=0; i < projCols.size(); ++i){
			output->_UnitInsert(input->column_list.at(projCols.at(i)).Dic.at(input->column_list.at(projCols.at(i)).columndata.at(index_list.at(j)).valueIndex).value,i,25);
		}
	}

	vector<char> type_output;
	for (int i=0; i< projCols.size(); ++i){
		type_output.push_back(input->column_list.at(projCols.at(i)).type);
	}
	output->insert(projCols.size(), type_output);

	cck.SetEndClock();

	std::cout << "Select time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << '\n';
}

struct hash_element{
	long long index;
	long long value;
	hash_element* next;
	hash_element(long long point, long long index, hash_element* next)
		: index(index), value(value), next(next){}
};

void Operator::join(
        Table* output,
        Table* lhs, Table* rhs, 
        vector<JoinCond> conds, 
        vector<int> lProjsCols, vector<int> rProjCols) {

	int size_r = rhs->column_list.at(conds[0].rhsIdx).columndata.size();
	output->column_list.resize(lProjsCols.size() + rProjCols.size());

	vector<hash_element> hash_table;
	hash_table.clear();
	for (long long i=0; i< size_r; ++i){
		hash_element temp(-1, -1, '\0');
		hash_table.push_back(temp);
	}

	// HASH TABLE FOR RIGHT TABLE
	for (long long i=0; i< size_r; ++i){
		int coordinate = _atoi64(rhs->column_list.at(conds[0].rhsIdx).Dic.at(rhs->column_list.at(conds[0].rhsIdx).columndata.at(i).valueIndex).value) % size_r;
		if (hash_table[coordinate].index == -1){
			hash_table[coordinate].index = rhs->column_list.at(conds[0].rhsIdx).columndata.at(i).index;
			hash_table[coordinate].value = _atoi64(rhs->column_list.at(conds[0].rhsIdx).Dic.at(rhs->column_list.at(conds[0].rhsIdx).columndata.at(i).valueIndex).value);
		}
		else{
			hash_element* chain = &hash_table[coordinate];
			while(chain->next != '\0') chain = chain->next;
			chain->next = new hash_element(rhs->column_list.at(conds[0].rhsIdx).columndata.at(i).index, _atoi64(rhs->column_list.at(conds[0].rhsIdx).Dic.at(rhs->column_list.at(conds[0].rhsIdx).columndata.at(i).valueIndex).value),'\0');
		}
	}

	//
	// "size_l" is NOT MODULATOR!!!!!!
	// SCAN LEFT TABLE
	for (long long i=0; i < lhs->column_list.at(conds[0].lhsIdx).columndata.size(); ++i){
		int coordinate = atoi(lhs->column_list.at(conds[0].lhsIdx).Dic.at(lhs->column_list.at(conds[0].lhsIdx).columndata.at(i).valueIndex).value) % size_r;
		int l_value = atoi(lhs->column_list.at(conds[0].lhsIdx).Dic.at(lhs->column_list.at(conds[0].lhsIdx).columndata.at(i).valueIndex).value);
		if (hash_table[coordinate].value == l_value){
			for (int j=0; j < lProjsCols.size(); ++j) output->_UnitInsert(lhs->column_list.at(lProjsCols.at(j)).Dic.at(lhs->column_list.at(lProjsCols.at(j)).columndata.at(i).valueIndex).value, j, 25);
			for (int j=0; j < rProjCols.size(); ++j) output->_UnitInsert(rhs->column_list.at(rProjCols.at(j)).Dic.at(rhs->column_list.at(rProjCols.at(j)).columndata.at(hash_table[coordinate].index).valueIndex).value, lProjsCols.size() + j, 25);
		}
		else if(hash_table[coordinate].index != -1 && hash_table[coordinate].value != l_value){
			int ind = 0;
			hash_element* chain = &hash_table[coordinate];
			do{
				chain = chain->next;
				if (chain->value == l_value){
					ind = 1;
					break;
				}
			} while(chain->next != '\0');

			if (ind == 1){
				for (int j=0; j < lProjsCols.size(); ++j) output->_UnitInsert(lhs->column_list.at(lProjsCols.at(j)).Dic.at(lhs->column_list.at(lProjsCols.at(j)).columndata.at(i).valueIndex).value, j, 25);
				for (int j=0; j < rProjCols.size(); ++j) output->_UnitInsert(rhs->column_list.at(rProjCols.at(j)).Dic.at(rhs->column_list.at(rProjCols.at(j)).columndata.at(chain->index).valueIndex).value, lProjsCols.size() + j, 25);
			}
		}
	}
	vector<char> type;
	for (int i=0; i < lProjsCols.size(); ++i) type.push_back(lhs->column_list.at(lProjsCols[i]).type);
	for (int i=0; i < rProjCols.size(); ++i) type.push_back(rhs->column_list.at(rProjCols[i]).type);

	output->insert(lProjsCols.size() + rProjCols.size(), type);
}

bool comparisonFunc_asc_char(const tempElement c1, const tempElement c2){
	return strcmp(c1.value, c2.value) < 0;
}

bool comparisonFunc_asc_int(const tempElement c1, const tempElement c2){
	return (_atoi64(c1.value) < _atoi64(c2.value));
}

bool comparisonFunc_asc_float(const tempElement c1, const tempElement c2){
	return (atof(c1.value) < atof(c2.value));
}

bool comparisonFunc_desc_char(const tempElement c1, const tempElement c2){
	return strcmp(c1.value, c2.value) < 0;
}

bool comparisonFunc_desc_int(const tempElement c1, const tempElement c2){
	return (_atoi64(c1.value) < _atoi64(c2.value));
}

bool comparisonFunc_desc_float(const tempElement c1, const tempElement c2){
	return (atof(c1.value) < atof(c2.value));
}

void Operator::orderBy(
        Table* output,
        Table* input, 
        vector<OrderCond> conds) {

    //	sort list by sort function
	//	use asc function (comparisonFuc) and desc function (will be a counterorder)
	//	sort(vector.begin(), vector.end(), conparisonFunc or countercomp);
	//	output as index order for keeping row
	//
	char type = input->column_list.at(conds[0].idxCol).type;
	ClockChecker cck;
	cck.SetStartClock();
	output->column_list.resize(input->column_list.size());

	for (long long j=0; j < input->column_list.at(conds[0].idxCol).columndata.size(); ++j){
		tempElement temp;
		temp.index = input->column_list.at(conds[0].idxCol).columndata.at(j).index;
		temp.value = input->column_list.at(conds[0].idxCol).Dic.at(input->column_list.at(conds[0].idxCol).columndata.at(j).valueIndex).value;
		output->column_list.at(conds[0].idxCol).tempStoreOriginal.push_back(temp);
		output->column_list.at(conds[0].idxCol).type = type;
	}
	output->column_list.at(conds[0].idxCol).Dic = input->column_list.at(conds[0].idxCol).Dic;
	if (conds[0].desc == false){
		switch(type){
		case 'I':
			sort(output->column_list.at(conds[0].idxCol).tempStoreOriginal.begin(), 
				output->column_list.at(conds[0].idxCol).tempStoreOriginal.end(),
				comparisonFunc_asc_int);
			break;
		case 'F':
			sort(output->column_list.at(conds[0].idxCol).tempStoreOriginal.begin(), 
				output->column_list.at(conds[0].idxCol).tempStoreOriginal.end(),
				comparisonFunc_asc_float);
			break;
		case 'C':
			sort(output->column_list.at(conds[0].idxCol).tempStoreOriginal.begin(), 
				output->column_list.at(conds[0].idxCol).tempStoreOriginal.end(),
				comparisonFunc_asc_char);
		}
	}
	else if (conds[0].desc == true){
		switch(type){
		case 'I':
			sort(output->column_list.at(conds[0].idxCol).tempStoreOriginal.begin(), 
				output->column_list.at(conds[0].idxCol).tempStoreOriginal.end(),
				comparisonFunc_desc_int);
			break;
		case 'F':
			sort(output->column_list.at(conds[0].idxCol).tempStoreOriginal.begin(), 
				output->column_list.at(conds[0].idxCol).tempStoreOriginal.end(),
				comparisonFunc_desc_float);
			break;
		case 'C':
			sort(output->column_list.at(conds[0].idxCol).tempStoreOriginal.begin(), 
				output->column_list.at(conds[0].idxCol).tempStoreOriginal.end(),
				comparisonFunc_desc_char);
			break;
		}
	}

	for (long long i=0; i < input->column_list.size(); ++i){
		if (i != conds[0].idxCol){
			for (long long j=0; j < input->column_list.at(conds[0].idxCol).columndata.size(); ++j){
				tempElement temp;
				temp.index = j;
				temp.value = input->column_list.at(i).Dic.at(input->column_list.at(i).columndata.at(output->column_list.at(conds[0].idxCol).tempStoreOriginal.at(j).index).valueIndex).value;
				output->column_list.at(i).tempStoreOriginal.push_back(temp);
				output->column_list.at(i).type = input->column_list.at(i).type;
			}
		}
		output->column_list.at(i).Dic = input->column_list.at(i).Dic;
	}
	for (int i=0; i< output->column_list.size(); ++i) output->DicToStore(output->column_list.at(i).tempStoreOriginal, output->column_list.at(i).Dic, output->column_list.at(i).columndata, output->column_list.at(i).type);
	cck.SetEndClock();
	cout << "Orderby time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << '\n';
}

long long binarySearch_plan(char* searchValue, vector<char*>& reference, char type){
	long long first = 0;
	long long last = reference.size() -1;
	long long middle = (first+last)/2;
	switch (type){
	case 'C':
		while(first <= last){
			int index = strcmp(reference[middle], searchValue);
			if (index < 0) first = middle + 1;
			else if (index == 0) break;
			else last = middle -1;

			middle = (first + last) /2;
		}
		if (first > last){
			reference.push_back(searchValue);
			return -1;
		}
		return middle;
	case 'I':
		while(first <= last){
			if (_atoi64(reference[middle]) < _atoi64(searchValue)) first = middle + 1;
			else if (_atoi64(reference[middle]) == _atoi64(searchValue)) break;
			else last = middle -1;

			middle = (first + last) /2;
		}
		if (first > last){
			reference.push_back(searchValue);
			return -1;
		}
		return middle;
	case 'F':
		while(first <= last){
			if (atof(reference[middle]) < atof(searchValue)) first = middle + 1;
			else if (atof(reference[middle]) == atof(searchValue)) break;
			else last = middle -1;

			middle = (first + last) /2;
		}
		if (first > last){
			reference.push_back(searchValue);
			return -1;
		}
		return middle;
	}
}

void aggr_count(vector<float>& vec, vector<char*>& mem, Table* input, int col_num){
	for (long long i=0; i < input->column_list.at(col_num).columndata.size(); ++i){
		long long result;
		if (mem.size() == 0){
			mem.push_back(input->column_list.at(col_num).Dic.at(input->column_list.at(col_num).columndata.at(i).valueIndex).value);
			vec.push_back(1);
		}
		else{
			result = binarySearch_plan(input->column_list.at(col_num).Dic.at(input->column_list.at(col_num).columndata.at(i).valueIndex).value, mem, input->column_list.at(col_num).type);
			if (result != -1) vec.at(result) += 1;
			else vec.push_back(1);
		}
	}
}

void aggr_min(vector<float>& vec, vector<char*>& mem, Table* input, int aggr_col, int groupby_col){
	for (long long i=0; i < input->column_list.at(groupby_col).columndata.size(); ++i){
		long long result;
		if (mem.size() == 0){
			mem.push_back(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value);
			vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
		}
		else{
			result = binarySearch_plan(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value, mem, input->column_list.at(groupby_col).type);
			if (result != -1) vec.at(result) = min(vec.at(result), (float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value) );
			else vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
		}
	}
}

void aggr_max(vector<float>& vec, vector<char*>& mem, Table* input, int aggr_col, int groupby_col){
	for (long long i=0; i < input->column_list.at(groupby_col).columndata.size(); ++i){
		long long result;
		if (mem.size() == 0){
			mem.push_back(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value);
			vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
		}
		else{
			result = binarySearch_plan(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value, mem, input->column_list.at(groupby_col).type);
			if (result != -1) vec.at(result) = max(vec.at(result), (float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value) );
			else vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
		}
	}
}

void aggr_sum(vector<float>& vec, vector<char*>& mem, Table* input, int aggr_col, int groupby_col){
	for (long long i=0; i < input->column_list.at(groupby_col).columndata.size(); ++i){
		long long result;
		if (mem.size() == 0){
			mem.push_back(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value);
			vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
		}
		else{
			result = binarySearch_plan(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value, mem, input->column_list.at(groupby_col).type);
			if (result != -1) vec.at(result) += (float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value);
			else vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
		}
	}
}

void aggr_avg(vector<float>& vec, vector<char*>& mem, Table* input, int aggr_col, int groupby_col){
	vector<int> count;
	for (long long i=0; i < input->column_list.at(groupby_col).columndata.size(); ++i){
		long long result;
		if (mem.size() == 0){
			mem.push_back(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value);
			vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
			count.push_back(1);
		}
		else{
			result = binarySearch_plan(input->column_list.at(groupby_col).Dic.at(input->column_list.at(groupby_col).columndata.at(i).valueIndex).value, mem, input->column_list.at(groupby_col).type);
			if (result != -1){
				vec.at(result) = (vec.at(result)*count[result] + (float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value)) / (count[result]+1);
				count[result] += 1;
			}
			else{
				vec.push_back((float)atof(input->column_list.at(aggr_col).Dic.at(input->column_list.at(aggr_col).columndata.at(i).valueIndex).value));
				count.push_back(1);
			}
		}
	}
}

void Operator::aggr(
        Table* output,
        Table* input, 
        vector<int> groupCols,
        vector<AggrCond> conds) {

    // use orderby funtion first
	//	count as same number or condition, work .. and so on
	//

	output->column_list.resize(groupCols.size() + conds.size());
	vector<vector<char*> > value_groupby;
	vector<vector<float> > value_aggr;
	ClockChecker cck;

	cck.SetStartClock();

	value_groupby.resize(conds.size());
	value_aggr.resize(conds.size());
	for (int i=0; i< conds.size(); ++i){
		switch(conds[i].op){
		case COUNT:
			aggr_count(value_aggr.at(i), value_groupby.at(i), input, groupCols[0]);
			break;
		case MIN:
			aggr_min(value_aggr.at(i), value_groupby.at(i), input, conds[i].idxCol, groupCols[0]);
			break;
		case MAX:
			aggr_max(value_aggr.at(i), value_groupby.at(i), input, conds[i].idxCol, groupCols[0]);
			break;
		case AVG:
			aggr_avg(value_aggr.at(i), value_groupby.at(i), input, conds[i].idxCol, groupCols[0]);
			break;
		case SUM:
			aggr_sum(value_aggr.at(i), value_groupby.at(i), input, conds[i].idxCol, groupCols[0]);
			break;
		}
	}

	for (size_t i=0; i < value_aggr.at(0).size(); ++i){
		for (size_t j=0; j < groupCols.size(); ++j){
			output->_UnitInsert(std::string(value_groupby.at(j).at(i)),j,25);
		}
		for (size_t j=0; j < conds.size(); ++j){
            char temp[10];
            sprintf(temp, "%f", value_aggr.at(j).at(i));
			output->_UnitInsert(temp, groupCols.size()+j, 25);
		}
	}

	vector<char> type_output;
	for (int i=0; i< input->column_list.size(); ++i){
		for (size_t j=0; j < groupCols.size(); ++j) type_output.push_back(input->column_list.at(groupCols.at(j)).type);
		for (size_t j=0; j < conds.size(); ++j) type_output.push_back('I');
	}
	output->insert(groupCols.size() + conds.size(), type_output);

	cck.SetEndClock();
	cout << "Aggr time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << '\n';
}

void Operator::print(
        Table* input, 
        int topN) {

	ofstream output("result.txt");
	if (topN == -1 ){
		for (long long i=0; i<input->column_list.at(0).columndata.size(); ++i){
			output << input->column_list.at(0).Dic.at(input->column_list.at(0).columndata.at(i).valueIndex).value;
			if (input->column_list.size() > 1){
				for (long long j=1; j<input->column_list.size(); ++j){
					output << "_" << input->column_list.at(j).Dic.at(input->column_list.at(j).columndata.at(i).valueIndex).value;
				}
			}
			output << '\n';
		}
	}
	else {
		for (long long i=0; i<topN; i++){
			output << input->column_list.at(0).Dic.at(input->column_list.at(0).columndata.at(i).valueIndex).value;
			if (input->column_list.size() > 1){
				for (long long j=1; j<input->column_list.size(); j++){
					output << "_" << input->column_list.at(j).Dic.at(input->column_list.at(j).columndata.at(i).valueIndex).value;
				}
			}
			output << '\n';
		}
	}
	output.close();
}
