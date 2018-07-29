// HW6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Table.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "ClockChecker.h"

using namespace std;

enum RelOp{
	Nothing = 0,
	EQ = 1,
	GEQ = 2,
	LEQ = 3
};

int main(int argc, _TCHAR* argv[]){
	Table column_store;
	ifstream insert_file((char *)argv[1]);

	ClockChecker cck;
	ClockChecker cck2;
	cck.SetStartClock();
	string _SSN;
	string _FirstName;
	string _LastName;
	string _DOB;
	string _Adress;
	string _city;
	Table temp;
	ofstream output_file2("report.txt");

	while(!insert_file.eof()){
		getline(insert_file, _SSN, '|');
		getline(insert_file, _FirstName, '|');
		getline(insert_file, _LastName, '|');
		getline(insert_file, _DOB, '|');
		getline(insert_file, _Adress, '|');
		getline(insert_file, _city, '\n');
		column_store._UnitInsert(_SSN, _FirstName, _LastName, _DOB, _Adress, _city);
	}
	cck.SetEndClock();
	cout << "File I/O time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;
	cck.SetStartClock();
	column_store.insert();
	cck.SetEndClock();

	cout << "Dictionarying time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;
	int id1 = atoi((const char*)argv[2]);
	int id2 = atoi((const char*)argv[3]);
	int id3 = atoi((const char*)argv[4]);

	ofstream output_file("output.txt");
	vector<int> columnNumber;
	columnNumber.clear();
	columnNumber.push_back(id1);
	columnNumber.push_back(id2);
	columnNumber.push_back(id3);

	cck2.SetStartClock();
	column_store.select(columnNumber, 0, GEQ, "2946584165915", output_file);
	cck2.SetEndClock();
	cout << "Select time : " << (double)cck2.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;
	output_file.close();

	cout << "Test finished. You may press ENTER to terminate the program!" << endl << "Output data is located in [current_directory]/output.txt" << endl;
	getchar();
	return 0;
}

