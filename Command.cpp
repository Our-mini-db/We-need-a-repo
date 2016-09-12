#define _CRT_SERURE_NO_WARNINGS
#include "Command.h"

bool is_legal(char *name)
{
	for (int i = 0; i < key_num; ++i)
	{
		if (_stricmp(name, key_string[i]) == 0)
			return false;
	}
	return true;
}

char* add_char_size(char name[])
{
	char *temp = new char[name_length + 1];
	for (int i = 0; i < name_length + 1; i++)
	{
		temp[i] = name[i];
		if (name[i] == '\0')break;

	}
	//strcpy(temp, name);
	delete name;
	name = new char[name_length + add_size];
	name_length = name_length + add_size;
	for (int i = 0; i < name_length + 1; i++)
	{
		name[i] = temp[i];
		if (temp[i] == '\0')break;
	}
	//strcpy(name, temp);
	delete temp;
	return name;
}

bool deal_order(char order_command[])
{
	return true;
}

int deal_with_command(char cmd[], int & length, int & flag, string & database)
{
	char * command = new char[length + 1];
	bool check = false;  //脠莽鹿没脙眉脕卯驴陋脢录脢卤戮脥脢脟驴脮赂帽脭玫脙麓 掳矛 录脫脪禄赂枚卤锚录脟卤盲脕驴
	int temp = 0;

	int k = 0;	//录脟脗录碌脷录赂赂枚脦陋路脟脙眉脕卯脳脰露脦
	for (int i = 0; i < length; ++i)	//露脕脠毛脙驴脤玫脙眉脕卯碌脛碌脷脪禄赂枚脳脰露脦
	{
		if (temp > 6)break;
		if (cmd[i] != ' ')
		{
			command[temp++] = cmd[i];
			check = true;
		}
		else
		{
			if (check == true)
			{
				k = i;
				command[temp] = '\0';
				break;
			}
		}
	}
	if (temp > 6)
	{
		printf("Command Error!");
		command[6] = '\0';
		return 0;
	}
	for (int i = 0; command[i] != '\0'; ++i)	//陆芦脨隆脨麓脳脰脛赂脳陋禄炉脦陋麓贸脨麓脳脰脛赂
	{
		if (command[i] <= 'z'&&command[i] >= 'a')
			command[i] = command[i] - 32;
	}
	int command_kind = -1;
	for (int i = 0; i < command_num; ++i)	//脜脨露脧脰赂脕卯脢脟路帽脭脷脰赂脕卯录炉脰脨脪脩卤禄露篓脪氓
	{
		if (strcmp(command_content[i], command) == 0)
		{
			command_kind = i;
			break;
		}
	}
	if (command_kind == -1)	//脠莽鹿没脦陋脦麓露篓脪氓碌脛脰赂脕卯脳脰露脦拢卢陆谩脢酶碌卤脟掳脰赂脕卯碌脛麓娄脌铆
	{
		printf("We don't have %s command\n", command);
		return 0;
	}
	//cout << command << endl;
	//陆芦脢拢脧脗碌脛脙眉脕卯脳脰露脦脧貌脟掳脜虏碌陆脳脰路没麓庐脢脳拢卢脪虏录麓脧脰脭脷碌脛command脳脰路没麓庐麓忙碌脛脙眉脕卯虏禄掳眉潞卢CREATE拢卢UPDATE碌脠脳脰露脦拢禄
	//虏垄脟脪脙眉脕卯驴陋脥路虏禄潞卢驴脮赂帽 
	check = false;
	temp = 0;

	for (int i = k; i < length; ++i)
	{
		if (cmd[i] != ' ')
		{
			command[temp++] = cmd[i];
			check = true;
		}
		else
		{
			if (check == true)
			{
				command[temp++] = cmd[i];
			}
		}
	}
	command[temp] = '\0';
	//cout << command << endl;

	length = temp;

	//澶囦唤database浠ュ強flag
	int temp_flag = flag;
	string temp_database(database);

	switch (command_kind)	//掳脣脤玫脙眉脕卯脪脭录掳麓铆脦贸麓娄脌铆
	{
	case 0:	//麓麓陆篓卤铆碌脛脙眉脕卯脢媒戮脻麓娄脌铆
	{
		string table_name;
		vector<fieldType> my_field;

		bool check = deal_create_data(command, length, table_name, my_field, flag);

		if (check == true)
		{
			if (flag == 1)	//flag=1浠ｈ〃宸茬粡open涓€涓暟鎹簱  鍒涘缓涓€涓〃   
			{
				createTable(database,table_name, my_field);
			}
			else if (flag == 2)	//flag=2浠ｈ〃鍒涘缓涓€涓暟鎹簱
			{
				database = table_name;
				createDataBase(database);
				database = temp_database;
				flag = temp_flag;
			}
			else
				return -1;
		}
		else
		{
			printf("create failed!\n");

		}
		break;
	}
	case 1:	//drop
	{
		string table_name;

		bool check = deal_drop_data(command, length, table_name, flag);

		if (check == true)
		{
			if (flag == 3)	//鎵惧埌浜嗘暟鎹簱鍚嶅瓧
			{
				database = table_name;
				dropDatabase(database);
				database = temp_database;
				flag = temp_flag;
			}
			else if (flag == 1)
			{
				dropTable(database,table_name);
			}
		}
		else
		{
			printf("DROP failed;\n");
		}
		break;
	}
	case 2:
	{
		if (flag == 0)return -1;
		string table_name;
		string where_command;
		vector<string> field_name;
		string order_command;
		bool check = deal_select_data(command, length, table_name, where_command, order_command, field_name);
		//check = true;
		if (check == true)
		{
			selectData(database,table_name, where_command, order_command, field_name);
		}
		else
		{
			printf("select error!\n");
		}
		break;
	}
	case 3:
	{
		if (flag == 0)return -1;
		string table_name;
		vector<pairData> my_data;
		bool check = false;
		check = deal_insert_data(command, length, table_name, my_data);
		if (check == true)
		{
			insertData(database,table_name, my_data);
		}
		else
		{
			printf("insert!\n");
		}
		break;
	}
	case 4:
	{
		if (flag == 0)return -1;
		string table_name;
		vector<string> field_name;
		bool check = false;
		check = deal_cancel_data(command, length, table_name, field_name);
		if (check == true)
			CancelField(database,table_name, field_name);
		else
		{
			printf("cancel failed!\n");
		}
		break;
	}
	case 5:
	{
		if (flag == 0)return -1;
		string table_name;
		string where_command;
		bool check = deal_delete_data(command, length, table_name, where_command);
		if (check == true)
		{
			deleteData(database,table_name, where_command);
		}
		else
		{
			printf("delete failed!\n");
		}
		break;
	}
	case 6:
	{
		if (flag == 0)return -1;
		string table_name;
		fieldType my_field;
		bool check = deal_add_data(command, length, table_name, my_field);
		if (check == true)
		{
			addField(database,table_name, my_field);
		}
		else
		{
			printf("add failed!\n");
		}
		break;
	}
	case 7:
	{
		if (flag == 0)return -1;
		string table_name;
		string where_command;
		vector<pairData> new_update_data;
		bool check = false;

		check = deal_update_data(command, length, table_name, new_update_data, where_command);
		if (check == true)
		{
			updateData(database,table_name, new_update_data, where_command);
		}
		else
		{
			printf("update failed!\n");
		}
		break;
	}
	case 8:
	{
		bool check = false;
		check = deal_open_data(command, length, database);
		if (check == true)
		{
			openDataBase(database);
			flag = 1;
		}
		else
		{
			printf("open error\n");
		}
		break;
	}

	default:
	{
		printf("Please input command correctly!\n");
		break;
	}
	}
	delete command;
	return true;
}


