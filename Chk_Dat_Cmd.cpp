#include "Chk_Dat_Cmd.h"
#include "Command.h"
#include <cstring>
bool deal_insert_data(char command[], int & length, string & table_name, vector<pairData>& my_data)
{
	int counter = -1;

	char *name = new char[name_length];
	int temp = 0;
	vector<string> field;
	vector<string> info;

	int flag = 0;
	bool space = false;
	//name¼ÇÂ¼Ã¿Ò»¸ö×Ö¶Î
	for (int i = 0; i < length; ++i)
	{
		if (command[i] != ' ')	//Èç¹û²»Îª' 'µÄ»° ¾Í½«Æä¼ÓÈëname
		{
			if (temp == name_length - 2)
			{
				name = add_char_size(name);
			}
			space = true;
			name[temp++] = command[i];
			name[temp] = '\0';
		}
		else
		{
			if (space == false)
				continue;
			space = false;
			if (counter == -1)
			{
				table_name = name;
			}
			else
			{
				if (_stricmp(name, "VALUES") == 0)
				{
					flag = i;
					break;
				}
				else
				{
					field.push_back(name);
				}
			}

			temp = 0;
			counter++;

			name_length = name_length_bak;
			delete name;
			name = new char[name_length];
		}

	}

	//½ÓÏÂÀ´´¦ÀíVALUES£»
	bool quote = false;	//¼ÇÂ¼ÊÇ·ñ½øÈë×óÒýºÅ
	temp = 0;

	name[0] = '\0';
	bool error = true;

	for (int i = flag; i < length; ++i)
	{
		if (temp == name_length - 2)
		{
			name = add_char_size(name);
		}
		if (quote == false)	//Ã»ÓÐ½øÈë×óÒýºÅ
		{
			if (command[i] == ' ')	//½«¿Õ¸ñ³Ôµô
				continue;
			else if (command[i] == '\"')//Óöµ½ÒýºÅÄÇÃ´¾ÍÊÇ×óÒýºÅ  ½«¼ÇÂ¼ÐÞ¸ÄÎªtrue
			{
				quote = true;
				error = false;
			}
			else if (error == true)
			{
				break;
			}

		}
		else     //½øÈëÁË×óÒýºÅ
		{
			if (command[i] == '\"')	//Óöµ½ÓÒÒýºÅ
			{
				if (command[i - 1] == '\\')	//ÊÇ·ñÎª×ªÒåµÄ
				{
					command[temp - 1] = '"';		//Èç¹û ÊÇ×ªÒåµÄ" Ö±½Ó ½«\È¥µô
					command[temp] = '\0';
				}
				else        //Èç¹û²»ÊÇ  ³ö×óÒýºÅ
				{
					quote = false;
					info.push_back(name);
					temp = 0;

					delete name;
					name_length = name_length_bak;
					name = new char[name_length];
				}
			}
			else
			{
				name[temp++] = command[i];
				name[temp] = '\0';
			}
		}
	}

	delete name;

	int my_size = 0;
	if (field.size() != info.size())
	{
		error = true;
		if (counter == 0)
			error = false;
	}
	else
	{
		my_size = info.size();
	}
	if (my_size == 0)return false;
	if (error == true)
	{
		return false;
	}
	else
	{
		pairData my_pair;
		int i = 0;
		vector<string>::iterator is1;
		vector<string>::iterator is2;
		if (field.size() != 0)
			is1 = field.begin();
		is2 = info.begin();

		while (i++ < my_size)
		{
			if (field.size() != 0)
			{
				my_pair.fieldName = *is1++;
			}
			else
				my_pair.fieldName = "";
			my_pair.data = *is2++;
			my_data.push_back(my_pair);
		}
	}
	return true;
}

bool deal_drop_data(char command[], int & length, string & table_name)
{
	char * name = new char[name_length];

	bool check = false;
	int counter = 0;
	int temp = 0;
	for (int i = 0; i <= length; ++i)
	{
		if (name_length - 2 == temp)
		{
			name = add_char_size(name);
		}
		if (command[i] == ' ' || command[i] == '\0')
		{
			if (check == true)
				counter++;
			check = false;
		}
		else
		{
			if (counter == 1)
				return false;
			check = true;
			name[temp++] = command[i];
			name[temp] = '\0';
		}
	}
	table_name = name;
	delete name;

	return true;
}

