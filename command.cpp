#include "command.h"
#include "HandleTable.h"


bool deal_select_data(char command[], int & length, string & table_name, string & where_command, string & order_command, vector<string>&field_name)
{
	char *name = new char[name_length];
	int temp = 0;
	
	int counter = 0;
	int flag = 0;
	int temp1 = 0;	//记录where语句
	int temp2 = 0;	//记录order 语句

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
	bool check = false;  //如果命令开始时就是空格怎么 办 加一个标记变量
	int temp = 0;

	int k = 0;	//记录第几个为非命令字段
	for (int i = 0; i < length; ++i)	//读入每条命令的第一个字段
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
	for (int i = 0; command[i] != '\0'; ++i)	//将小写字母转化为大写字母
	{
		if (command[i] <= 'z'&&command[i] >= 'a')
			command[i] = command[i] - 32;
	}
	int command_kind = -1;
	for (int i = 0; i < command_num; ++i)	//判断指令是否在指令集中已被定义
	{
		if (strcmp(command_content[i], command) == 0)
		{
			command_kind = i;
			break;
		}
	}
	if (command_kind == -1)	//如果为未定义的指令字段，结束当前指令的处理
	{
		printf("We don't have %s command\n", command);
		return;
	}
	cout << command << endl;
	//将剩下的命令字段向前挪到字符串首，也即现在的command字符串存的命令不包含CREATE，UPDATE等字段；
	//并且命令开头不含空格 
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

	switch (command_kind)	//八条命令以及错误处理
	{
	case 0:	//创建表的命令数据处理
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照下列格式输入插入建表命令\n");
			printf("CREATE table;\n字段1 数据类型 约束条件\n字段2 数据类型 约束条件\n");
			printf("eg:CREATE 成绩 数学 int 10 英语 int 00;\n");
			printf("============================\n");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照下列格式输入插入删除命令\n");
			printf("DROP table;\n");
			printf("eg:DROP 成绩;\n");
			printf("============================\n");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照下列格式输入插入记录命令\n");
			printf("SELECT 	table 字段1 字段2 字段3\
				   nwhere 条件\nORDER  by 字段 ASC(DESC)\n[ALL, TOP N, *]\n");
			printf("eg:SELECT 学生 年龄 性别\nwhere 成绩>“90”  top 5\nORDER BY 成绩 ASC; \n");
			printf("============================\n");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照下列格式输入插入记录命令\n");
			printf("Cancel table 字段名称1 字段名称2 ... 字段名称n,;\n");
			printf("eg:Cancel 成绩 班级 性别;\n");
			printf("============================\n");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照下列格式输入删除字段命令\n");
			printf("Cancel table 字段名称1 字段名称2 ... 字段名称n,;\n");
			printf("eg:Cancel 成绩 班级 性别;\n");
			printf("============================\n");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照以下格式输入命令:\n");
			printf("ADD table 字段 数据类型 约束条件\n");
			printf("eg:ADD 成绩 班级 String 00;");
			printf("PAY ATTENTION : You can only add one field\n");
			printf("=============================================");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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
			printf("您刚才输入的命令有错误!\n");
			printf("请按照以下格式输入命令:\n");
			printf("ADD table 字段 数据类型 约束条件\n");
			printf("eg:ADD 成绩 班级 String 00;");
			printf("=============================================");
			printf("刚才的命令将会是无效命令，如果您想重新执行刚才的操作请重新输入正确的命令:\n");
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


int check_data_type(string name)//判断字段数据类型
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

int check_constraint(string name)	//判断约束条件
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

bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType> field)//处理创建表的数据
{
	bool check = false;//如果含有多个空格
	bool error = false;//判断输入是否有错

	int count = -2;	//用来区分字段的属性
	int temp = 0;	//记录name的下标

	char * name = new char[name_length + 1];	//暂存所有的输入段name 只需要一个即可

	fieldType  myfield;
	for (int i = 0; i <= length; ++i)
	{
		//判断是否为空格
		if (command[i] != ' '&&command[i] != '\0') //非空格的话读入	
		{
			check = true;
			if (temp == name_length - 2)
			{
				add_char_size(name);
			}

			name[temp++] = command[i];
			name[temp] = '\0';

		}
		else if (command[i] == ' ' || command[i] == '\0')//是空格的话进行处理
		{
			if (check == true)	//处理开始的第一个字符为空格的情况
			{
				count++;
				check = false;

				if (count == -1)	//表名
				{
					name[temp] = '\0';
					temp = 0;
					table_name = name;
				}
				else
				{
					name[temp] = '\0';
					if (count % 3 == 0)	//字段名
					{
						myfield.fieldName = name;
					}
					else if (count % 3 == 1)//字段类型
					{
						for (int i = 0; name[i] != '\0'; ++i)
						{
							if (name[i] >= 'a'&&name[i] <= 'z')//将小写转换为大写
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
					else if (count % 3 == 2)//字段约束条件
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
							field.push_back(myfield);	//加入一个字段
						}
					}
					temp = 0;	//只要是读到空格之后就要将name下标置为0
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
	int temp = 0;	//name 的下标
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

	//name记录每一个字段
	for (int i = 0; i < length; ++i)
	{
		if (command[i] != ' ')	//如果不为' '的话 就将其加入name
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

	//接下来处理VALUES；
	bool quote = false;	//记录是否进入左引号
	temp = 0;

	name[0] = '\0';
	bool error = true;

	for (int i = flag; i < length; ++i)
	{
		if (temp == name_length - 2)
		{
			add_char_size(name);
		}
		if (quote == false)	//没有进入左引号
		{
			if (command[i] == ' ')	//将空格吃掉
				continue;
			else if (command[i] == '\"')//遇到引号那么就是左引号  将记录修改为true
			{
				quote = true;
				error = false;
			}
			else if (error == true)
			{
				break;
			}

		}
		else     //进入了左引号
		{
			if (command[i] == '\"')	//遇到右引号
			{
				if (command[i - 1] == '\\')	//是否为转义的
				{
					command[temp - 1] = '"';		//如果 是转义的" 直接 将\去掉
					command[temp] = '\0';
				}
				else        //如果不是  出左引号
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

//已解决空格
bool deal_update_data(char command[], int & length, string & table_name,
	vector<pairData> & updata_data, string & where_command
	)
{

	pairData my_pair;
	char *name = new char[name_length]; //暂存每个字段以及记录

	int temp = 0;	//name的下标
	int counter = 0;	//总共有多少个字段以及记录

	int flag = 0;	//记录遇到where的下标

	bool quote = false;	//帮助判断是否进入引号
	bool effec = false;	//帮助判断空格是否该舍弃  目前空格该舍弃
	bool have_where = false;

	for (int i = 0; i <= length; ++i)
	{
		if (temp == name_length - 2)
		{
			add_char_size(name);
		}

		if (quote == false)	//没有进入引号  是字段或者表名
		{
			if (command[i] == ' ' || command[i] == '=')	//为空格
			{
				if (stricmp(name, "where") == 0)	//必须是没有进入引号的where语句才行
				{
					have_where = true;
					flag = i;
					break;
				}
				if (effec == true)	//如果字符串开头是空格就不会进入
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
			else if (command[i] == '\"')//扫到双引号
			{
				if (command[i - 1] == '=')	//进入双引号
				{
					quote = true;
				}
				else if (command[i - 1] == '\\')	//是字段中的双引号
				{
					command[temp - 1] = '\"';
					command[temp] = '\0';
				}
			}
			else       //
			{
				effec = true;	//开头的空格舍弃

				name[temp++] = command[i];
				name[temp] = '\0';
			}
		}
		else if (quote == true)//进入引号了
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
					if (counter % 2 == 0)	//如果不配对的话  就是错的
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

	for (int i = flag; i < length; ++i)	//如果开头有空格就跳出
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

	for (int i = flag; i < length; ++i)	//如果开头有空格就跳出
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
	int temp = 0;	//记录name的下标
	bool error = false;
	bool check = false;	//处理多个空格
	char * name = new char[name_length];	//暂存所有的输入段 name 只需要一个即可

	fieldType myfield;
	myfield.fieldNum = 0;
	for (int i = 0; i <= length; ++i)
	{
		if (command[i] != ' '&&command[i] != '\0') //非空格的话读入	
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
					if (name[i] >= 'a'&&name[i] <= 'z')//将小写转换为大写
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
