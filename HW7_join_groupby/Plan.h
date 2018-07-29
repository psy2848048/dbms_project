#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Table.h"

using namespace std;

enum CmdOp { EQ, NEQ, LT, LEQ, GT, GEQ };
enum AggrOp { COUNT, MIN, MAX, AVG, SUM };

struct SelectCond {
    int idxCol;     // index of column
    CmdOp op;
    int intConst;
    string strConst;
    float floatConst;

    SelectCond(int idxCol, CmdOp op, int intConst) 
        : idxCol(idxCol), op(op), intConst(intConst) {}
    SelectCond(int idxCol, CmdOp op, string strConst) 
        : idxCol(idxCol), op(op), strConst(strConst) {}
    SelectCond(int idxCol, CmdOp op, float floatConst) 
        : idxCol(idxCol), op(op), floatConst(floatConst) {}
};

struct JoinCond {
    int lhsIdx;     // index of join column of left table
    CmdOp op;
    int rhsIdx;     // index of join column of right table

    JoinCond(int lhsIdx, CmdOp op, int rhsIdx) 
        : lhsIdx(lhsIdx), op(op), rhsIdx(rhsIdx) {}
};

struct OrderCond {
    int idxCol;     // index of column
    bool desc;      // is decreasing orders?

    OrderCond(int idxCol, bool desc) : idxCol(idxCol), desc(desc) {}
};

struct AggrCond {
    int idxCol;     // index of aggregated column
    AggrOp op;

    AggrCond(int idxCol, AggrOp op) : idxCol(idxCol), op(op) {}
};

class Operator {
public:
    static void selection(
            Table* output,
            Table* input, 
            vector<SelectCond> conds, 
            vector<int> projCols 
    );

    static void join(
            Table* output,
            Table* lhs, Table* rhs, 
            vector<JoinCond> conds, 
            vector<int> lProjsCols, vector<int> rProjCols 
    );

    static void orderBy(
            Table* output,
            Table* input, 
            vector<OrderCond> conds 
    );

    static void aggr(
            Table* output,
            Table* input, 
            vector<int> groupCols,
            vector<AggrCond> conds
    );

    static void print(
            Table* input, 
            int topN = -1
    );
};
