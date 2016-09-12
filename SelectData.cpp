#include "SelectData.h"
#include "Deal_With_Where.h"
vector<Priority> priority;
bool cmp(rowData a, rowData b)
{
	int len = priority.size();
	for (int i = 0; i < len; i++)
	{
		if (priority[i].judgeUpOrDown)
		{
			if (priority[i].theDataType == INT)
			{
				return atoi(a.Data[priority[i].columnnum].c_str()) < atoi(b.Data[priority[i].columnnum].c_str());
			}
			else if (priority[i].theDataType == DOUBLE)
			{
				return atof(a.Data[priority[i].columnnum].c_str()) < atof(b.Data[priority[i].columnnum].c_str());
			}
			else if (priority[i].theDataType == STRING || priority[i].theDataType == DATE)
			{
				return a.Data[priority[i].columnnum] < b.Data[priority[i].columnnum];
			}
		}
		else
		{
			if (priority[i].theDataType == INT)
			{
				return atoi(a.Data[priority[i].columnnum].c_str()) > atoi(b.Data[priority[i].columnnum].c_str());
			}
			else if (priority[i].theDataType == DOUBLE)
			{
				return atof(a.Data[priority[i].columnnum].c_str()) > atof(b.Data[priority[i].columnnum].c_str());
			}
			else if (priority[i].theDataType == STRING || priority[i].theDataType == DATE)
			{
				return a.Data[priority[i].columnnum] > b.Data[priority[i].columnnum];
			}
		}
	}
	return false;
}
void selectData(string databaseName,string tableName, string where_command, string order_command, vector<string>field_name)
{
	table Thetable = openTable(databaseName, tableName);
	pair<vector<int>, bool> aPair = dealWith_Where(Thetable, where_command);
	if (aPair.second == false)
	{
		cout << "格式错误" << endl;
		return;
	}
	vector<int> selectNumber = aPair.first;
	int top = -100;
	table finalTable = orderBy(Thetable, selectNumber, order_command,top);
	if (top == -2)return;
	vector<int> field_colunm;
	for each (string var in field_name)
	{
		if (Thetable.fieldmap.count(var) == 0)
		{
			cout << "不存在字段" + var << endl;
			return;
		}
		else
		{
			field_colunm.push_back(Thetable.fieldmap[var]);
		}
	}
	for each (int var in field_colunm)
	{
		cout << Thetable.field[var].fieldName + "\t";
	}
	cout << endl;
	if (top != -1)
	{
		for (int i = 0; i < top&&i < finalTable.data.size(); i++)
		{
			for each (int var in field_colunm)
			{
				cout << finalTable.data[i].Data[var] + "\t";
			}
			cout << endl;
		}
	}
	else
	{
		for (int i = 0; i < finalTable.data.size(); i++)
		{
			for each (int var in field_colunm)
			{
				cout << finalTable.data[i].Data[var] + "\t";
			}
			cout << endl;
		}
	}
}
table orderBy(table &Thetable, vector<int>  selectNumber,string orderby_command,int &top)
{
	table finaltable;
	for each (int c in selectNumber)
	{
		finaltable.data.push_back(Thetable.data[c]);
	}
	priority.clear();
	//处理priority
	top = dealWith_priority(Thetable, priority, orderby_command);
	//
	if (top == -2)return finaltable;
	sort(finaltable.data.begin(), finaltable.data.end(), cmp);
	return finaltable;
}
int dealWith_priority(table &theTable, vector<Priority> &priority, string orderby_command)
{
	int sp = orderby_command.find("top");
	string order = orderby_command.substr(0, sp);
	string topCommand = orderby_command.substr(sp + 3, orderby_command.size() - sp);
	int orderlen = order.size();
	int first = 0;
	while (order[first] == ' ')first++;
	for (int last = 0; last < orderlen; last++)
	{
		if (order[last] == ' ')
		{
			string order1 = order.substr(first, last - first);
			if (order1 != "ASC"&&order1 != "DESC")
			{
				Priority temp;
				if (theTable.fieldmap.count(order1) == 0)
				{
					cout << "没找到字段" << endl;
					return -2;
				}
				else
				{
					temp.columnnum = theTable.fieldmap[order1];
					temp.theDataType = theTable.field[temp.columnnum].theType;
					temp.judgeUpOrDown = true;
					priority.push_back(temp);
				}
			}
			else
			{
				if (order1 == "ASC")
				{
					priority.back().judgeUpOrDown = true;
				}
				else
				{
					priority.back().judgeUpOrDown = false;
				}
			}
			while (last < orderlen&&order[last] == ' ')last++;
			first = last;
		}
	}
	if (sp == -1)return -1;
	else
	{
		int a = atoi(topCommand.c_str());
		return a;
	}
}