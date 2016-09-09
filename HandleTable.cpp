#include "HandleTable.h"
void createTable(string tableName, vector<fieldType> field)
{
	table TheTable;
	TheTable.name = tableName;
	for each (fieldType var in field)
	{
		TheTable.field.push_back(var);
	}
	saveTable(TheTable);
}
void dropTable(string tableName)
{
	openTable(tableName);
}
void addField(string tableName, fieldType newField)
{
	table tempTable = openTable(tableName);
	tempTable.field.push_back(newField);
	saveTable(tempTable);
}
void CancelField(string tableName, vector<string> allFieldName)
{

}