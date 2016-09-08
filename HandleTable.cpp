#include "HandleTable.h"

void createTable(string tableName, vector<fieldType> field)
{
	printf("Create table %s\n", tableName.c_str());
}
void dropTable(string tableName)
{
	printf("DROP table %s\n", tableName.c_str());
}
void addField(string tableName, fieldType newField)
{
	printf("ADD %s \n", tableName.c_str());
}

void CancelField(string tableName, vector<string> allFieldName)
{
	printf("CANCEL %s \n", tableName.c_str());
}





void insertData(string tableName, vector<pairData> _dataPair)
{

}


void deleteData(string tableName, string where_command)
{

}
void updateData(string tableName, vector<pairData> updata_data, string where_command)
{

}


void selectData(string tableNmae,string & where_command, string & order_command, vector<string>&field_name)
{

}
