#include "Plan.h"
#include "Table.h"
#include "column.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "ClockChecker.h"

using namespace std;

/* Table schema
 * create table LINEITEM (
 *      L_ORDERKEY int,         // 0
 *      L_PARTKEY int,          // 1
 *      L_QUANTITY float,       // 2
 *      L_DISCOUNT float,       // 3
 *      L_SHIPDATE char(10),    // 4
 *      L_RECEIPDATE char(10)   // 5
 * );
 *
 * create table ORDERS (
 *      O_ORDERKEY int,         // 0
 *      O_CUSTKEY int,          // 1
 *      O_TOTALPRICE float,     // 2
 *      O_ORDERDATE char(10)    // 3
 * );
 *
 * create table CUSTOMER (
 *      C_CUSTKEY int,          // 0
 *      C_NAME varchar(25),     // 1
 *      C_MKTSEGMENT char(10)   // 2
 * );
 */


/*
 * ########## A SIMPLE QUERY TO UNDERSTAIND SKELETON CODE ##########
 * SELECT TOP 10 l_orderkey, l_discount
 * FROM lineitem
 * WHERE l_shipdate < '1998-07-01';
 */

void plan1(Table* lineitem, Table* tmp1) {
    vector<SelectCond> conds;
    // l_shipdate(4th column) <(Less Than) '1998-07-01'
    conds.push_back(SelectCond(4, LT, "1998-07-01"));

    vector<int> projs;
    // SELECT l_orderkey(0th column), l_discount(3th column)
    projs.push_back(0);
    projs.push_back(3);

    // SELECT ... FROM lineitem --> tmp1
    Operator::selection(tmp1, lineitem, conds, projs);

    // TOP 10
    Operator::print(tmp1, 10);
}


/*
 * ###### SIMPLE JOIN ######
 * SELECT TOP 5 o_orderkey, o_totalprice
 * FROM orders, customer
 * WHERE o_custkey = c_custkey;
 */

void plan2(Table* orders, Table* customer, Table* tmp1) {
    /*vector<SelectCond> conds_sel;
	conds_sel.push_back(SelectCond());
    vector<int> projs;
    // SELECT o_orderkey, o_totalprice, o_custkey
    projs.push_back(0);
    projs.push_back(2);
    projs.push_back(1);

    // SELECT ... FROM orders --> tmp1
    Operator::selection(tmp1, orders, conds_sel, projs);*/
    //==-----------------------------------------------------------------------
    //==-----------------------------------------------------------------------

    vector<JoinCond> conds_join;
    // WHERE o_custkey(3rd column of tmp1) = c_custkey(0th column of customer)
    conds_join.push_back(JoinCond(1, EQ, 0));

    vector<int> projs2;
    // SELECT o_orderkey(1st column of tmp1, o_totalprice(2nd column of tmp1)
    projs2.push_back(0);
    projs2.push_back(1);

	vector<int> projs_l;
	projs_l.push_back(0);
	projs_l.push_back(1);
	projs_l.push_back(2);

    // SELECT ... FROM tmp1, customer --> tmp2
	Operator::join(tmp1, orders, customer, conds_join, projs_l, projs2);

    // TOP 5
    Operator::print(tmp1, 5);
}

/*
 * ############# AGGREGATION WITH GROUP BY + JOIN ############
 * SELECT TOP 5 l_shipdate, SUM(l_quantity), MAX(l_discount)
 * FROM lineitem, orders, customer
 * WHERE c_mktsegment = 'BUILDING'
 *      AND l_orderkey = o_orderkey
 *      AND o_custkey = c_custkey
 * GROUP BY l_shipdate
 * ORDER BY l_shipdate desc;
 */

void plan3(Table* lineitem, Table* orders, Table* customer, Table* cust_1,
        Table* joined_l_o, Table* joined_l_o_c, Table* aggregated, Table* final) {
    vector<SelectCond> selCond;
    // c_mktsegment = 'BUILDING'
    selCond.push_back(SelectCond(2, EQ, "BUILDING"));
    vector<int> selProj;
    // SELECT c_custkey
    selProj.push_back(0);

    // SELECT ... FROM customer -->cust_1 
    Operator::selection(cust_1, customer, selCond, selProj);

    //==-----------------------------------------------------------------------
    //==-----------------------------------------------------------------------

    vector<JoinCond> joinCond1;
    // WHERE l_orderkey = o_orderkey
    joinCond1.push_back(JoinCond(0, EQ, 0));

    vector<int> joinProj1_l;
    // SELECT l_shipdate, l_quantity, l_discount
    joinProj1_l.push_back(4);
    joinProj1_l.push_back(2);
    joinProj1_l.push_back(3);

    vector<int> joinProj1_r;
    // SELECT o_custkey
    joinProj1_r.push_back(1);

    // SELECT ... FROM lineitem, orders --> joined_l_o
    Operator::join(joined_l_o, lineitem, orders, joinCond1, joinProj1_l, joinProj1_r);
	
    //==-----------------------------------------------------------------------
    //==-----------------------------------------------------------------------

    vector<JoinCond> joinCond2;
    // WHERE o_custkey(4th column of joined_l_o) = c_custkey
    joinCond2.push_back(JoinCond(3, EQ, 0));

    vector<int> joinProj2_l;
    vector<int> joinProj2_r;
    // SELECT l_shipdate, l_quantity, l_discount
    joinProj2_l.push_back(0);
    joinProj2_l.push_back(1);
    joinProj2_l.push_back(2);
	joinProj2_r.push_back(0);
	
    // SELECT ... FROM joined_l_o, cust_1 --> joined_l_o_c
    Operator::join(joined_l_o_c, joined_l_o, cust_1, joinCond2, joinProj2_l, joinProj2_r);

    //==-----------------------------------------------------------------------
    //==-----------------------------------------------------------------------
    
    // GROUP BY l_shipdate
    vector<int> groupCols;
    vector<int> projCols;
    groupCols.push_back(0);

    // SUM(l_quantity), MAX(l_discount)
    vector<AggrCond> aggrCond;
    aggrCond.push_back(AggrCond(1, SUM));
    aggrCond.push_back(AggrCond(2, MAX));

    Operator::aggr(aggregated, joined_l_o_c, groupCols, aggrCond);


    //==-----------------------------------------------------------------------
    //==-----------------------------------------------------------------------

    // ORDER BY l_shipdate desc
    vector<OrderCond> orderCond;
    orderCond.push_back(OrderCond(0, true));

    Operator::orderBy(final, aggregated, orderCond);


    //==-----------------------------------------------------------------------
    //==-----------------------------------------------------------------------

    // TOP 5
    Operator::print(final, 5);
}

