#include "Deal_With_Where.h"
int step_1(char x)
{
	if (x == '+')
		return 1;
	if (x == '*')
		return 2;
	if (x == '(')
		return 4;
	if (x == ')')
		return 5;
	else
		return 0;
}
int error(string ss)
{
	int expect, zuo, you;
	expect = 0;
	zuo = you = 0;
	int i, len;
	len = (int)ss.length();
	int num;
	for (i = 0; i<len; i++)
	{
		if (expect == 0)
		{
			num = ss[i] - '0';
			if ((num <= 9) && (num >= 0))//情况1
			{
				while ((num <= 9) && (num >= 0))
				{
					num = ss[i + 1] - '0';
					if (i + 1>len - 1)
						break;
					if ((num <= 9) && (num >= 0))
					{
						i++;
					}
				}
				expect = 1;
				continue;
			}
			else if (ss[i] == '(')
			{
				zuo++;
				continue;
			}
			else
				return 1;
		}
		if (expect == 1)
		{
			num = ss[i] - '0';
			if (ss[i] == '(')
			{
				return 1;
			}
			else if (ss[i] == ')')
			{
				if (zuo == 0)
					return 1;
				else
				{
					zuo--;
					continue;
				}
			}
			else if ((num <= 9) && (num >= 0))
				return 1;
			else
			{
				expect = 0;
				continue;
			}
		}
	}
	if (zuo != you)
		return 1;
	else
		return 0;
}
int find_ans(int x, char y, int z)
{
	if (y == '+')
	{
		return x + z;
	}
	if (y == '-')
	{
		return x - z;
	}
	if (y == '*')
	{
		return x*z;
	}
	else
		return 0;
}
int calculation(table &theTable, string ss)
{
	stack <int > numm;
	stack<char> s;
	int i, divide1, error1;
	int type;
	divide1 = 0;
	error1 = 0;
	type = 0;         //type 为0的时候输入数字，为1的时候输入运算符//
	if (error(ss))
	{

		return (int)theTable.data.size();
	}
	else
	{
		int len;
		len = (int)ss.length();
		while (!numm.empty())
		{
			numm.pop();
		}
		while (!s.empty())
		{
			s.pop();
		}
		for (i = 0; i<len; i++)
		{

			if ((ss[i] <= '9') && (ss[i] >= '0'))//如果是数字的话
			{
				int fu;
				fu = 0;
				if (i>1)
				{
					if ((ss[i - 1] == '-') && ((ss[i - 2]>'9') || (ss[i - 2]<'0')))//判断是否为负数（没有考虑首位为负）
						fu = 1;
				}
				if (i == 1)
				{
					if (ss[i - 1] == '-')
						fu = 1;//考虑首位
				}
				int num1, temp;
				num1 = ss[i] - '0';
				while (1)
				{
					temp = ss[i + 1] - '0';
					if ((temp <= 9) && (temp >= 0))
					{
						num1 = num1 * 10 + temp;
						i++;
					}
					else
						break;
				}
				if (fu == 1)
					num1 = 0 - num1;
				numm.push(num1);//放入栈
			}
			else
			{
				int cal1, cal2;
				cal1 = step_1(ss[i]);
				if (type == 0 && ss[i] == '-')
					continue;
				else if (type == 0 && ss[i] == '(')
					type = type;
				else if (type == 1 && ss[i] == ')')
					type = type;
				else if (type == 1)
					type = (type ^ 1);
				while (!s.empty())
				{
					cal2 = step_1(s.top());
					if (((cal2<cal1) && (cal1 != 5)) || ((cal1 == cal2) && (cal1 == 3)))
					{
						break;
					}
					else if (cal1 == 5)
					{
						while (cal2 != 4)
						{
							int n1, n2;
							char c;
							c = s.top();
							n1 = numm.top();
							numm.pop();
							n2 = numm.top();
							numm.pop();
							numm.push(find_ans(n2, c, n1));
							s.pop();
							cal2 = step_1(s.top());
						}
						s.pop();
						break;
					}
					if ((cal1 <= cal2))
					{
						if (cal2 != 4)
						{
							int n1, n2;
							char c;
							c = s.top();
							n1 = numm.top();
							numm.pop();
							n2 = numm.top();
							numm.pop();
							numm.push(find_ans(n2, c, n1));
							s.pop();
						}
						else
							break;
					}
				}
				if (cal1 != 5)
					s.push(ss[i]);
			}
		}
		while (!s.empty())
		{
			int n1, n2;
			char c;
			c = s.top();
			n1 = numm.top();
			numm.pop();
			n2 = numm.top();
			numm.pop();
			numm.push(find_ans(n2, c, n1));
			s.pop();
		}
		if (numm.size() == 1)
			return numm.top();
		else
			return -1;
	}

	return 0;
}//去空格去“”
string preWhere(string ss)
{
	int i, flag1, flag2;
	flag1 = flag2 = 0;
	//cout << ss << endl;
	for (i = 0; i<ss.size(); i++)
	{
		if (ss[i] == '\"')
		{
			flag1++;
			ss.erase(i, 1);
			i--;
		}
		if ((ss[i] == ' ') && (flag1 % 2 == 0))
		{
			ss.erase(i, 1);
			i--;
		}
	}
	return ss;
}
//出错处理
string check_true(table &a, shortString b)
{
	string ss;
	int i, flag;
	flag = 0;
	//map
	for (i = 0; i<a.field.size(); i++)
	{
		if (a.field[i].fieldName.compare(b.fieldName) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		ss = "WRONG";
		return ss;
	}
	//ex
	else
	{
		for (int i = 0; i<a.field.size(); i++)
		{
			if (a.field[i].fieldName == b.fieldName)
			{
				if ((a.field[i].theType == STRING) || (a.field[i].theType == NONE) || (a.field[i].theType == DATE))
				{

					if (b.compareMark.compare("<") == 0 || b.compareMark.compare(">") == 0)
					{
						ss = "WRONG";
						return ss;
					}
					else
					{
						ss = "STRING";
						return ss;
					}
				}
				if ((a.field[i].theType == INT) || (a.field[i].theType == DOUBLE))
				{
					int len = (int)b.value.length();
					for (int i = 0; i<len; i++)
					{
						if (b.value[i]<48 || b.value[i]>57)//ascii
						{
							ss = "WRONG";
							return ss;
						}
					}
					if (a.field[i].theType == INT)
					{
						ss = "INT";
						return ss;
					}
					if (a.field[i].theType == DOUBLE)
					{
						ss = "DOUBLE";
						return ss;
					}
				}
			}

		}
	}
	return ss;
}
//分解成小句子
djString dealWith_Command(table &a, string command)
{
	djString temp1;
	vector<shortString> temp2;
	shortString temp3;
	int flag1, i, j;
	int len = (int)command.length() - 1;//;
	for (i = 0; i <= len; i++)
	{
		flag1 = i;
		if (command[i] == '(')
		{
			temp3.left = 1;
			i++;
			flag1 = i;
		}
		//1
		while (1)
		{
			if (command[i] == '<' || command[i] == '>' || command[i] == '=' || command[i] == '!')
				break;
			if (i == len - 1)
				break;
			else
				i++;
		}
		//1
		for (j = flag1; j<i; j++)
		{
			temp3.fieldName += command[j];
		}
		//2
		if (command[i] == '!')
		{
			temp3.compareMark = "!=";
			i = i + 3;//"
		}
		else
		{
			temp3.compareMark += command[i];
			i = i + 1;
		}
		flag1 = i;
		//3
		while (1)
		{
			if (command[i] == 'A' || command[i] == 'O')
				break;
			if (i == len)
				break;
			i++;
		}
		//3
		if (command[i - 1] == ')')
			i--;
		for (j = flag1; j<i; j++)
		{
			temp3.value += command[j];
		}
		if (i == len&&command[i] != ')')
			temp3.value += command[i];
		//4
		if (command[i] == ')')
		{
			temp3.right = 1;
			i++;
		}
		if (command[i] == 'A')
		{
			i = i + 2;
			temp3.rel = '*';
		}
		else
		{
			i = i + 1;
			temp3.rel = '+';
		}
		//justice
		//temp3
		if (check_true(a, temp3).compare("WRONG") != 0)
		{
			temp3.fieldType = check_true(a, temp3);
			temp2.push_back(temp3);
			temp3.compareMark = "";
			temp3.fieldName = "";
			temp3.fieldType = "";
			temp3.rel = "";
			temp3.value = "";
			temp3.left = 0;
			temp3.right = 0;
			continue;
		}
		else
		{
			temp1.flag = false;
			return temp1;
		}

	}
	temp1.shortStrings = temp2;
	temp1.flag = true;
	return temp1;
}
//返回筛选出满足要求的记录号
pair<vector<int>, bool> dealWith_Where(table &theTable, string where_command)//¥??ìwhere”??‰
{
	vector<int> a;
	pair<vector<int>, bool> b;
	string ss;
	djString dealStrings;
	string real_command;
	real_command = preWhere(where_command);
	//cout << real_command << endl;
	dealStrings = dealWith_Command(theTable, real_command);
	if (dealStrings.flag == false)
	{
		b.second = false;
		return b;
	}
	else
	{
		for (int i = 0; i < theTable.data.size(); i++)//逐行处理
		{
			for (int j = 0; j < dealStrings.shortStrings.size(); j++)
			{
				int num = 0;
				//map
				if (dealStrings.shortStrings[j].left == 1)
					ss += '(';
				for (int k = 0; k<theTable.field.size(); k++)
				{
					if (theTable.field[k].fieldName.compare(dealStrings.shortStrings[j].fieldName) == 0)
					{
						num = k;
						break;
					}
				}
				if (dealStrings.shortStrings[j].fieldType.compare("STRING") == 0)
				{
					if (dealStrings.shortStrings[j].compareMark.compare("=") == 0)
					{
						if (theTable.data[i].Data[num].compare(dealStrings.shortStrings[j].value) == 0)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}

					}
					if (dealStrings.shortStrings[j].compareMark.compare("!=") == 0)
					{
						if (theTable.data[i].Data[num].compare(dealStrings.shortStrings[j].value) != 0)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}

				}
				if (dealStrings.shortStrings[j].fieldType.compare("INT") == 0)
				{
					int x, y;
					x = atoi(theTable.data[i].Data[num].c_str());
					y = atoi(dealStrings.shortStrings[j].value.c_str());
					if (dealStrings.shortStrings[j].compareMark.compare("=") == 0)
					{
						if (x == y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}

					}
					if (dealStrings.shortStrings[j].compareMark.compare("!=") == 0)
					{
						if (x != y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}
					if (dealStrings.shortStrings[j].compareMark.compare("<") == 0)
					{
						if (x < y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}
					if (dealStrings.shortStrings[j].compareMark.compare(">") == 0)
					{
						if (x > y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}

				}
				if (dealStrings.shortStrings[j].fieldType.compare("DOUBLE") == 0)
				{
					double x, y;
					x = atof(theTable.data[i].Data[num].c_str());
					y = atof(dealStrings.shortStrings[j].value.c_str());
					if (dealStrings.shortStrings[j].compareMark.compare("=") == 0)
					{
						if (x == y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}

					}
					if (dealStrings.shortStrings[j].compareMark.compare("!=") == 0)
					{
						if (x != y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}
					if (dealStrings.shortStrings[j].compareMark.compare("<") == 0)
					{
						if (x < y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}
					if (dealStrings.shortStrings[j].compareMark.compare(">") == 0)
					{
						if (x > y)//ok
						{
							ss += '1';
						}
						else
						{
							ss += '0';
						}
					}

				}
				if (dealStrings.shortStrings[j].right == 1)
					ss += ')';
				if (j != dealStrings.shortStrings.size() - 1)
					ss += dealStrings.shortStrings[j].rel;

			}
			if (calculation(theTable, ss) < 0)
			{
				a.clear();
				b.second = false;
				return b;
			}
			if (calculation(theTable, ss) > 0)
			{
				a.push_back(i);
			}
			ss = "";
		}
	}
	b.first = a;
	b.second = true;
	return b;
}