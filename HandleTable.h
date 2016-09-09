#ifndef HANDLETABLE_H
#define HANDLETABLE_H
#include "main.h"

void createTable(string tableName, vector<fieldType> field);
void dropTable(string tableName);
void addField(string tableName, fieldType newField);
void CancelField(string tableName, vector<string> allFieldName);
#endif