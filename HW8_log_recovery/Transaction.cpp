#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;

void Transaction::start(){
	ofstream log_file("log.csv", std::ios_base::out | std::ios_base::app);
	log_file << t_number << "|s|" << '\n';
	log_file.close();
}

void Transaction::commit(){
	ofstream log_file("log.csv", std::ios_base::out | std::ios_base::app);
	log_file << t_number << "|c|" << '\n';
	log_file.close();
	tbl->record();
}

void Transaction::insert(long f1, char* f2, char* f3, char* f4, char* f5, char* f6){
	ofstream log_file("log.csv", std::ios_base::out | std::ios_base::app);
	log_file << t_number << "|i|" << f1 << "|" << f2 << "|" << f3 << "|" << f4 << "|" << f5 << "|" << f6 << "\n";
	Row temp;
	temp.insert(f1, f2, f3, f4, f5, f6);
	tbl->row_store.push_back(temp);
	tbl->record();
	log_file.close();
}

void Transaction::update(long f1, char* f2, char* f3, char* f4, char* f5, char* f6){
	ofstream log_file("log.csv", std::ios_base::out | std::ios_base::app);
	log_file << t_number << "|u|" << f1 << "|" << f2 << "|" << f3 << "|" << f4 << "|" << f5 << "|" << f6 << "\n";
	tbl->row_store.at(f1).update(f1, f2, f3, f4, f5, f6);
	tbl->record();
	log_file.close();
}

void Transaction::scan(int id1, int id2, int id3){
	tbl->scan(id1, id2, id3);
}
