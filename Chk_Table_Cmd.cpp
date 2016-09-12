#include"Chk_Table_Cmd.h"
#include "Command.h"
bool deal_add_data(char command[], int &length, string &table_name, fieldType & myfield)
{
	int counter = 0;
	int temp = 0;	//录脟脗录name碌脛脧脗卤锚
	bool error = false;
	bool check = false;	//麓娄脌铆露脿赂枚驴脮赂帽
	char * name = new char[name_length];	//脭脻麓忙脣霉脫脨碌脛脢盲脠毛露脦 name 脰禄脨猫脪陋脪禄赂枚录麓驴脡

	myfield.fieldNum = 0;
	for (int i = 0; i <= length; ++i)
	{
		if (command[i] != ' '&&command[i] != '\0') //路脟驴脮赂帽碌脛禄掳露脕脠毛	
		{
			check = true;
			if (temp == name_length - 2)
			{
				name = add_char_size(name);
			}
			name[temp++] = command[i];
			name[temp] = '\0';
		}
		else
		{
			if (counter == 0)
			{
				table_name = name;
			}
			else if (counter == 1)
			{
				myfield.fieldName = name;
				myfield.fieldNum++;
			}
			else if (counter == 2)
			{
				for (int i = 0; name[i] != '\0'; ++i)
				{
					if (name[i] >= 'a'&&name[i] <= 'z')//陆芦脨隆脨麓脳陋禄禄脦陋麓贸脨麓
						name[i] = name[i] - 32;
				}
				int field_type = check_data_type(name);
				switch (field_type)
				{
				case 0:
					myfield.theType = STRING;
					break;
				case 1:
					myfield.theType = INT;
					break;
				case 2:
					myfield.theType = DOUBLE;
					break;
				case 3:
					myfield.theType = DATE;
					break;
				case -1:
					error = true;
					printf("We don't have the data type %s\n", name);
					break;
				}
				if (!error)
					myfield.fieldNum++;

			}
			else if (counter == 3)
			{
				if (temp > 3)
					printf("Error! Constriant bits should equal to 2");
				int judge_type = check_constraint(name);
				switch (judge_type)
				{
				case 10:	// 10
					error = true;
					printf("The PK field can't be null");
					break;
				case 0:		// 00
					myfield.limitation = 0;
					break;
				case 11:	// 11
					myfield.limitation = 11;
					break;
				case 1:		// 01
					myfield.limitation = 1;
					break;
				case -1:
					error = true;
					printf("We don't have %s constriant type\n", name);
					break;
				}
				if (!error)
					myfield.fieldNum++;

			}
			counter++;
			temp = 0;
			if (error)
			{
				return false;
			}
			delete name;
			name_length = name_length_bak;
			name = new char[name_length + 1];
		}
	}
	delete name;

	if (myfield.fieldNum != 3)
	{
		return false;
	}
	myfield.fieldNum = 0;
	return true;
}

bool deal_cancel_data(char command[], int &length, string & table_name, vector<string> &field_name)
{
	char * name = new char[name_length];
	bool flag = false;
	int counter = 0;
	int temp = 0;	//name 碌脛脧脗卤锚
	for (int i = 0; i <= length; ++i)
	{
		if (command[i] != ' '&&command[i] != '\0')
		{
			flag = true;
			if (temp == name_length - 2)
			{
				name = add_char_size(name);
			}
			name[temp++] = command[i];
			name[temp] = '\0';
		}
		else
		{
			if (counter == 0)
			{
				table_name = name;
				counter = 1;
			}
			else
			{
				counter++;
				field_name.push_back(name);
			}
			temp = 0;
		}
	}
	delete name;

	if (counter <= 1)
		flag = false;
	return flag;
}


bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType>& field, int & flag)//麓娄脌铆麓麓陆篓卤铆碌脛脢媒戮脻
{
	bool check = false;//脠莽鹿没潞卢脫脨露脿赂枚驴脮赂帽
	bool error = false;//脜脨露脧脢盲脠毛脢脟路帽脫脨麓铆

	int count = -2;	//脫脙脌麓脟酶路脰脳脰露脦碌脛脢么脨脭
	int temp = 0;	//录脟脗录name碌脛脧脗卤锚

	char * name = new char[name_length + 1];	//脭脻麓忙脣霉脫脨碌脛脢盲脠毛露脦name 脰禄脨猫脪陋脪禄赂枚录麓驴脡

	fieldType  myfield;
	for (int i = 0; i <= length; ++i)
	{
		//脜脨露脧脢脟路帽脦陋驴脮赂帽
		if (command[i] != ' '&&command[i] != '\0') //路脟驴脮赂帽碌脛禄掳露脕脠毛	
		{
			check = true;
			if (temp == name_length - 2)
			{
				name = add_char_size(name);
			}

			name[temp++] = command[i];
			name[temp] = '\0';

		}
		else if (command[i] == ' ' || command[i] == '\0')//脢脟驴脮赂帽碌脛禄掳陆酶脨脨麓娄脌铆
		{
			if (check == false)continue;
			count++;
			check = false;

			if (count == -1)	//琛ㄥ悕
			{
				table_name = name;
				if (flag == 2)
				{
					bool legal = is_legal(name);
					if (legal == false)
					{
						printf("sorry , you have input a name is the same as key string.\n");
						return false;
					}
				}
				if (_stricmp(name, "database") == 0)
				{
					flag = 2;
					count--;
				}
				else
				{
					if (flag == 0)
					{
						printf("Please open or create a database!\n");
						return false;
					}
				}
				temp = 0;
			}
			else
			{
				if (flag == 2)
					return false;
				name[temp] = '\0';
				if (count % 3 == 0)	//脳脰露脦脙没
				{
					myfield.fieldName = name;
				}
				else if (count % 3 == 1)//脳脰露脦脌脿脨脥
				{
					for (int i = 0; name[i] != '\0'; ++i)
					{
						if (name[i] >= 'a'&&name[i] <= 'z')//陆芦脨隆脨麓脳陋禄禄脦陋麓贸脨麓
							name[i] = name[i] - 32;
					}
					int field_type = check_data_type(name);
					switch (field_type)
					{
					case 0:
						myfield.theType = STRING;
						break;
					case 1:
						myfield.theType = INT;
						break;
					case 2:
						myfield.theType = DOUBLE;
						break;
					case 3:
						myfield.theType = DATE;
						break;
					case -1:
						return false;
					}

				}
				else if (count % 3 == 2)//脳脰露脦脭录脢酶脤玫录镁
				{
					if (temp > 3)
						return false;
					int judge_type = check_constraint(name);
					switch (judge_type)
					{
					case 10:	// 10
						return false;
					case 0:		// 00
						myfield.limitation = 0;
						break;
					case 11:	// 11
						myfield.limitation = 11;
						break;
					case 1:		// 01
						myfield.limitation = 1;
						break;
					case -1:
						return false;
					}
					if (!error)
					{
						field.push_back(myfield);	//录脫脠毛脪禄赂枚脳脰露脦
					}
				}
				temp = 0;	//脰禄脪陋脢脟露脕碌陆驴脮赂帽脰庐潞贸戮脥脪陋陆芦name脧脗卤锚脰脙脦陋0
			}
			if (error) break;
			delete name;
			name_length = name_length_bak;
			name = new char[name_length + 1];
		}
	}

	if (count == -2 || ((count + 3) % 3 != 2))return false;
	delete name;

	return true;
}

bool deal_open_data(char command[], int & length, string & database)
{
	int len = strlen(command);
	int now = 0;
	database.clear();
	for (; now < len&&command[now] != ' '; now++)
		database += command[now];
	while (now < len&&command[now] == ' ')
		now++;
	length = database.length();
	if (now != len)
		return false;
	return true;
}