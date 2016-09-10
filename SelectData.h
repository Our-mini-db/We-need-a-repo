#ifndef SELECTDATA_H
#define SELECTDATA_H
#include"main.h"
void selectData(const string tableName, const string where_command, const string order_command, const vector<string>field_name);
table orderBy(table &Thetable, vector<int>  selectNumber, string orderby_command);
Priority getPriority(table &theTable, string order[]);
void dealWith_priority(table &theTable, vector<Priority> &priority, string orderby_command);
#endif