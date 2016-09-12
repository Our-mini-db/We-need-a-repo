#pragma warning(disable:4996)
#include "HandleDatabase.h"
bool openDataBase(string databaseName)
{
	FILE *file = fopen("Database.slist", "r");
	char temp[10000];
	bool flag = false;
	while (fscanf(file, "%s",temp) != EOF)
	{
		if (strcmp(databaseName.c_str(), temp) == 0)
		{
			flag = true;
			break;
		}
	}
	fclose(file);
	if (flag)cout << "打开数据库成功" << endl;
	else cout << "未找到该数据库" << endl;
	return flag;
}
void createDataBase(string databaseName)
{
	FILE *file = fopen("Database.slist", "a+");
	fprintf(file, "%s\n", databaseName.c_str());
	fclose(file);
	mkdir(databaseName.c_str());
	cout << "创建成功" << endl;
}
void dropDatabase(string databaseName)
{
	vector<string> allDatabaseName;
	char temp[10000];
	FILE *file = fopen("Database.slist", "r");
	while (fscanf(file, "%s", temp) != EOF)
	{
		string tempstr(temp);
		if (databaseName != tempstr)allDatabaseName.push_back(tempstr);
	}
	fclose(file);
	file = fopen("Database.slist", "w");
	for each (string var in allDatabaseName)
	{
		fprintf(file, "%s\n", var.c_str());
	}
	fclose(file);
	remove(databaseName.c_str());
}