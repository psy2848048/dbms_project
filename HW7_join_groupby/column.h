#pragma once
#include <vector>

using namespace std;

typedef struct{
	long long index;
	char* value;
} tempElement;

typedef struct{
	long long index;
	long long valueIndex;
} columnElement;
class column{
public:
	column(void);
	~column(void);
	char type;
	vector<columnElement> columndata;
	vector<tempElement> Dic;
	vector<tempElement> tempStoreOriginal;
};
