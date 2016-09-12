#ifndef SELECTDATA_H
#define SELECTDATA_H
#include"main.h"
void selectData(string databaseName, string tableName, string where_command, string order_command, vector<string>field_name);
table orderBy(table &Thetable, vector<int>  selectNumber, string orderby_command, int &top);
Priority getPriority(table &theTable, string order[]);
int dealWith_priority(table &theTable, vector<Priority> &priority, string orderby_command);
#endif