#include <vector>
#include "Table.h"

using namespace std;

class Transaction{
public:
	void start();
	void update(long key, long fieldIdx, char* value);
	void commit();
	void insert(long f1, char* f2, char* f3, char* f4);
	void scan(int id1, int id2, int id3);
	void select(long key, long fieldIdx);
	Table* tbl;

	Transaction(Table* id, long num){
		tbl = id;
		t_number = num;
	}
	~Transaction(void){}
	long t_number;
};
