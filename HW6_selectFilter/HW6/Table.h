#pragma once
#include <vector>

using namespace std;

typedef struct{
	long long index;
	long long value;
} Dic_element_SSN;

typedef struct{
	long long index;
	char* value;
} Dic_element_Other;

class Table{
public:
	Table(void);
	~Table(void);
	void _UnitInsert(string f1, string f2, string f3, string f4, string f5, string f6);
	void insert();
	void makeDic(vector<char*>& input, vector<Dic_element_Other>& target);
	void DicToStore(vector<char*>& temp, vector<Dic_element_Other>& dic, vector<long long>& store);
	vector<long long>* __scan_table(int fid);
	vector<Dic_element_Other>* Table::__scan_Other_dic(int fid);
	vector<Dic_element_SSN>* Table::__scan_SSN_dic(int fid);
	void select(vector<int> fid, int column_no, int oper, char* value, ofstream& output_file);


private:
	vector<long long> SSN;
	vector<Dic_element_SSN> SSN_Dic;
	vector<long long> SSN_temp;
	vector<long long> FirstName;
	vector<Dic_element_Other> FirstName_Dic;
	vector<char*> FirstName_temp;
	vector<long long> LastName;
	vector<Dic_element_Other> LastName_Dic;
	vector<char*> LastName_temp;
	vector<long long> DOB;
	vector<Dic_element_Other> DOB_Dic;
	vector<char*> DOB_temp;
	vector<long long> Adress;
	vector<Dic_element_Other> Adress_Dic;
	vector<char*> Adress_temp;
	vector<long long> City;
	vector<Dic_element_Other> City_Dic;
	vector<char*> City_temp;

	char* assignVarChar(string f, int _size);
};
