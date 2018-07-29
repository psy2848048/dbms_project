// HW4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

class ClockChecker{
private :
	clock_t startClock;
	clock_t endClock;

public:
	void SetStartClock(){
		startClock = clock();
	}
	void SetEndClock(){
		endClock = clock();
	}
	clock_t ElapsedClock(){
		return (endClock - startClock);
	}
};

class Table {
	public:
		Table(){ PAGE_SIZE=4096; }
		// ~Table(){ delete[] SSN; delete[] FirstName; delete[] LastName; delete[] DOB; delete[] Adress; delete[] city; }
		
		void insert(string f1, string f2, string f3, string f4, string f5, string f6){
			strcpy_s(SSN, f1.c_str());
			FirstName = assignVarChar(f2, 30);
			LastName = assignVarChar(f3, 30);
			strcpy_s(DOB, f4.c_str());
			Adress = assignVarChar(f5, 128);
			strcpy_s(city, f6.c_str());
		}
		
		void scan(int fid1, int fid2, int fid3, ofstream& output_file){
			__scan(fid1, output_file);
			output_file << '_';
			__scan(fid2, output_file);
			output_file << '_';
			__scan(fid3, output_file);
			output_file << endl;
		}

		void __scan(int fid, ofstream& output_file){
			switch(fid){
			case 0: 
				output_file << SSN;
				break; // this needs more improvement to print whole char array
			case 1: 
				output_file << FirstName;
				break;
			case 2: 
				output_file << LastName;
				break;
			case 3: 
				output_file << DOB;
				break;
			case 4: 
				output_file << Adress;
				break;
			case 5: 
				output_file << city;
				break;
			default: 
				cout << endl << "Incorrect column indicator inputted" << endl;
				break;
			}
		}
		

	private:
		int PAGE_SIZE;// Bytes
		
		char SSN[14];
		char* FirstName;
		char* LastName;
		char DOB[9];
		char* Adress;
		char city[3];

		char* assignVarChar(string f, int _size){
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
};

int main(int argc, _TCHAR* argv[]){
	vector<Table> row_store;
	ifstream insert_file((char *)argv[1]);
	row_store.clear();

	ClockChecker cck;
	ClockChecker cck2;
	cck.SetStartClock();
	while(!insert_file.eof()){
		string _SSN;
		string _FirstName;
		string _LastName;
		string _DOB;
		string _Adress;
		string _city;
		Table temp;
		
		getline(insert_file, _SSN, '|');
		getline(insert_file, _FirstName, '|');
		getline(insert_file, _LastName, '|');
		getline(insert_file, _DOB, '|');
		getline(insert_file, _Adress, '|');
		getline(insert_file, _city, '\n');
		temp.insert(_SSN, _FirstName, _LastName, _DOB, _Adress, _city);
		row_store.push_back(temp);
	}
	cck.SetEndClock();

	cout << "Insertion time : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;

	int id1 = atoi((const char*)argv[2]);
	int id2 = atoi((const char*)argv[3]);
	int id3 = atoi((const char*)argv[4]);
	int count = row_store.size();

	while(1){
		ofstream output_file("output.txt");
		int a, b, c;
		cout << "input column number" << endl;
		cin >> a >> b >> c;
		if (a >= 6) break;
		cck2.SetStartClock();
		for (int i = 0; i < count; i++) row_store[i].scan(a, b, c, output_file);
		cck2.SetEndClock();
		cout << "Scan time : " << (double)cck2.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" << endl;
		output_file.close();
	}

	cout << "Test finished. You may press ENTER to terminate the program!" << endl << "Output data is located in [current_directory]\output.txt" << endl;
	getchar();

	for (int i = 0; i < count; i++) row_store.pop_back();
	return 0;
}