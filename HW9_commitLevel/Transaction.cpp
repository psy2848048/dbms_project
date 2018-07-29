#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <ctime>

using namespace std;

void Transaction::start(){
}

void Transaction::commit(){
	for (long i=0; i < tbl->row_store.size(); ++i){
		Row* ptr = &tbl->row_store.at(i);
		do{
			if (ptr->tx_num == t_number) ptr->committed = true;
			ptr = ptr->next;
		} while(ptr != NULL);
	}
	tbl->record();
}

void Transaction::insert(long f1, char* f2, char* f3, char* f4){
	Row temp;
	temp.insert(f1, f2, f3, f4);
	temp.start_time = clock();
	temp.tx_num = t_number;
	tbl->row_store.push_back(temp);
}

void Transaction::update(long key, long fieldIdx, char* value){
	Row* temp = new Row;
	Row* ptr;
	for (long i=0; i<tbl->row_store.size(); ++i){
		if (tbl->row_store.at(i).SSN == key){
			ptr = &tbl->row_store.at(i);
			break;
		}
	}
	Row* ptr_temp = ptr;
	while(1){
		if (ptr_temp->tx_num == t_number || ptr->committed == true) ptr = ptr_temp;
		if (ptr_temp->next == NULL) break;
		ptr_temp = ptr_temp->next;
	}
    
	temp->SSN = ptr->SSN;
	temp->FirstName = temp->assignVarChar(ptr->FirstName, 30);
	temp->LastName = temp->assignVarChar(ptr->LastName, 30);
	temp->city = temp->assignVarChar(ptr->city, 3);
	switch(fieldIdx){
	case 0:
		temp->SSN = atol(value);
		break;
	case 1:
		temp->FirstName = temp->assignVarChar(value, strlen(value));
		break;
	case 2:
		temp->LastName = temp->assignVarChar(value, strlen(value));
		break;
	case 3:
		temp->city = temp->assignVarChar(value, strlen(value));
		break;
	}
	temp->start_time = clock();
	temp->tx_num = t_number;

	ptr_temp->next = temp;
}

void Transaction::scan(int id1, int id2, int id3){
	tbl->scan(id1, id2, id3);
}

void Transaction::select(long key, long fieldIdx){
	Row *ptr;
	for (long i=0; i<tbl->row_store.size(); ++i){
		if (tbl->row_store.at(i).SSN == key){
			ptr = &tbl->row_store.at(key);
			break;
		}
	}
	Row *ptr_temp = ptr;
	while(1){
		if (ptr_temp->tx_num == t_number || ptr->committed == true) ptr = ptr_temp;
		if (ptr_temp->next == NULL) break;
		ptr_temp = ptr_temp->next;
	}
	
	switch (fieldIdx){
	case 0:
		cout << ptr->SSN << '\n';
		break;
	case 1:
		cout << ptr->FirstName << '\n';
		break;
	case 2:
		cout << ptr->LastName << '\n';
		break;
	case 3:
		cout << ptr->city << '\n';
		break;
	}
}
