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
	while ((ch = getchar()) != EOF)//�����ַ����д���
	{
		if (ch == ';')//������� ; ��ʾ����һ������   ֧��֧�� �ֺŵ�����
		{
			int cmd = -1;
			command[bitnum] = '\0';	//�ղ������ָ��(�����س��Ե�)
			cout << command << endl;

			deal_with_command(command,bitnum);	//������������
			bitnum = 0;

			//���·���command���ڴ��С
			input_command_length = input_command_length_bak;
			delete command;
			command = new char[input_command_length];
		}
		else
		{
			if (bitnum == input_command_length - 2)//���ַ������Ȳ���ʱ���·���
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
