#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

class Row{
	public:
		Row(){ PAGE_SIZE=4096; }
		void insert(long f1, string f2, string f3, string f4, string f5, string f6);
		void scan(int fid1, int fid2, int fid3, ofstream& output_file);
		void __scan(int fid, ofstream& output_file);
		void update(long f1, string f2, string f3, string f4, string f5, string f6);
		void recover();

	private:
		int PAGE_SIZE;// Bytes
		long SSN;
		char* FirstName;
		char* LastName;
		char* DOB;
		char* Adress;
		char* city;
		char* assignVarChar(string f, int _size);
};
