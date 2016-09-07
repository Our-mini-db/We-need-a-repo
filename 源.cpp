#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "command.h"
#include "HandleTable.h"
using namespace std;

static int input_command_length = 50;
const int input_command_length_bak = 20;
//const int add_size = 10;

int main()
{
	char ch = 0;
	char* command = new char[input_command_length];

	static int bitnum = 0;
	while ((ch = getchar()) != EOF)//挨个字符进行处理
	{
		if (ch == ';')//如果读到 ; 表示输入一条命令   支不支持 分号的输入
		{
			int cmd = -1;
			command[bitnum] = '\0';	//刚才输入的指令(仅将回车吃掉)
			cout << command << endl;

			deal_with_command(command,bitnum);	//处理这条命令
			bitnum = 0;

			//重新分配command的内存大小
			input_command_length = input_command_length_bak;
			delete command;
			command = new char[input_command_length];
		}
		else
		{
			if (bitnum == input_command_length - 2)//当字符串长度不够时重新分配
			{
				char *temp = new char[input_command_length];
				strcpy(temp, command);
				command = new char[input_command_length + add_size];
				input_command_length += add_size;
				strcpy(command, temp);
				delete temp;
			}
			if (ch == '\n')	ch = ' ';
			command[bitnum++] = ch;
			command[bitnum] = '\0';
		}
	}
	delete command;
	return 0;
}
