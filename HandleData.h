#ifndef HANDLEDATA_H
#define HANDLEDATA_H
#include "main.h"
void insertData(string databaseName,string tableName, vector<pairData> _dataPair);
void updateData(string databaseName, string tableName, vector<pairData> updata_data, string where_command);
void deleteData(string databaseName, string tableName, string where_command);
#endif