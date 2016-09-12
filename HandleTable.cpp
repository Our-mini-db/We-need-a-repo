#include "HandleTable.h"
void createTable(string databaseName, string tableName, vector<fieldType> field)
{
	table TheTable;
	TheTable.name = tableName;
	for each (fieldType var in field)
	{
		TheTable.field.push_back(var);
	}
	saveTable(databaseName,TheTable);
	cout << "创建表成功" << endl;
}
void dropTable(string databaseName, string tableName)
{
	openTable(databaseName,tableName);
}
void addField(string databaseName, string tableName, fieldType newField)
{
	table tempTable = openTable(databaseName,tableName);
	tempTable.field.push_back(newField);
	saveTable(databaseName,tempTable);
}
void CancelField(string databaseName, string tableName, vector<string> allFieldName)
{

}