int check_data_type(string name)//脜脨露脧脳脰露脦脢媒戮脻脌脿脨脥
{
	if (strcmp(name.c_str(), "STRING") == 0)
		return 0;
	else if (strcmp(name.c_str(), "INT") == 0)
		return 1;
	else if (strcmp(name.c_str(), "DOUBLE") == 0)
		return 2;
	else if (strcmp(name.c_str(), "DATE") == 0)
		return 3;
	return -1;
}

int check_constraint(string name)	//脜脨露脧脭录脢酶脤玫录镁
{
	if (name[0] == '1' && name[0] == '0')
		return 10;
	else if (name[0] == '0' && name[1] == '0')
		return 0;
	else if (name[0] == '1' && name[1] == '1')
		return 11;
	else if (name[0] == '0' && name[1] == '1')
		return 1;
	else return -1;
}

bool judgeJudge(string judge) {
	if (judge == "=" || judge == ">" || judge == "<" || judge == "!=" || judge == ">=" || judge == "<=")
		return true;
	return false;
}
bool judgeMark(string mark)
{
	if (mark == "AND" || mark == "OR")
		return true;
	else
		return false;
}
bool deal_where(const char command[])//处理where语句不符合格式 
{
	int commandLen = strlen(command);
	int first, last, commandNum;
	part content;
	//	memset(&content, 0, sizeof(content));
	//bool withMarks=false;//双引号的标识符
	first = last = commandNum = 0;
	for (; last<commandLen; last++) {
		if (commandNum == 0 && command[last] != ' '&&command[last] != '!'&&command[last] != '>'&&command[last] != '<'&&command[last] != '=')//get the name
			content.listName += command[last];
		else if (commandNum == 0)
		{
			while (command[last] == ' '&&last<commandLen)
				last++;
			if (last >= commandLen)
				return false;
			if (command[last] != ' ') //consider the string judge
				commandNum = 1;
		}
		if (commandNum == 1 && command[last] != ' '&&command[last] != '"')//consider judge
			content.judge += command[last];
		else if (commandNum == 1) {
			if (command[last] != ' '&&command[last] != '"')//not space or double marks
				return false;
			else if (command[last] == ' ')//deal with space
			{
				while (last < commandLen&&command[last] == ' ')
					last++;
				if (command[last] != '"' || last >= commandLen)
					return false;
			}
			if (commandNum == 1 && command[last] == '"')//deal with the first "
			{
				commandNum = 2;
				last++;
				if (last >= commandLen)
					return false;
			}
		}
		if (commandNum == 2 && command[last] != '"'&&command[last] != '\\')//已经处理完第一个双引号
			content.constant += command[last];
		else if (command[last] == '\\')//对于转义字符进行处理
		{
			last++;
			if (last >= commandLen)
				return false;
			content.constant += command[last];
		}
		else if (command[last] == '"')
		{
			commandNum = 3;
			last++;
		}
		if (commandNum == 3 && last<commandLen){
			while ((command[last] == ' ' || command[last] == ')') && last<commandLen)
				last++;
			if (last >= commandLen)
				return true;
			while (last < commandLen&&command[last] != ' ')
				content.mark += command[last++];
			if (last >= commandLen)
				return false;
			if (judgeJudge(content.judge) && judgeMark(content.mark))
			{
				content.listName.clear();
				content.judge.clear();
				content.constant.clear();
				content.mark.clear();
				commandNum = 0;
				while ((command[last] == ' ' || command[last] == '(') && last < commandLen)
					last++;
				last--;
			}
			else
				return false;
		}
	}
	return judgeJudge(content.judge) && !content.mark.length();
}


