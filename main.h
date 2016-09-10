//#define _CRT_SERURE_NO_WARNINGS
#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;
typedef enum{
	NONE, STRING, INT, DOUBLE, DATE
}dataType;
typedef struct {
	int year;
	int month;
	int day;
}date;
typedef struct{
	int rowNum;//行号
	string Data[10];
}rowData;
typedef struct{
	int fieldNum;//字段序号
	string fieldName;//字段名称
	dataType theType;//数据类型
	int limitation;//约束条件
}fieldType;
typedef struct{
	string fieldName;
	string data;
}pairData;//字段与数据的一组对应
typedef struct{
	string name;
	vector<fieldType> field;
	vector<rowData> data;
	map<string, int> fieldmap;
}table;//表的结构

typedef struct{
	int columnnum;
	dataType theDataType;
	bool judgeUpOrDown;// true表示升序 false表示降序
}Priority;
typedef struct
{
	string fieldName;
	string compareMark;
	string value;
	string rel;
	string fieldType;
}shortString;//whereè¯­å¥å¤„ç†
typedef   struct
{
	vector<shortString> shortStrings;
	bool flag;
}djString;

extern int name_length;
const int name_length_bak = 20;

typedef map<string, int>findFieldnum;
void input_Command();//输入命令
//void dealWith_Command(string command);//处理命令 提取command的信息
//vector<int> dealWith_Where(table theTable, string where_command);//处理where语句
table openTable(string tableName);//打开磁盘中的表
void saveTable(table _theSavingTable);//保存磁盘中的表
#endif