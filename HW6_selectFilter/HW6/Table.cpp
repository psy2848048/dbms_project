#include "stdafx.h"
#include "Table.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "ClockChecker.h"

using namespace std;

Table::Table(void){
	SSN.clear();
	SSN_Dic.clear();
	SSN_temp.clear();
	FirstName.clear();
	FirstName_Dic.clear();
	FirstName_temp.clear();
	LastName.clear();
	LastName_Dic.clear();
	LastName_temp.clear();
	DOB.clear();
	DOB_Dic.clear();
	DOB_temp.clear();
	Adress.clear();
	Adress_Dic.clear();
	Adress_temp.clear();
	City.clear();
	City_Dic.clear();
	City_temp.clear();
}

Table::~Table(void){
}

void Table::_UnitInsert(string f1, string f2, string f3, string f4, string f5, string f6){
	SSN_temp.push_back(_atoi64(f1.c_str()));
	FirstName_temp.push_back(assignVarChar(f2, 30));
	LastName_temp.push_back(assignVarChar(f3, 30));
	DOB_temp.push_back(assignVarChar(f4, 8));
	Adress_temp.push_back(assignVarChar(f5, 128));
	City_temp.push_back(assignVarChar(f6, 2));
}

void Table::makeDic(vector<char*>& input, vector<Dic_element_Other>& target){
	long long index = 0;
	char* compare = input[0];

	Dic_element_Other _temp;
	_temp.index = index;
	_temp.value = input[0];
	target.push_back(_temp);

	for (long long i=1; i < input.size(); i++){
		if (strcmp(compare, input[i]) != 0){
			index++;
			Dic_element_Other temp;
			temp.index = index;
			temp.value = input[i];
			compare = input[i];
			target.push_back(temp);
		}
	}
	input.clear();
}

long long binarySearch_other(char* searchValue, vector<Dic_element_Other>& reference);

void Table::DicToStore(vector<char*>& temp, vector<Dic_element_Other>& dic, vector<long long>& store){
//	for(auto it = temp.begin() ; it != temp.end() ; ++it)
//		store.push_back(binarySearch_other(*it,dic));
	for (long long i=0; i< temp.size(); i++){
		store.push_back(binarySearch_other(temp[i], dic));
	}
}

bool comparisonFunc(const char *c1, const char *c2){
    return strcmp(c1, c2) < 0;
}

long long binarySearch_other(char* searchValue, vector<Dic_element_Other>& reference){
	long long first = 0;
	long long last = reference.size() -1;
	long long middle = (first+last)/2;

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
}

long long binarySearch_SSN(long long searchValue, vector<Dic_element_SSN>& reference){
	long long first = 0;
	long long last = reference.size() -1;
	long long middle = (first+last)/2;

	while(first <= last){
		if (reference[middle].value < searchValue) first = middle + 1;
		else if (reference[middle].value == searchValue) break;
		else last = middle -1;

		middle = (first + last) /2;
	}
	if (first > last){
		cout << "There is no value" << endl;
		return -1;
	}
	return reference[middle].index;
}

