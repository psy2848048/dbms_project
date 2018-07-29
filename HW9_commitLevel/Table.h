#include <vector>
#include "Row.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct log_element{
	long t_number;
	char func;
	vector<char*> value;
	log_element* next;
};

class Table{
public:
	vector<Row> row_store;
	void scan(int id1, int id2, int id3);
	void record();
	void recover();
	void printAll();
	void collectGarbage();
};

