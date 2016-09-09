
#define _CRT_SERURE_NO_WARNINGS
#include "Command.h"

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

void deal_with_command(char cmd[], int & length)
{
	char * command = new char[length + 1];
	bool check = false;  //Èç¹ûÃüÁî¿ªÊ¼Ê±¾ÍÊÇ¿Õ¸ñÔõÃ´ °ì ¼ÓÒ»¸ö±ê¼Ç±äÁ¿
	int temp = 0;

	int k = 0;	//¼ÇÂ¼µÚ¼¸¸öÎª·ÇÃüÁî×Ö¶Î
	for (int i = 0; i < length; ++i)	//¶ÁÈëÃ¿ÌõÃüÁîµÄµÚÒ»¸ö×Ö¶Î
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
		return;
	}
	for (int i = 0; command[i] != '\0'; ++i)	//½«Ð¡Ð´×ÖÄ¸×ª»¯Îª´óÐ´×ÖÄ¸
	{
		if (command[i] <= 'z'&&command[i] >= 'a')
			command[i] = command[i] - 32;
	}
	int command_kind = -1;
	for (int i = 0; i < command_num; ++i)	//ÅÐ¶ÏÖ¸ÁîÊÇ·ñÔÚÖ¸Áî¼¯ÖÐÒÑ±»¶¨Òå
	{
		if (strcmp(command_content[i], command) == 0)
		{
			command_kind = i;
			break;
		}
	}
	if (command_kind == -1)	//Èç¹ûÎªÎ´¶¨ÒåµÄÖ¸Áî×Ö¶Î£¬½áÊøµ±Ç°Ö¸ÁîµÄ´¦Àí
	{
		printf("We don't have %s command\n", command);
		return;
	}
	//cout << command << endl;
	//½«Ê£ÏÂµÄÃüÁî×Ö¶ÎÏòÇ°Å²µ½×Ö·û´®Ê×£¬Ò²¼´ÏÖÔÚµÄcommand×Ö·û´®´æµÄÃüÁî²»°üº¬CREATE£¬UPDATEµÈ×Ö¶Î£»
	//²¢ÇÒÃüÁî¿ªÍ·²»º¬¿Õ¸ñ 
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

	switch (command_kind)	//°ËÌõÃüÁîÒÔ¼°´íÎó´¦Àí
	{
	case 0:	//´´½¨±íµÄÃüÁîÊý¾Ý´¦Àí
	{
		string table_name;
		vector<fieldType> my_field;
		bool check = deal_create_data(command, length, table_name, my_field);
		if (check == true)
		{
			createTable(table_name, my_field);
			cout << "创建成功" << endl;
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÏÂÁÐ¸ñÊ½ÊäÈë²åÈë½¨±íÃüÁî\n");
			printf("CREATE table;\n×Ö¶Î1 Êý¾ÝÀàÐÍ Ô¼ÊøÌõ¼þ\n×Ö¶Î2 Êý¾ÝÀàÐÍ Ô¼ÊøÌõ¼þ\n");
			printf("eg:CREATE ³É¼¨ ÊýÑ§ int 10 Ó¢Óï int 00;\n");
			printf("============================\n");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 1:	//drop
	{
		string table_name;
		bool check = deal_drop_data(command, length, table_name);
		if (check == true)
		{
			dropTable(table_name);
			cout << "删表成功" << endl;
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÏÂÁÐ¸ñÊ½ÊäÈë²åÈëÉ¾³ýÃüÁî\n");
			printf("DROP table;\n");
			printf("eg:DROP ³É¼¨;\n");
			printf("============================\n");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 2:
	{
		string table_name;
		string where_command;
		vector<string> field_name;
		string order_command;
		bool check = deal_select_data(command, length, table_name, where_command, order_command, field_name);
		if (check == true)
		{
			selectData(table_name, where_command, order_command, field_name);
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÏÂÁÐ¸ñÊ½ÊäÈë²åÈë¼ÇÂ¼ÃüÁî\n");
			printf("SELECT 	table ×Ö¶Î1 ×Ö¶Î2 ×Ö¶Î3\
				   				   nwhere Ìõ¼þ\nORDER  by ×Ö¶Î ASC(DESC)\n[ALL, TOP N, *]\n");
			printf("eg:SELECT Ñ§Éú ÄêÁä ÐÔ±ð\nwhere ³É¼¨>¡°90¡±  top 5\nORDER BY ³É¼¨ ASC; \n");
			printf("============================\n");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 3:
	{
		string table_name;
		vector<pairData> my_data;
		bool check = false;
		check = deal_insert_data(command, length, table_name, my_data);
		if (check == true)
		{
			insertData(table_name, my_data);
			cout << "插入成功" << endl;
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÏÂÁÐ¸ñÊ½ÊäÈë²åÈë¼ÇÂ¼ÃüÁî\n");
			printf("Cancel table ×Ö¶ÎÃû³Æ1 ×Ö¶ÎÃû³Æ2 ... ×Ö¶ÎÃû³Æn,;\n");
			printf("eg:Cancel ³É¼¨ °à¼¶ ÐÔ±ð;\n");
			printf("============================\n");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 4:
	{
		string table_name;
		vector<string> field_name;
		bool check = false;
		check = deal_cancel_data(command, length, table_name, field_name);
		if (check == true)
			CancelField(table_name, field_name);
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÏÂÁÐ¸ñÊ½ÊäÈëÉ¾³ý×Ö¶ÎÃüÁî\n");
			printf("Cancel table ×Ö¶ÎÃû³Æ1 ×Ö¶ÎÃû³Æ2 ... ×Ö¶ÎÃû³Æn,;\n");
			printf("eg:Cancel ³É¼¨ °à¼¶ ÐÔ±ð;\n");
			printf("============================\n");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 5:
	{
		string table_name;
		string where_command;
		bool check = deal_delete_data(command, length, table_name, where_command);
		if (check == true)
		{
			deleteData(table_name, where_command);
			cout << "删除成功" << endl;
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÏÂÁÐ¸ñÊ½ÊäÈëdelete×Ö¶ÎÃüÁî\n");
			printf(";\n");
			printf("eg:;\n");
			printf("============================\n");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 6:
	{
		string table_name;
		fieldType my_field;
		bool check = deal_add_data(command, length, table_name, my_field);
		if (check == true)
		{
			addField(table_name, my_field);
			cout << "添加成功" << endl;
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÒÔÏÂ¸ñÊ½ÊäÈëÃüÁî:\n");
			printf("ADD table ×Ö¶Î Êý¾ÝÀàÐÍ Ô¼ÊøÌõ¼þ\n");
			printf("eg:ADD ³É¼¨ °à¼¶ String 00;");
			printf("PAY ATTENTION : You can only add one field\n");
			printf("=============================================");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
		}
		break;
	}
	case 7:
	{
		string table_name;
		string where_command;
		vector<pairData> new_update_data;
		bool check = false;

		check = deal_update_data(command, length, table_name, new_update_data, where_command);
		if (check == true)
		{
			updateData(table_name, new_update_data, where_command);
		}
		else
		{
			printf("Äú¸Õ²ÅÊäÈëµÄÃüÁîÓÐ´íÎó!\n");
			printf("Çë°´ÕÕÒÔÏÂ¸ñÊ½ÊäÈëÃüÁî:\n");
			printf("ADD table ×Ö¶Î Êý¾ÝÀàÐÍ Ô¼ÊøÌõ¼þ\n");
			printf("eg:ADD ³É¼¨ °à¼¶ String 00;");
			printf("=============================================");
			printf("¸Õ²ÅµÄÃüÁî½«»áÊÇÎÞÐ§ÃüÁî£¬Èç¹ûÄúÏëÖØÐÂÖ´ÐÐ¸Õ²ÅµÄ²Ù×÷ÇëÖØÐÂÊäÈëÕýÈ·µÄÃüÁî:\n");
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

}


int check_data_type(string name)//ÅÐ¶Ï×Ö¶ÎÊý¾ÝÀàÐÍ
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

int check_constraint(string name)	//ÅÐ¶ÏÔ¼ÊøÌõ¼þ
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
bool deal_where(char command[])//´¦ÀíwhereÓï¾ä²»·ûºÏ¸ñÊ½ 
{
	int commandLen = strlen(command);
	int first, last, commandNum;
	part content;
	//	memset(&content, 0, sizeof(content));
	//bool withMarks=false;//Ë«ÒýºÅµÄ±êÊ¶·û
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
		if (commandNum == 2 && command[last] != '"'&&command[last] != '\\')//ÒÑ¾­´¦ÀíÍêµÚÒ»¸öË«ÒýºÅ
			content.constant += command[last];
		else if (command[last] == '\\')//¶ÔÓÚ×ªÒå×Ö·û½øÐÐ´¦Àí
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
			while (command[last] == ' '&&last<commandLen)
				last++;
			if (last >= commandLen)
				return false;
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
				while (command[last] == ' '&&last < commandLen)
					last++;
				last--;
			}
			else
				return false;
		}
	}
	return judgeJudge(content.judge) && !content.mark.length();
}




