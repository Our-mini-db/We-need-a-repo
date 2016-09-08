#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

typedef enum{
	STRING, INT, DOUBLE, DATE,
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
	int judgeBound;//约束条件
}fieldType;
typedef struct{
	string fieldName;
	string data;
}pairData;//字段与数据的一组对应
typedef struct{
	vector<fieldType> field;
	vector<rowData> data;

	string name;

}table;//表的结构



const int data_num = 4;
const int add_size = 30;
const int command_num = 8;
const int command_length = 30;

static int name_length = 20;
const int name_length_bak = 20;
const char command_content[command_num][command_length] =
{
	"CREATE", "DROP", "SELECT", "INSERT",
	"CANCEL", "DELETE", "ADD", "UPDATE",
};


//所有这些函数接受的参数都是除去了关键字命令字段(CREATE,DROP,SELECT等等)的命令  而且开头字符必然不为空格


bool deal_update_data(char command[], int & length, string & table_name, 
	vector<pairData> & updata_data, string & where_command
	);
bool deal_delete_data(char command[], int & length, string & table_name, string & where_command);

bool deal_select_data(char command[], int & length, string & table_name,
		string & where_command,string & order_command,vector<string>&field_name);

bool deal_insert_data(char command[], int & length, string & table_name, vector<pairData>& my_data);

bool deal_cancel_data(char command[], int &length, string & table_name, vector<string> & field_name);

bool deal_add_data(char command[], int &length, string &table_name, fieldType & my_field);

bool deal_drop_data(char command[], int & length,string & table_name);

//处理创建表的数据
bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType> field);


//cmd参数 吃掉回车的一条命令
void deal_with_command(char cmd[], int &length);   

int check_data_type(string name);//判断字段数据类型
int check_constraint(string name);	//判断约束条件

bool deal_where(char where_command[]);
bool deal_order(char order_command[]);

void add_char_size(char name[]);



#endif