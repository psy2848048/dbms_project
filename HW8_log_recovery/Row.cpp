#include "Row.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

void Row::insert(long f1, string f2, string f3, string f4, string f5, string f6){
	SSN = f1;
	FirstName = assignVarChar(f2, 30);
	LastName = assignVarChar(f3, 30);
	DOB =  assignVarChar(f4, 8);
	Adress = assignVarChar(f5, 128);
	city = assignVarChar(f6, 2);
}

void Row::update(long f1, string f2, string f3, string f4, string f5, string f6){
	delete FirstName, LastName, DOB, Adress, city;
	SSN = f1;
	FirstName = assignVarChar(f2, 30);
	LastName = assignVarChar(f3, 30);
	DOB =  assignVarChar(f4, 8);
	Adress = assignVarChar(f5, 128);
	city = assignVarChar(f6, 2);
}

void Row::scan(int fid1, int fid2, int fid3, ofstream& output_file){
	__scan(fid1, output_file);
	output_file << '_';
	__scan(fid2, output_file);
	output_file << '_';
	__scan(fid3, output_file);
	output_file << endl;
}

void Row::__scan(int fid, ofstream& output_file){
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

char* Row::assignVarChar(string f, int _size){
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