void Table::insert(){
	vector<long long> SSN_sorted;
	vector<char*> FirstName_sorted;
	vector<char*> LastName_sorted;
	vector<char*> DOB_sorted;
	vector<char*> Adress_sorted;
	vector<char*> City_sorted;

	ClockChecker cck;

	for (long long i=0; i< SSN_temp.size(); i++) SSN_sorted.push_back(SSN_temp.at(i));
	for (long long i=0; i< FirstName_temp.size(); i++) FirstName_sorted.push_back(FirstName_temp.at(i));
	for (long long i=0; i< LastName_temp.size(); i++) LastName_sorted.push_back(LastName_temp.at(i));
	for (long long i=0; i< DOB_temp.size(); i++) DOB_sorted.push_back(DOB_temp.at(i));
	for (long long i=0; i< Adress_temp.size(); i++) Adress_sorted.push_back(Adress_temp.at(i));
	for (long long i=0; i< City_temp.size(); i++) City_sorted.push_back(City_temp.at(i));

	cck.SetStartClock();
	sort(SSN_sorted.begin(), SSN_sorted.end());
	sort(FirstName_sorted.begin(), FirstName_sorted.end(), comparisonFunc);
	sort(LastName_sorted.begin(), LastName_sorted.end(), comparisonFunc);
	sort(DOB_sorted.begin(), DOB_sorted.end(), comparisonFunc);
	sort(Adress_sorted.begin(), Adress_sorted.end(), comparisonFunc);
	sort(City_sorted.begin(), City_sorted.end(), comparisonFunc);
	cck.SetEndClock();

	cout << "Sorting time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;
	
	cck.SetStartClock();
	long long index_SSN = 0;
	long long compare = SSN_sorted[0];
	Dic_element_SSN _temp;
	_temp.index = index_SSN;
	_temp.value = SSN_sorted[0];
	SSN_Dic.push_back(_temp);
	for (long long i=1; i < SSN_sorted.size(); i++){// need to revise
		if (compare != SSN_sorted[i]){
			index_SSN++;
			Dic_element_SSN temp;
			temp.index = index_SSN;
			temp.value = SSN_sorted[i];
			compare = SSN_sorted[i];
			SSN_Dic.push_back(temp);
		}
	}
	SSN_sorted.clear();
	
	makeDic(FirstName_sorted, FirstName_Dic);
	makeDic(LastName_sorted, LastName_Dic);
	makeDic(DOB_sorted, DOB_Dic);
	makeDic(Adress_sorted, Adress_Dic);
	makeDic(City_sorted, City_Dic);
	cck.SetEndClock();

	cout << "Dictionary making : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;

	cck.SetStartClock();
	for (long long i=0; i< SSN_temp.size(); i++) SSN.push_back(binarySearch_SSN(SSN_temp[i], SSN_Dic));
	for (long long i=0; i< SSN_temp.size(); i++) SSN_temp.pop_back();

	DicToStore(FirstName_temp, FirstName_Dic, FirstName);
	DicToStore(LastName_temp, LastName_Dic, LastName);
	DicToStore(DOB_temp, DOB_Dic, DOB);
	DicToStore(Adress_temp, Adress_Dic, Adress);
	DicToStore(City_temp, City_Dic, City);
	cck.SetEndClock();

	cout << "Dictionary to Column : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;

	return;
}

