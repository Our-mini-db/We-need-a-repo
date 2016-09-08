#ifndef HANDLETABLE_H
#define HANDLETABLE_H

#include "command.h"

void createTable(string tableName, vector<fieldType> field);
void dropTable(string tableName);
void addField(string tableName, fieldType newField);
void CancelField(string tableName, vector<string> allFieldName);



void insertData(string tableName, vector<pairData> _dataPair);
void deleteData(string tableName, string where_command);
void updateData(string tableName, vector<pairData> updata_data, string where_command);

void selectData(string tableName,string  where_command, string  order_command, vector<string> field_name);

#endif