#include <vector>
#include "Row.h"
#include "Table.h"

using namespace std;

class Transaction{
public:
	void start();
	void update(long f1, char* f2, char* f3, char* f4, char* f5, char* f6);
	void commit();
	void insert(long f1, char* f2, char* f3, char* f4, char* f5, char* f6);
	void scan(int id1, int id2, int id3);
	Table* tbl;

	Transaction(Table* id, long num){
		tbl = id;
		t_number = num;
	}
	~Transaction(void){}
	long t_number;
};
