#ifndef HANDLETABLE_H
#define HANDLETABLE_H
#include "main.h"

void createTable(string databaseName,string tableName, vector<fieldType> field);
void dropTable(string databaseName,string tableName);
void addField(string databaseName, string tableName, fieldType newField);
void CancelField(string databaseName, string tableName, vector<string> allFieldName);
#endif