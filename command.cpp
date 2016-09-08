#include "command.h"
#include "HandleTable.h"


bool deal_select_data(char command[], int & length, string & table_name, string & where_command, string & order_command, vector<string>&field_name)
{
	char *name = new char[name_length];
	int temp = 0;
	
	int counter = 0;
	int flag = 0;
	int temp1 = 0;	//��¼where���
	int temp2 = 0;	//��¼order ���

	bool space = false;
	for (int i = 0; i <= length; ++i)
	{
		if (name_length - 2 == temp)
		{
			add_char_size(name);
		}
		if (command[i] == ' ' || command[i] == '\0')
		{
			if (space == false)
				continue;
			space = false;
			if (counter == 0)
			{
				table_name = name;
				counter = 1;
			}
			else
			{
				if (stricmp(name, "where") == 0)
				{
					temp1 = i;
					break;
				}
				else if (stricmp(name, "order") == 0)
				{
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
		if (temp2 == 0)
		{
			return true;
		}
		else
		{
			for (int i = temp2; i < length;i++)
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
					add_char_size(name);
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
				delete name;
				return true;
			}
		}
	}
	else if (temp1 != 0)
	{
		
	}
	return true;
}

void deal_with_command(char cmd[], int & length)
{

	char * command = new char[length + 1];
	bool check = false;  //������ʼʱ���ǿո���ô �� ��һ����Ǳ���
	int temp = 0;

	int k = 0;	//��¼�ڼ���Ϊ�������ֶ�
	for (int i = 0; i < length; ++i)	//����ÿ������ĵ�һ���ֶ�
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
	for (int i = 0; command[i] != '\0'; ++i)	//��Сд��ĸת��Ϊ��д��ĸ
	{
		if (command[i] <= 'z'&&command[i] >= 'a')
			command[i] = command[i] - 32;
	}
	int command_kind = -1;
	for (int i = 0; i < command_num; ++i)	//�ж�ָ���Ƿ���ָ����ѱ�����
	{
		if (strcmp(command_content[i], command) == 0)
		{
			command_kind = i;
			break;
		}
	}
	if (command_kind == -1)	//���Ϊδ�����ָ���ֶΣ�������ǰָ��Ĵ���
	{
		printf("We don't have %s command\n", command);
		return;
	}
	cout << command << endl;
	//��ʣ�µ������ֶ���ǰŲ���ַ����ף�Ҳ�����ڵ�command�ַ�������������CREATE��UPDATE���ֶΣ�
	//�������ͷ�����ո� 
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
	cout << command << endl;

	length = temp;

	switch (command_kind)	//���������Լ�������
	{
	case 0:	//��������������ݴ���
	{
		string table_name;
		vector<fieldType> my_field;
		bool check = deal_create_data(command, length,table_name,my_field);
		if (check == true)
		{
			createTable(table_name, my_field);
		}
		else
		{
			printf("���ղ�����������д���!\n");
			printf("�밴�����и�ʽ������뽨������\n");
			printf("CREATE table;\n�ֶ�1 �������� Լ������\n�ֶ�2 �������� Լ������\n");
			printf("eg:CREATE �ɼ� ��ѧ int 10 Ӣ�� int 00;\n");
			printf("============================\n");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
		}
		break;
	}
	case 1:	//drop
	{
		string table_name;
		bool check = deal_drop_data(command, length, table_name);
		if (check ==true)
			dropTable(table_name);
		else
		{
			printf("���ղ�����������д���!\n");
			printf("�밴�����и�ʽ�������ɾ������\n");
			printf("DROP table;\n");
			printf("eg:DROP �ɼ�;\n");
			printf("============================\n");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
		}
		break;
	}
	case 2:
	{
		string table_name;
		string where_command;
		bool check = deal_select_data(command, length, table_name, where_command);
		if (check == true)
			selectData(table_name, where_command);
		else
		{
			printf("���ղ�����������д���!\n");
			printf("�밴�����и�ʽ��������¼����\n");
			printf("SELECT 	table �ֶ�1 �ֶ�2 �ֶ�3\
				   nwhere ����\nORDER  by �ֶ� ASC(DESC)\n[ALL, TOP N, *]\n");
			printf("eg:SELECT ѧ�� ���� �Ա�\nwhere �ɼ�>��90��  top 5\nORDER BY �ɼ� ASC; \n");
			printf("============================\n");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
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
			insertData(table_name, my_data);
		else
		{
			printf("���ղ�����������д���!\n");
			printf("�밴�����и�ʽ��������¼����\n");
			printf("Cancel table �ֶ�����1 �ֶ�����2 ... �ֶ�����n,;\n");
			printf("eg:Cancel �ɼ� �༶ �Ա�;\n");
			printf("============================\n");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
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
			printf("���ղ�����������д���!\n");
			printf("�밴�����и�ʽ����ɾ���ֶ�����\n");
			printf("Cancel table �ֶ�����1 �ֶ�����2 ... �ֶ�����n,;\n");
			printf("eg:Cancel �ɼ� �༶ �Ա�;\n");
			printf("============================\n");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
		}
		break;
	}
	case 5:
	{
		string table_name;
		string where_command;
		deal_delete_data(command, length, table_name, where_command);
		deleteData(table_name, where_command);
		break;
	}
	case 6:
	{
		string table_name;
		fieldType my_field;
		bool check  = deal_add_data(command, length, table_name, my_field);
		if (check== true)
		{
			addField(table_name, my_field);
		}
		else
		{
			printf("���ղ�����������д���!\n");
			printf("�밴�����¸�ʽ��������:\n");
			printf("ADD table �ֶ� �������� Լ������\n");
			printf("eg:ADD �ɼ� �༶ String 00;");
			printf("PAY ATTENTION : You can only add one field\n");
			printf("=============================================");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
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
			printf("���ղ�����������д���!\n");
			printf("�밴�����¸�ʽ��������:\n");
			printf("ADD table �ֶ� �������� Լ������\n");
			printf("eg:ADD �ɼ� �༶ String 00;");
			printf("=============================================");
			printf("�ղŵ����������Ч��������������ִ�иղŵĲ���������������ȷ������:\n");
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


int check_data_type(string name)//�ж��ֶ���������
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

int check_constraint(string name)	//�ж�Լ������
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

bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType> field)//�������������
{
	bool check = false;//������ж���ո�
	bool error = false;//�ж������Ƿ��д�

	int count = -2;	//���������ֶε�����
	int temp = 0;	//��¼name���±�

	char * name = new char[name_length + 1];	//�ݴ����е������name ֻ��Ҫһ������

	fieldType  myfield;
	for (int i = 0; i <= length; ++i)
	{
		//�ж��Ƿ�Ϊ�ո�
		if (command[i] != ' '&&command[i] != '\0') //�ǿո�Ļ�����	
		{
			check = true;
			if (temp == name_length - 2)
			{
				add_char_size(name);
			}

			name[temp++] = command[i];
			name[temp] = '\0';

		}
		else if (command[i] == ' ' || command[i] == '\0')//�ǿո�Ļ����д���
		{
			if (check == true)	//����ʼ�ĵ�һ���ַ�Ϊ�ո�����
			{
				count++;
				check = false;

				if (count == -1)	//����
				{
					name[temp] = '\0';
					temp = 0;
					table_name = name;
				}
				else
				{
					name[temp] = '\0';
					if (count % 3 == 0)	//�ֶ���
					{
						myfield.fieldName = name;
					}
					else if (count % 3 == 1)//�ֶ�����
					{
						for (int i = 0; name[i] != '\0'; ++i)
						{
							if (name[i] >= 'a'&&name[i] <= 'z')//��Сдת��Ϊ��д
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
					else if (count % 3 == 2)//�ֶ�Լ������
					{
						if (temp > 3)
							return false;
						int judge_type = check_constraint(name);
						switch (judge_type)
						{
						case 10:	// 10
							return false;
						case 0:		// 00
							myfield.judgeBound = 0;
							break;
						case 11:	// 11
							myfield.judgeBound = 11;
							break;
						case 1:		// 01
							myfield.judgeBound = 1;
							break;
						case -1:
							return false;
						}
						if (!error)
						{
							field.push_back(myfield);	//����һ���ֶ�
						}
					}
					temp = 0;	//ֻҪ�Ƕ����ո�֮���Ҫ��name�±���Ϊ0
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



bool deal_cancel_data(char command[], int &length, string & table_name, vector<string> &field_name)
{
	char * name = new char[name_length];
	bool flag = false;
	int counter = 0;
	int temp = 0;	//name ���±�
	for (int i = 0; i <= length; ++i)
	{
		if (command[i] != ' '&&command[i] != '\0')
		{
			flag = true;
			if (temp == name_length - 2)
			{
				add_char_size(name);
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


bool deal_insert_data(char command[], int & length, string & table_name, vector<pairData>& my_data)
{
	int counter = -1;

	char *name = new char[name_length];
	int temp = 0;
	vector<string> field;
	vector<string> info;

	int flag = 0;

	//name��¼ÿһ���ֶ�
	for (int i = 0; i < length; ++i)
	{
		if (command[i] != ' ')	//�����Ϊ' '�Ļ� �ͽ������name
		{
			if (temp == name_length - 2)
			{
				add_char_size(name);
			}
			name[temp++] = command[i];
			name[temp] = '\0';
		}
		else
		{
			if (counter == -1)
			{
				table_name = name;
			}
			else
			{
				if (stricmp(name, "VALUES") == 0)
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

	//����������VALUES��
	bool quote = false;	//��¼�Ƿ����������
	temp = 0;

	name[0] = '\0';
	bool error = true;

	for (int i = flag; i < length; ++i)
	{
		if (temp == name_length - 2)
		{
			add_char_size(name);
		}
		if (quote == false)	//û�н���������
		{
			if (command[i] == ' ')	//���ո�Ե�
				continue;
			else if (command[i] == '\"')//����������ô����������  ����¼�޸�Ϊtrue
			{
				quote = true;
				error = false;
			}
			else if (error == true)
			{
				break;
			}

		}
		else     //������������
		{
			if (command[i] == '\"')	//����������
			{
				if (command[i - 1] == '\\')	//�Ƿ�Ϊת���
				{
					command[temp - 1] = '"';		//��� ��ת���" ֱ�� ��\ȥ��
					command[temp] = '\0';
				}
				else        //�������  ��������
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

//�ѽ���ո�
bool deal_update_data(char command[], int & length, string & table_name,
	vector<pairData> & updata_data, string & where_command
	)
{

	pairData my_pair;
	char *name = new char[name_length]; //�ݴ�ÿ���ֶ��Լ���¼

	int temp = 0;	//name���±�
	int counter = 0;	//�ܹ��ж��ٸ��ֶ��Լ���¼

	int flag = 0;	//��¼����where���±�

	bool quote = false;	//�����ж��Ƿ��������
	bool effec = false;	//�����жϿո��Ƿ������  Ŀǰ�ո������
	bool have_where = false;

	for (int i = 0; i <= length; ++i)
	{
		if (temp == name_length - 2)
		{
			add_char_size(name);
		}

		if (quote == false)	//û�н�������  ���ֶλ��߱���
		{
			if (command[i] == ' ' || command[i] == '=')	//Ϊ�ո�
			{
				if (stricmp(name, "where") == 0)	//������û�н������ŵ�where������
				{
					have_where = true;
					flag = i;
					break;
				}
				if (effec == true)	//����ַ�����ͷ�ǿո�Ͳ������
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
			else if (command[i] == '\"')//ɨ��˫����
			{
				if (command[i - 1] == '=')	//����˫����
				{
					quote = true;
				}
				else if (command[i - 1] == '\\')	//���ֶ��е�˫����
				{
					command[temp - 1] = '\"';
					command[temp] = '\0';
				}
			}
			else       //
			{
				effec = true;	//��ͷ�Ŀո�����

				name[temp++] = command[i];
				name[temp] = '\0';
			}
		}
		else if (quote == true)//����������
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
					if (counter % 2 == 0)	//�������ԵĻ�  ���Ǵ��
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

	for (int i = flag; i < length; ++i)	//�����ͷ�пո������
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
			add_char_size(name);
		}
		name[temp++] = command[i];
	}
	name[temp] = '\0';

	bool is_correct = deal_where(name);
	where_command = name;
	delete name;

	return is_correct;

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
			add_char_size(name);
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
			add_char_size(name);
		}

		if (command[i] == ' ' || command[i] == '\0')
		{
			if (effec == false)continue;
			effec = false;
			if (stricmp(name, "where") == 0)
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
		}
		else
		{
			effec = true;

			name[temp++] = command[i];
			name[temp] = '\0';

			temp = 0;
			delete name;
			name_length = name_length_bak;
			name = new char[name_length];
		}
	}

	for (int i = flag; i < length; ++i)	//�����ͷ�пո������
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
			add_char_size(name);
		}
		name[temp++] = command[i];
	}
	name[temp] = '\0';

	bool is_correct = deal_where(name);
	where_command = name;
	delete name;
	return is_correct;
}

bool deal_where(char where_command[])
{
	return true;
}

bool deal_add_data(char command[], int &length, string &table_name, fieldType & my_field)
{
	int counter = 0;
	int temp = 0;	//��¼name���±�
	bool error = false;
	bool check = false;	//�������ո�
	char * name = new char[name_length];	//�ݴ����е������ name ֻ��Ҫһ������

	fieldType myfield;
	myfield.fieldNum = 0;
	for (int i = 0; i <= length; ++i)
	{
		if (command[i] != ' '&&command[i] != '\0') //�ǿո�Ļ�����	
		{
			check = true;
			if (temp == name_length - 2)
			{
				add_char_size(name);
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
					if (name[i] >= 'a'&&name[i] <= 'z')//��Сдת��Ϊ��д
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
					myfield.judgeBound = 0;
					break;
				case 11:	// 11
					myfield.judgeBound = 11;
					break;
				case 1:		// 01
					myfield.judgeBound = 1;
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
	return true;
}
void add_char_size(char name[])
{
	char *temp = new char[name_length + 1];
	strcpy(temp, name);
	name = new char[name_length + add_size];
	name_length += add_size;
	strcpy(name, temp);
	delete temp;
}
