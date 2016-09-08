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
	int rowNum;//�к�
	string Data[10];
}rowData;
typedef struct{
	int fieldNum;//�ֶ����
	string fieldName;//�ֶ�����
	dataType theType;//��������
	int judgeBound;//Լ������
}fieldType;
typedef struct{
	string fieldName;
	string data;
}pairData;//�ֶ������ݵ�һ���Ӧ
typedef struct{
	vector<fieldType> field;
	vector<rowData> data;

	string name;

}table;//��Ľṹ



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


//������Щ�������ܵĲ������ǳ�ȥ�˹ؼ��������ֶ�(CREATE,DROP,SELECT�ȵ�)������  ���ҿ�ͷ�ַ���Ȼ��Ϊ�ո�


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

//�������������
bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType> field);


//cmd���� �Ե��س���һ������
void deal_with_command(char cmd[], int &length);   

int check_data_type(string name);//�ж��ֶ���������
int check_constraint(string name);	//�ж�Լ������

bool deal_where(char where_command[]);
bool deal_order(char order_command[]);

void add_char_size(char name[]);



#endif