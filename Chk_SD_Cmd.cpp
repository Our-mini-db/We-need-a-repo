#include "Chk_SD_Cmd.h"
#include "Command.h"

void copy(char * str1, string & str2)
{
	int length = str2.size();
	for (int i = 0; i < length; ++i)
	{
		str1[i] = str2[i];
	}

	str1[length] = '\0';
}
bool deal_select_data(char command[], int & length, string & table_name, string & where_command, string & order_command, vector<string>&field_name)
{
	char *name = new char[name_length];
	int temp = 0;

	int counter = 0;
	int flag = 0;
	int temp1 = 0;	//录脟脗录where脫茂戮盲
	int temp2 = 0;	//录脟脗录order 脫茂戮盲

	bool space = false;

	for (int i = 0; i <= length; ++i)
	{
		if (name_length - 2 == temp)
		{
			name = add_char_size(name);
		}
		if (command[i] == ' ' || command[i] == '\0')
		{
			if (space == false)
				continue;
			space = false;
			if (counter == 0)
			{
				table_name = name;
				counter++;
			}
			else
			{
				if (_stricmp(name, "where") == 0)
				{
					//if (counter == 0)
					//	return false;
					temp1 = i;
					break;
				}
				else if (_stricmp(name, "order") == 0 || _stricmp(name, "top") == 0)
				{
					//if (counter == 0)
					//	return false;
					temp2 = i;
					break;
				}
				else
				{
					field_name.push_back(name);
				}
			}
			temp = 0;

			delete name;
			if (command[i] == '\0')return true;
			name_length = name_length_bak;
			name = new char[name_length];
		}
		else
		{
			space = true;
			name[temp++] = command[i];
			name[temp] = '\0';
		}
	}
	temp = 0;
	if (temp1 == 0)
	{
		where_command = "";
		if (temp2 == 0)
		{
			order_command = "";
			return true;
		}
		else
		{
			for (int i = temp2; i < length; i++)
			{
				if (command[i] != ' ')
				{
					temp2 = i;
					break;
				}
			}

			for (int i = temp2; i < length; ++i)
			{
				if (name_length == temp - 2)
				{
					name = add_char_size(name);
				}
				name[temp++] = command[i];
				name[temp] = '\0';
			}
			bool is_correct = deal_order(name);
			if (is_correct == false)
				return false;
			else
			{
				order_command = name;
				return true;
			}
		}
	}
	else if (temp1 != 0)//驴脧露篓脫脨where脳脰露脦
	{
		counter = 0;
		space = false;

		int temp_flag = 0;

		bool quote = false; //脜脨露脧脢脟路帽陆酶脠毛脣芦脪媒潞脜
		for (int i = temp1; i <= length; ++i)
		{
			if (command[i] != ' ')
			{
				temp1 = i;
				break;
			}
		}
		for (int i = temp1; i <= length; ++i)
		{
			if (name_length == temp - 2)
			{
				name = add_char_size(name);
			}

			if (command[i] == ' ' || command[i] == '\0')
			{
				if (space == false)continue;
				space = false;
				if (_stricmp(name, "order") == 0 || _stricmp(name, "top") == 0)
				{
					if (_stricmp(name, "top") == 0)
						temp_flag = 1;
					if (counter == 1)
						return false;

					char *str = new char[where_command.size() + 1];
					copy(str, where_command);
					bool check = deal_where(str);
					delete str;

					if (check == false)
					{
						return false;
					}
					temp2 = i;
					break;
				}
				else
				{
					where_command += name;
					where_command += " ";
					temp = 0;
					delete name;
					name_length = name_length_bak;
					name = new char[name_length];
				}
			}
			else
			{
				space = true;
				name[temp++] = command[i];
				name[temp] = '\0';
			}
		}
		if (temp2 == 0)	//脙禄脫脨order脫茂戮盲
		{
			order_command = "";
			return true;
		}
		else            //脫脨order脫茂戮盲禄貌脮脽top脫茂戮盲
		{

			//temp2 = 0;
			for (int i = temp2; i <= length; ++i)
			{
				if (command[i] != ' ')
				{
					temp2 = i;
					break;
				}
			}
			temp = 0;
			if (temp_flag == 1)
			{
				name[0] = 't';
				name[1] = 'o';
				name[2] = 'p';
				name[3] = '\0';
				temp = 3;
				if (temp2 == length)return false;
			}
			for (int i = temp2; i <= length; ++i)
			{
				if (name_length == temp - 2)
					name = add_char_size(name);
				name[temp++] = command[i];
				name[temp] = '\0';
			}
			bool check = deal_order(name);
			if (check == true)
				order_command = name;
			else return false;

		}
	}
	delete name;
	return true;
}
