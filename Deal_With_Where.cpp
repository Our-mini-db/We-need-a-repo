#include "Deal_With_Where.h"
int step_1(char x)
{
	if (x == '+')
		return 1;
	if (x == '*')
		return 2;
	else
		return 0;
}
int find_ans(int x, char y, int z)
{
	if (y == '+')
		return x + z;
	if (y == '*')
		return x*z;
	else
		return 0;
}
//ä¸­ç¼€è½¬åŽç¼€è®¡ç®—æ˜¯å¦ä¸ºåˆæ³•è®°å½•
int calculation(string ss)
{
	int i, len, type;
	stack <int > numm;
	stack<char> s;
	type = 0;         //type ä¸º0çš„æ—¶å€™è¾“å…¥æ•°å­—ï¼Œä¸º1çš„æ—¶å€™è¾“å…¥è¿ç®—ç¬¦//
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

		if ((ss[i] <= '9') && (ss[i] >= '0'))//å¦‚æžœæ˜¯æ•°å­—çš„è¯
		{
			int fu;
			fu = 0;
			if (i>1)
			{
				if ((ss[i - 1] == '-') && ((ss[i - 2]>'9') || (ss[i - 2]<'0')))//åˆ¤æ–­æ˜¯å¦ä¸ºè´Ÿæ•°ï¼ˆæ²¡æœ‰è€ƒè™‘é¦–ä½ä¸ºè´Ÿï¼‰
					fu = 1;
			}
			if (i == 1)
			{
				if (ss[i - 1] == '-')
					fu = 1;//è€ƒè™‘é¦–ä½
			}
			if (type == 0)
				type = (type ^ 1);
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
			numm.push(num1);//æ”¾å…¥æ ˆ
		}
		else
		{
			int cal1, cal2;
			cal1 = step_1(ss[i]);
			if (type == 0 && ss[i] == '-')
				continue;
			else if (type == 1)
				type = (type ^ 1);
			while (!s.empty())
			{
				cal2 = step_1(s.top());
				if (((cal2<cal1) && (cal1 != 5)) || ((cal1 == cal2) && (cal1 == 3)))
				{
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
	return numm.top();
}
//å‡ºé”™å¤„ç†
string check_true(table a, shortString b)
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
//åˆ†è§£æˆå°å¥å­
djString dealWith_Command(table a, string command)
{
	djString temp1;
	vector<shortString> temp2;
	shortString temp3;
	int flag1, i, j;
	int len = (int)command.length() - 1;//;
	for (i = 0; i <= len; i++)
	{
		flag1 = i;
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
		for (j = flag1; j<i; j++)
		{
			temp3.value += command[j];
		}
		if (i == len)
			temp3.value += command[i];
		//4
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
		//temp3    *
		if (check_true(a, temp3).compare("WRONG") != 0)
		{
			temp3.fieldType = check_true(a, temp3);
			temp2.push_back(temp3);
			temp3.compareMark = "";
			temp3.fieldName = "";
			temp3.fieldType = "";
			temp3.rel = "";
			temp3.value = "";
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
//è¿”å›žç­›é€‰å‡ºæ»¡è¶³è¦æ±‚çš„è®°å½•å·
vector<int> dealWith_Where(table theTable, string where_command)//Â¥??Ã¬whereâ€??â€°
{
	vector<int> a;
	string ss;
	string rel_command = preWhere(where_command);
	djString dealStrings;
	dealStrings = dealWith_Command(theTable, rel_command);
	if (dealStrings.flag == false)
	{
		a.push_back((int)theTable.data.size());//æ”¾å…¥ä¸å¯èƒ½æ•°å­—åšé”™è¯¯å¤„ç†
	}
	else
	{
		for (int i = 0; i < theTable.data.size(); i++)//é€è¡Œå¤„ç†
		{
			for (int j = 0; j < dealStrings.shortStrings.size(); j++)
			{
				int num = 0;
				//map
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
				if (j != dealStrings.shortStrings.size() - 1)
					ss += dealStrings.shortStrings[j].rel;

			}
			if (calculation(ss) > 0)
				a.push_back(i);
			ss = "";
		}
	}
	return a;
}
string preWhere(string ss)
{
	int i, flag1, flag2;
	flag1 = flag2 = 0;
	cout << ss << endl;
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