bool deal_delete_data(char command[], int & length, string & table_name, string & where_command)
{

	char *name = new char[name_length];
	int temp = 0;
	int flag;

	int effec = false;
	int counter = 0;
	for (int i = 0; i <= length; ++i)
	{
		if (temp == name_length - 2)
		{
			name = add_char_size(name);
		}

		if (command[i] == ' ' || command[i] == '\0')
		{
			if (effec == false)continue;
			effec = false;
			if (_stricmp(name, "where") == 0)
			{
				flag = i;
				break;
			}
			if (counter == 0)
			{
				table_name = name;
			}
			if (counter > 1)
				return false;
			counter++;

			temp = 0;
			delete name;
			name_length = name_length_bak;
			name = new char[name_length];
		}
		else
		{
			effec = true;

			name[temp++] = command[i];
			name[temp] = '\0';

			
		}
	}

	for (int i = flag; i < length; ++i)	//Èç¹û¿ªÍ·ÓÐ¿Õ¸ñ¾ÍÌø³ö
	{
		if (command[i] != ' ')
		{
			flag = i;
			break;
		}
	}

	temp = 0;
	for (int i = flag; i < length; ++i)
	{
		if (temp == name_length - 2)
		{
			name = add_char_size(name);
		}
		name[temp++] = command[i];
	}
	name[temp] = '\0';

	bool is_correct = deal_where(name);
	where_command = name;
	delete name;
	return is_correct;
}

bool deal_update_data(char command[], int & length, string & table_name,vector<pairData> & updata_data, string & where_command)
{

	pairData my_pair;
	char *name = new char[name_length]; //ÔÝ´æÃ¿¸ö×Ö¶ÎÒÔ¼°¼ÇÂ¼

	int temp = 0;	//nameµÄÏÂ±ê
	int counter = 0;	//×Ü¹²ÓÐ¶àÉÙ¸ö×Ö¶ÎÒÔ¼°¼ÇÂ¼

	int flag = 0;	//¼ÇÂ¼Óöµ½whereµÄÏÂ±ê

	bool quote = false;	//°ïÖúÅÐ¶ÏÊÇ·ñ½øÈëÒýºÅ
	bool effec = false;	//°ïÖúÅÐ¶Ï¿Õ¸ñÊÇ·ñ¸ÃÉáÆú  Ä¿Ç°¿Õ¸ñ¸ÃÉáÆú
	bool have_where = false;

	for (int i = 0; i <= length; ++i)
	{
		if (temp == name_length - 2)
		{
			name = add_char_size(name);
		}

		if (quote == false)	//Ã»ÓÐ½øÈëÒýºÅ  ÊÇ×Ö¶Î»òÕß±íÃû
		{
			if (command[i] == ' ' || command[i] == '=')	//Îª¿Õ¸ñ
			{
				if (_stricmp(name, "where") == 0)	//±ØÐëÊÇÃ»ÓÐ½øÈëÒýºÅµÄwhereÓï¾ä²ÅÐÐ
				{
					have_where = true;
					flag = i;
					break;
				}
				if (effec == true)	//Èç¹û×Ö·û´®¿ªÍ·ÊÇ¿Õ¸ñ¾Í²»»á½øÈë
				{
					if (counter == 0)
						table_name = name;
					else if (counter % 2 == 1)
					{
						my_pair.fieldName = name;
					}
					else
					{
						delete name;
						return false;
					}

					effec = false;

					temp = 0;
					delete name;
					name_length = name_length_bak;
					name = new char[name_length];
					counter++;
				}

			}
			else if (command[i] == '\"')//É¨µ½Ë«ÒýºÅ
			{
				if (command[i - 1] == '=')	//½øÈëË«ÒýºÅ
				{
					quote = true;
				}
				else if (command[i - 1] == '\\')	//ÊÇ×Ö¶ÎÖÐµÄË«ÒýºÅ
				{
					command[temp - 1] = '\"';
					command[temp] = '\0';
				}
			}
			else       //
			{
				effec = true;	//¿ªÍ·µÄ¿Õ¸ñÉáÆú

				name[temp++] = command[i];
				name[temp] = '\0';
			}
		}
		else if (quote == true)//½øÈëÒýºÅÁË
		{
			if (command[i] == '\"')
			{
				if (command[i - 1] == '\\')
				{
					command[temp - 1] = '\"';
					command[temp] = '\0';
				}
				else
				{
					if (counter % 2 == 0)	//Èç¹û²»Åä¶ÔµÄ»°  ¾ÍÊÇ´íµÄ
					{
						my_pair.data = name;
						updata_data.push_back(my_pair);

						temp = 0;
						delete name;
						name_length = name_length_bak;
						name = new char[name_length];
						counter++;
					}
					else
					{
						delete name;
						return false;
					}
				}
			}
			else
			{
				name[temp++] = command[i];
				name[temp] = '\0';
			}
		}
	}
	delete name;

	if (counter % 2 == 0)return false;

	if (have_where == false) return true;

	for (int i = flag; i < length; ++i)	//Èç¹û¿ªÍ·ÓÐ¿Õ¸ñ¾ÍÌø³ö
	{
		if (command[i] != ' ')
		{
			flag = i;
			break;
		}
	}

	temp = 0;
	for (int i = flag; i < length; ++i)
	{
		if (temp == name_length - 2)
		{
			name = add_char_size(name);
		}
		name[temp++] = command[i];
	}
	name[temp] = '\0';

	bool is_correct = deal_where(name);
	where_command = name;
	delete name;

	return is_correct;

}