void Table::select(vector<int> fid, int column_no, int oper, char* value, ofstream& output_file){
	vector<long long>* column1;
	vector<long long>* column2;
	vector<long long>* column3;

	vector<Dic_element_SSN>* dic1_SSN = NULL;
	vector<Dic_element_Other>* dic1_Other = NULL;
	vector<Dic_element_SSN>* dic2_SSN = NULL;
	vector<Dic_element_Other>* dic2_Other = NULL;
	vector<Dic_element_SSN>* dic3_SSN = NULL;
	vector<Dic_element_Other>* dic3_Other = NULL;

	column1 = __scan_table(fid[0]);
	if (fid[0] != 0) dic1_Other = __scan_Other_dic(fid[0]);
	else dic1_SSN = __scan_SSN_dic(fid[0]);

	column2 = __scan_table(fid[1]);
	if (fid[1] != 0) dic2_Other = __scan_Other_dic(fid[1]);
	else dic2_SSN = __scan_SSN_dic(fid[1]);

	column3 = __scan_table(fid[2]);
	if (fid[2] != 0) dic3_Other = __scan_Other_dic(fid[2]);
	else dic3_SSN = __scan_SSN_dic(fid[2]);

	vector<long long>* reference = NULL;
	vector<Dic_element_Other>* reference_DIC = NULL;
	vector<Dic_element_SSN>* reference_DIC_SSN = NULL;
	reference = __scan_table(column_no);
	if (column_no != 0) reference_DIC = __scan_Other_dic(column_no);
	else reference_DIC_SSN = __scan_SSN_dic(column_no);

	switch (oper){
	case 0:
		for (long long i=0; i< column1->size(); i++){
			if (dic1_SSN != NULL && dic1_Other == NULL){
				output_file << dic1_SSN->at(column1->at(i)).value;
			}
			else if (dic1_SSN == NULL && dic1_Other != NULL){
				output_file << dic1_Other->at(column1->at(i)).value;
			}
			output_file << "_";
			if (dic2_SSN != NULL && dic2_Other == NULL){
				output_file << dic2_SSN->at(column2->at(i)).value;
			}
			else if (dic2_SSN == NULL && dic2_Other != NULL){
				output_file << dic2_Other->at(column2->at(i)).value;
			}
			output_file << "_";
			if (dic3_SSN != NULL && dic3_Other == NULL){
				output_file << dic3_SSN->at(column3->at(i)).value;
			}
			else if (dic3_SSN == NULL && dic3_Other != NULL){
				output_file << dic3_Other->at(column3->at(i)).value;
			}
			output_file << endl;
		}
		break;
	case 1:
		for (long long i=0; i< column1->size(); i++){
			if (reference_DIC_SSN != NULL && reference_DIC == NULL){
				if (reference_DIC_SSN->at(reference->at(i)).value == _atoi64(value)){
					if (dic1_SSN != NULL && dic1_Other == NULL){
						output_file << dic1_SSN->at(column1->at(i)).value;
					}
					else if (dic1_SSN == NULL && dic1_Other != NULL){
						output_file << dic1_Other->at(column1->at(i)).value;
					}
					output_file << "_";
					if (dic2_SSN != NULL && dic2_Other == NULL){
						output_file << dic2_SSN->at(column2->at(i)).value;
					}
					else if (dic2_SSN == NULL && dic2_Other != NULL){
						output_file << dic2_Other->at(column2->at(i)).value;
					}
					output_file << "_";
					if (dic3_SSN != NULL && dic3_Other == NULL){
						output_file << dic3_SSN->at(column3->at(i)).value;
					}
					else if (dic3_SSN == NULL && dic3_Other != NULL){
						output_file << dic3_Other->at(column3->at(i)).value;
					}
					output_file << endl;
				}
			}
			else if (reference_DIC_SSN == NULL && reference_DIC != NULL){
				if (reference_DIC->at(reference->at(i)).value == value){
					if (dic1_SSN != NULL && dic1_Other == NULL){
						output_file << dic1_SSN->at(column1->at(i)).value;
					}
					else if (dic1_SSN == NULL && dic1_Other != NULL){
						output_file << dic1_Other->at(column1->at(i)).value;
					}
					output_file << "_";
					if (dic2_SSN != NULL && dic2_Other == NULL){
						output_file << dic2_SSN->at(column2->at(i)).value;
					}
					else if (dic2_SSN == NULL && dic2_Other != NULL){
						output_file << dic2_Other->at(column2->at(i)).value;
					}
					output_file << "_";
					if (dic3_SSN != NULL && dic3_Other == NULL){
						output_file << dic3_SSN->at(column3->at(i)).value;
					}
					else if (dic3_SSN == NULL && dic3_Other != NULL){
						output_file << dic3_Other->at(column3->at(i)).value;
					}
					output_file << endl;
				}
			}
		}
		break;
	case 2:
		for (long long i=0; i< column1->size(); i++){
			if (reference_DIC_SSN != NULL && reference_DIC == NULL){
				if (reference_DIC_SSN->at(reference->at(i)).value >= _atoi64(value)){
					if (dic1_SSN != NULL && dic1_Other == NULL){
						output_file << dic1_SSN->at(column1->at(i)).value;
					}
					else if (dic1_SSN == NULL && dic1_Other != NULL){
						output_file << dic1_Other->at(column1->at(i)).value;
					}
					output_file << "_";
					if (dic2_SSN != NULL && dic2_Other == NULL){
						output_file << dic2_SSN->at(column2->at(i)).value;
					}
					else if (dic2_SSN == NULL && dic2_Other != NULL){
						output_file << dic2_Other->at(column2->at(i)).value;
					}
					output_file << "_";
					if (dic3_SSN != NULL && dic3_Other == NULL){
						output_file << dic3_SSN->at(column3->at(i)).value;
					}
					else if (dic3_SSN == NULL && dic3_Other != NULL){
						output_file << dic3_Other->at(column3->at(i)).value;
					}
					output_file << endl;
				}
			}
			else if (reference_DIC_SSN == NULL && reference_DIC != NULL){
				if (reference_DIC->at(reference->at(i)).value >= value){
					if (dic1_SSN != NULL && dic1_Other == NULL){
						output_file << dic1_SSN->at(column1->at(i)).value;
					}
					else if (dic1_SSN == NULL && dic1_Other != NULL){
						output_file << dic1_Other->at(column1->at(i)).value;
					}
					output_file << "_";
					if (dic2_SSN != NULL && dic2_Other == NULL){
						output_file << dic2_SSN->at(column2->at(i)).value;
					}
					else if (dic2_SSN == NULL && dic2_Other != NULL){
						output_file << dic2_Other->at(column2->at(i)).value;
					}
					output_file << "_";
					if (dic3_SSN != NULL && dic3_Other == NULL){
						output_file << dic3_SSN->at(column3->at(i)).value;
					}
					else if (dic3_SSN == NULL && dic3_Other != NULL){
						output_file << dic3_Other->at(column3->at(i)).value;
					}
					output_file << endl;
				}
			}
		}
		break;
	case 3:
		for (long long i=0; i< column1->size(); i++){
			if (reference_DIC_SSN != NULL && reference_DIC == NULL){
				if (reference_DIC_SSN->at(reference->at(i)).value <= _atoi64(value)){
					if (dic1_SSN != NULL && dic1_Other == NULL){
						output_file << dic1_SSN->at(column1->at(i)).value;
					}
					else if (dic1_SSN == NULL && dic1_Other != NULL){
						output_file << dic1_Other->at(column1->at(i)).value;
					}
					output_file << "_";
					if (dic2_SSN != NULL && dic2_Other == NULL){
						output_file << dic2_SSN->at(column2->at(i)).value;
					}
					else if (dic2_SSN == NULL && dic2_Other != NULL){
						output_file << dic2_Other->at(column2->at(i)).value;
					}
					output_file << "_";
					if (dic3_SSN != NULL && dic3_Other == NULL){
						output_file << dic3_SSN->at(column3->at(i)).value;
					}
					else if (dic3_SSN == NULL && dic3_Other != NULL){
						output_file << dic3_Other->at(column3->at(i)).value;
					}
					output_file << endl;
				}
			}
			else if (reference_DIC_SSN == NULL && reference_DIC != NULL){
				if (reference_DIC->at(reference->at(i)).value <= value){
					if (dic1_SSN != NULL && dic1_Other == NULL){
						output_file << dic1_SSN->at(column1->at(i)).value;
					}
					else if (dic1_SSN == NULL && dic1_Other != NULL){
						output_file << dic1_Other->at(column1->at(i)).value;
					}
					output_file << "_";
					if (dic2_SSN != NULL && dic2_Other == NULL){
						output_file << dic2_SSN->at(column2->at(i)).value;
					}
					else if (dic2_SSN == NULL && dic2_Other != NULL){
						output_file << dic2_Other->at(column2->at(i)).value;
					}
					output_file << "_";
					if (dic3_SSN != NULL && dic3_Other == NULL){
						output_file << dic3_SSN->at(column3->at(i)).value;
					}
					else if (dic3_SSN == NULL && dic3_Other != NULL){
						output_file << dic3_Other->at(column3->at(i)).value;
					}
					output_file << endl;
				}
			}
		}
		break;
	default:
		cout << "You inserted wrong number. Please check input number" << endl;
		break;
	}
}

