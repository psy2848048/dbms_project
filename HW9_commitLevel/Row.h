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

class Row{
	public:
		Row(){committed=false; next=NULL;}
		void insert(string f1, string f2, string f3, string f4);
		void insert(long f1, string f2, string f3, string f4);
		void scan(int fid1, int fid2, int fid3, ofstream& output_file);
		void __scan(int fid, ofstream& output_file);
		//void update(long f1, string f2, string f3, string f4); depricated
		void recover();
		
		long SSN;
		char* FirstName;
		char* LastName;
		char* city;
		long tx_num;
		clock_t start_time;
		bool committed;
		Row* next;
		char* assignVarChar(string f, int _size);
};