int main() {

	// Need : type vector<char> for define type of each column
	Table lineitem;
	ifstream insert_file("lineitem.tbl");

	ClockChecker cck;
	ClockChecker cck2;
	cck.SetStartClock();

	string _orderKey, _partKey, _quantity, _discount, _shipDate, _receiptDate, _dummy;
	lineitem.column_list.resize(6);

	while(!insert_file.eof()){
		getline(insert_file, _orderKey, '|');
		getline(insert_file, _partKey, '|');
		getline(insert_file, _quantity, '|');
		getline(insert_file, _discount, '|');
		getline(insert_file, _shipDate, '|');
		getline(insert_file, _receiptDate, '|');
		getline(insert_file, _dummy, '\n');
		lineitem._UnitInsert(_orderKey, 0, 11);
		lineitem._UnitInsert(_partKey, 1, 11);
		lineitem._UnitInsert(_quantity, 2, 9);
		lineitem._UnitInsert(_discount, 3, 9);
		lineitem._UnitInsert(_shipDate, 4, 10);
		lineitem._UnitInsert(_receiptDate, 5, 10);
	}
	insert_file.close();
	
	vector<char> type_lineitem;
	type_lineitem.push_back('I');
	type_lineitem.push_back('I');
	type_lineitem.push_back('F');
	type_lineitem.push_back('F');
	type_lineitem.push_back('C');
	type_lineitem.push_back('C');

	lineitem.insert(6, type_lineitem);

	ofstream output("test.txt");

	Table orders;
	ifstream insert_file2("orders.tbl");
	string _custkey, _totalprice, _orderdate;
	orders.column_list.resize(4);

	while(!insert_file2.eof()){
		getline(insert_file2, _orderKey, '|');
		getline(insert_file2, _custkey, '|');
		getline(insert_file2, _totalprice, '|');
		getline(insert_file2, _orderdate, '|');
		getline(insert_file2, _dummy, '\n');
		orders._UnitInsert(_orderKey, 0, 11);
		orders._UnitInsert(_custkey, 1, 11);
		orders._UnitInsert(_totalprice, 2, 9);
		orders._UnitInsert(_orderdate, 3, 10);
	}
	insert_file2.close();
	vector<char> type_orders;
	type_orders.push_back('I');
	type_orders.push_back('I');
	type_orders.push_back('F');
	type_orders.push_back('C');

	orders.insert(4, type_orders);

	Table customer;
	ifstream insert_file3("customer.tbl");
	string _name, _mktsegment; // + _custkey
	customer.column_list.resize(3);

	while(!insert_file3.eof()){
		getline(insert_file3, _custkey, '|');
		getline(insert_file3, _name, '|');
		getline(insert_file3, _mktsegment, '|');
		getline(insert_file3, _dummy, '\n');
		customer._UnitInsert(_custkey, 0, 11);
		customer._UnitInsert(_name, 1, 25);
		customer._UnitInsert(_mktsegment, 2, 10);
	}
	insert_file3.close();
	vector<char> type_customer;
	type_customer.push_back('I');
	type_customer.push_back('C');
	type_customer.push_back('C');

	customer.insert(3, type_customer);

	Table* output_table = new Table;
	
	cout << "-------------------PLAN 1-----------------------" << '\n';
	cck.SetStartClock();
	plan1(&lineitem, output_table);
	cck.SetEndClock();
	cout << "ELAPSED TIME : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" <<endl;

	cout << "-------------------PLAN 2-----------------------" << '\n';
	Table* tmp1 = new Table;
	cck.SetStartClock();
	plan2(&orders, &customer, tmp1);
	cck.SetEndClock();
	cout << "ELAPSED TIME : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" <<endl;

	Table* cust_t = new Table;
	Table* joined_l_o = new Table;
	Table* joined_l_o_c = new Table;
	Table* aggregated = new Table;
	Table* final = new Table;

	cout << "-------------------PLAN 3-----------------------" << '\n';
	cck.SetStartClock();
	plan3(&lineitem, &orders, &customer, cust_t, joined_l_o, joined_l_o_c, aggregated, final);
	cck.SetEndClock();
	cout << "ELAPSED TIME : " << (double)cck.ElapsedClock()/(double)CLOCKS_PER_SEC << "sec" <<endl;
    
	return 0;
}
