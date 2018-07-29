#include "Table.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

void Table::scan(int id1, int id2, int id3){
	ofstream DBoutput("output.csv");
	for (int i = 0; i < row_store.size(); i++) row_store[i].scan(id1, id2, id3, DBoutput);
	DBoutput.close();
}

void Table::record(){
	ofstream DBrecord("DBcurrent.csv");
	for (long long i=0; i < row_store.size(); ++i){
		row_store[i].__scan(0, DBrecord);
		DBrecord << '|';
		row_store[i].__scan(1, DBrecord);
		DBrecord << '|';
		row_store[i].__scan(2, DBrecord);
		DBrecord << '|';
		row_store[i].__scan(3, DBrecord);
		if (i != row_store.size()-1) DBrecord << '\n';
	}
	DBrecord.close();
}
/* depricated

void Table::recover(){
	vector<log_element>* log_store = new vector<log_element>;
	log_store->clear();
	ifstream log_load("log.csv");
	// MAKE LIST OF Tx EXEC
	while(!log_load.eof()){
		log_element* ptr;
		string tx_num;
		string oper;
		string f1, f2, f3, f4;
		string dummy;
		char *_f1, *_f2, *_f3, *_f4;
		getline(log_load, tx_num, '|');
		getline(log_load, oper, '|');
		char _oper = (oper.c_str())[0];
		log_element temp;
		switch(_oper){
		case 's':
			temp.t_number = atol(tx_num.c_str());
			temp.func = 's';
			temp.next = NULL;
			log_store->push_back(temp);
			getline(log_load, dummy, '\n');
			break;
		case 'c':
			ptr = &log_store->at(atol(tx_num.c_str()));
			if (ptr != NULL) while(ptr->next != NULL) ptr = ptr->next;
			ptr->next = new log_element;
			ptr->next->t_number = atol(tx_num.c_str());
			ptr->next->func = 'c';
			ptr->next->next = NULL;
			getline(log_load, dummy, '\n');
			break;
		case 'i':
			ptr = &log_store->at(atol(tx_num.c_str()));
			if (ptr != NULL) while(ptr->next != NULL) ptr = ptr->next;
			ptr->next = new log_element;
			ptr->next->t_number = atol(tx_num.c_str());
			ptr->next->func = 'i';
			ptr->next->next = NULL;
			getline(log_load, f1, '|');
			getline(log_load, f2, '|');
			getline(log_load, f3, '|');
			getline(log_load, f4, '\n');
			_f1 = new char[strlen(f1.c_str())+1];
			_f2 = new char[strlen(f2.c_str())+1];
			_f3 = new char[strlen(f3.c_str())+1];
			_f4 = new char[strlen(f4.c_str())+1];
			strcpy(_f1, f1.c_str());
			strcpy(_f2, f2.c_str());
			strcpy(_f3, f3.c_str());
			strcpy(_f4, f4.c_str());
			ptr->next->value.push_back(_f1);
			ptr->next->value.push_back(_f2);
			ptr->next->value.push_back(_f3);
			ptr->next->value.push_back(_f4);
			break;
		case 'u':
			ptr = &log_store->at(atol(tx_num.c_str()));
			if (ptr != NULL) while(ptr->next != NULL) ptr = ptr->next;
			ptr->next = new log_element;
			ptr->next->t_number = atol(tx_num.c_str());
			ptr->next->func = 'u';
			ptr->next->next = NULL;
			getline(log_load, f1, '|');
			getline(log_load, f2, '|');
			getline(log_load, f3, '|');
			getline(log_load, f4, '\n');
			_f1 = new char[strlen(f1.c_str())+1];
			_f2 = new char[strlen(f2.c_str())+1];
			_f3 = new char[strlen(f3.c_str())+1];
			_f4 = new char[strlen(f4.c_str())+1];
			strcpy(_f1, f1.c_str());
			strcpy(_f2, f2.c_str());
			strcpy(_f3, f3.c_str());
			strcpy(_f4, f4.c_str());
			ptr->next->value.push_back(_f1);
			ptr->next->value.push_back(_f2);
			ptr->next->value.push_back(_f3);
			ptr->next->value.push_back(_f4);
			break;
		}
	}

	// EXEC ACCORDING TO Tx LIST
	// CHECK IF Tx IS COMMITTED or NOT
	

	for(long i=0; i < log_store->size(); ++i){
		log_element *ptr;
		log_element *start_tx;
		ptr = &log_store->at(i);
		start_tx = &log_store->at(i);
		while(ptr->next != NULL){
			ptr = ptr->next;
			if (ptr->func == 'c') break;
		}
		if (ptr->func == 'c'){
			while(start_tx->next != NULL){
				Row row;
				switch(start_tx->func){
				case 's':
					break;
				case 'c':
					break;
				case 'i':
					row.insert(atol(start_tx->value.at(0)), start_tx->value.at(1), start_tx->value.at(2), start_tx->value.at(3));
					row_store.push_back(row);
					break;
				case 'u':
					row_store.at(atol(start_tx->value.at(0))).update(atol(start_tx->value.at(0)), start_tx->value.at(1), start_tx->value.at(2), start_tx->value.at(3));
					break;
				}
				start_tx = start_tx->next;
				if (start_tx->func == 'c') break;
			}
		}
	}
	record();
}

*/

void Table::printAll(){
	Row *ptr;
	for (long i=0; i < row_store.size(); ++i){
		ptr = &row_store.at(i);
		cout << ptr->SSN << "|" << ptr->FirstName << "|" << ptr->LastName << "|" << ptr->city;
		while(1){
			ptr = ptr->next;
			if (ptr == NULL) break;
			cout << "  ->  ";
			cout << ptr->SSN << "|" << ptr->FirstName << "|" << ptr->LastName << "|" << ptr->city;
		}
		cout << '\n';
	}
}

void Table::collectGarbage(){
	Row *ptr, *ptr_temp, *ptr_del;
	for (long i=0; i < row_store.size(); ++i){
		ptr = &row_store.at(i);
		ptr_temp = ptr;
		while(ptr_temp->next != NULL && ptr_temp->next->committed != false) ptr_temp = ptr_temp->next;
		if (ptr_temp != &row_store.at(i)){
			ptr = ptr->next;
			while(ptr != ptr_temp){
				delete ptr->FirstName, ptr->LastName, ptr->city;
				ptr_del = ptr;
				ptr = ptr->next;
				delete ptr_del;
			}
			row_store.at(i).insert(ptr->SSN, ptr->FirstName, ptr->LastName, ptr->city);
			row_store.at(i).committed = ptr->committed;
			row_store.at(i).tx_num = ptr->tx_num;
			row_store.at(i).next = ptr->next;
			delete ptr->FirstName, ptr->LastName, ptr->city;
			delete ptr;
		}
	}
}
