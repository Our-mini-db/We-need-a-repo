#ifndef COMMAND_H
#define COMMAND_H
#include "main.h"
#include "Chk_Dat_Cmd.h"
#include "Chk_SD_Cmd.h"
#include "Chk_Table_Cmd.h"
#include "HandleData.h"
#include "HandleTable.h"
#include "SelectData.h"

struct part
{
	string listName;//×Ö¶ÎÃû³Æ
	string mark;//and or
	string constant;//³£Á¿ ×Ö¶ÎÖµ
	string judge;//¸÷ÖÖ·ûºÅ
};

const int data_num = 4;
const int add_size = 30;
const int command_num = 8;
const int command_length = 30;


const char command_content[command_num][command_length] =
{
	"CREATE", "DROP", "SELECT", "INSERT",
	"CANCEL", "DELETE", "ADD", "UPDATE",
};


//cmd²ÎÊý ³Ôµô»Ø³µµÄÒ»ÌõÃüÁî
void deal_with_command(char cmd[], int &length);

int check_data_type(string name);//ÅÐ¶Ï×Ö¶ÎÊý¾ÝÀàÐÍ
int check_constraint(string name);	//ÅÐ¶ÏÔ¼ÊøÌõ¼þ

bool deal_where(char where_command[]);
bool deal_order(char order_command[]);

char* add_char_size(char name[]);

bool judgeJudge(string judge);
bool judgeMark(string mark);
bool deal_where(char command[]);

#endif