vector<long long>* Table::__scan_table(int fid){
	switch(fid){
	case 0: 
		return &SSN;
	case 1: 
		return &FirstName;
	case 2: 
		return &LastName;
	case 3: 
		return &DOB;
	case 4: 
		return &Adress;
	case 5: 
		return &City;
	default: 
		cout << endl << "Incorrect column indicator inputted" << endl;
		break;
	}
}

vector<Dic_element_SSN>* Table::__scan_SSN_dic(int fid){
	if (fid == 0) return &SSN_Dic;
}

vector<Dic_element_Other>* Table::__scan_Other_dic(int fid){
	switch(fid){
	case 1: 
		return &FirstName_Dic;
	case 2: 
		return &LastName_Dic;
	case 3: 
		return &DOB_Dic;
	case 4: 
		return &Adress_Dic;
	case 5: 
		return &City_Dic;
	default: 
		cout << endl << "Incorrect column indicator inputted" << endl;
		break;
	}
}

char* Table::assignVarChar(string f, int _size){
	int char_Size = strlen((const char*)f.c_str());
	char* ret_val;
	if (char_Size < _size) {
		ret_val = new char[char_Size+1];
		strcpy_s(ret_val, char_Size+1, f.c_str());
	}
	else {
		ret_val = new char[_size+1];
		strncpy_s(ret_val, _size+1, f.c_str(), _size);
		ret_val[_size] = '\0';
	}
	return ret_val;
}