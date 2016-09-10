#ifndef HANDLEDATA_H
#define HANDLEDATA_H
#include "main.h"
void insertData(string tableName, vector<pairData> _dataPair);
void addField(string tableName, fieldType newField);
void updateData(string tableName, vector<pairData> updata_data, string where_command);
void deleteData(string tableName, string where_command);
#endif