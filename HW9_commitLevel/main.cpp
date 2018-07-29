#include "Transaction.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	Table* tbl = new Table;
	ifstream insert_file("small.csv");
	tbl->row_store.clear();

	while(!insert_file.eof()){
		string _SSN;
		string _FirstName;
		string _LastName;
		string _city;
		Row temp;
		
		getline(insert_file, _SSN, '|');
		getline(insert_file, _FirstName, '|');
		getline(insert_file, _LastName, '|');
		getline(insert_file, _city, '\n');
		temp.insert(_SSN, _FirstName, _LastName, _city);
		temp.committed = true;
		temp.tx_num = 0;
		tbl->row_store.push_back(temp);
	}
	
	Transaction tx0(tbl,0);
	Transaction tx1(tbl,1);
	Transaction tx2(tbl,2);

	// Tx SPACE
	tx0.start();
	tx0.update(1, 2, "HAN");
	tx0.select(1, 2);
	tx0.select(1, 1);
	tx0.select(1, 3);
	getchar();
	tx1.start();
	tx0.update(3, 2, "LEE");
	
	tx1.select(1,2);
	tx0.commit();
	tx1.select(1,2);
	tx2.start();
	tx1.update(0, 1,"btr");
	tx2.select(0, 1);
	tx2.commit();
	tx1.select(0, 1);
	tx1.commit();
	
	cout << "tx order good" << endl;
	getchar();
	
	tbl->printAll();
	tbl->collectGarbage();
	tbl->printAll();
	
	//

	cout << "Test finished. You may press ENTER to terminate the program!" << endl << "Output data is located in [current_directory]/output.txt" << endl;
	getchar();

	return 0;
}
