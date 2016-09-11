#include"Chk_Table_Cmd.h"
#include "Command.h"
bool deal_add_data(char command[], int &length, string &table_name, fieldType & myfield)
{
	int counter = 0;
	int temp = 0;	//¼ÇÂ¼nameµÄÏÂ±ê
	bool error = false;
	bool check = false;	//´¦Àí¶à¸ö¿Õ¸ñ
	char * name = new char[name_length];	//ÔÝ´æËùÓÐµÄÊäÈë¶Î name Ö»ÐèÒªÒ»¸ö¼´¿É

	myfield.fieldNum = 0;
	for (int i = 0; i <= length; ++i)
	{
		if (command[i] != ' '&&command[i] != '\0') //·Ç¿Õ¸ñµÄ»°¶ÁÈë	
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
					if (name[i] >= 'a'&&name[i] <= 'z')//½«Ð¡Ð´×ª»»Îª´óÐ´
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
	int temp = 0;	//name µÄÏÂ±ê
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

bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType>& field)//´¦Àí´´½¨±íµÄÊý¾Ý
{
	bool check = false;//Èç¹ûº¬ÓÐ¶à¸ö¿Õ¸ñ
	bool error = false;//ÅÐ¶ÏÊäÈëÊÇ·ñÓÐ´í

	int count = -2;	//ÓÃÀ´Çø·Ö×Ö¶ÎµÄÊôÐÔ
	int temp = 0;	//¼ÇÂ¼nameµÄÏÂ±ê

	char * name = new char[name_length + 1];	//ÔÝ´æËùÓÐµÄÊäÈë¶Îname Ö»ÐèÒªÒ»¸ö¼´¿É

	fieldType  myfield;
	for (int i = 0; i <= length; ++i)
	{
		//ÅÐ¶ÏÊÇ·ñÎª¿Õ¸ñ
		if (command[i] != ' '&&command[i] != '\0') //·Ç¿Õ¸ñµÄ»°¶ÁÈë	
		{
			check = true;
			if (temp == name_length - 2)
			{
				name = add_char_size(name);
			}

			name[temp++] = command[i];
			name[temp] = '\0';

		}
		else if (command[i] == ' ' || command[i] == '\0')//ÊÇ¿Õ¸ñµÄ»°½øÐÐ´¦Àí
		{
			if (check == true)	//´¦Àí¿ªÊ¼µÄµÚÒ»¸ö×Ö·ûÎª¿Õ¸ñµÄÇé¿ö
			{
				count++;
				check = false;

				if (count == -1)	//±íÃû
				{
					name[temp] = '\0';
					temp = 0;
					table_name = name;
				}
				else
				{
					name[temp] = '\0';
					if (count % 3 == 0)	//×Ö¶ÎÃû
					{
						myfield.fieldName = name;
					}
					else if (count % 3 == 1)//×Ö¶ÎÀàÐÍ
					{
						for (int i = 0; name[i] != '\0'; ++i)
						{
							if (name[i] >= 'a'&&name[i] <= 'z')//½«Ð¡Ð´×ª»»Îª´óÐ´
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
					else if (count % 3 == 2)//×Ö¶ÎÔ¼ÊøÌõ¼þ
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
							field.push_back(myfield);	//¼ÓÈëÒ»¸ö×Ö¶Î
						}
					}
					temp = 0;	//Ö»ÒªÊÇ¶Áµ½¿Õ¸ñÖ®ºó¾ÍÒª½«nameÏÂ±êÖÃÎª0
				}
			}
			if (error) break;
			delete name;
			name_length = name_length_bak;
			name = new char[name_length + 1];
		}
	}
	delete name;

	return true;
}

