#include "Transaction.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdio>

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

int main(int argc, char* argv[]){
	Table* tbl = new Table;
	tbl->row_store.clear();

	// PLEASE, INSERT ADRESS OF TABLE and Tx_NUM WHEN YOU CONSTRUCT A 'Transaction' OBJECT
	Transaction tx0(tbl, 0);
	Transaction tx1(tbl, 1);
	Transaction tx2(tbl, 2);
	// more Txs

	int arg = atoi(argv[1]);
	std::cout << "LOG DATA : log.csv" << endl;
	std::cout << "DB BACKUP : DBcurrent.csv" << endl;
	if (arg == 0){
		cout << "NORMAL MODE" << endl;
		tx0.start();
		tx0.insert(0, "Geore", "Han","19101231", "SUWON YONNGTONG", "SW");
		tx0.commit();
		tx1.start();
		tx1.insert(1, "Yong", "Cho", "19901112", "Nowon", "SE");
		tx1.update(0, "Geori", "Paek","19101231", "SUWON YONNGTONG", "SW");
		tx2.start();
		tx1.insert(2, "Jun-hang", "Lee", "19880531", "Hongseong", "HS");
		tx2.insert(3, "K", "S", "19590423", "Gwank", "GW");
		tx1.update(1, "Geori", "Paek","19101231", "SUWON YONNGTONG", "SW");
		tx0.scan(0,1,2);
		//tx2.commit();
		//tx1.commit();
		// ...
		//exit(1); // crash
	}
	else if (arg == 1){
		cout << "RECOVERY MODE" << endl;
		tbl->recover();
	}
	else if (arg == 2){
		if (remove("log.csv") == 0) cout << "File has successfully deleted!" << '\n';
	}
	else{
		cout << "Wrong input" << '\n';
	}

	std::cout << "Test finished. You may press ENTER to terminate the program!" << '\n' << "Output data is located in [current_directory]/output.txt" << endl;
	getchar();

	for (int i = 0; i < tbl->row_store.size(); i++) tbl->row_store.pop_back();
	delete tbl;
	return 0;
}
