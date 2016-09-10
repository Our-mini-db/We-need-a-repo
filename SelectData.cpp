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
void selectData(string tableName, string where_command, string order_command, vector<string>field_name)
{
	table Thetable = openTable(tableName);
	vector<int> selectNumber = dealWith_Where(Thetable, where_command);

	table finalTable = orderBy(Thetable, selectNumber, order_command);
	/*if (top != -1)
	{
		for (int i = 0; i < top&&i < finalTable.data.size(); i++)
		{
			printf("");
		}
	}
	else
	{
		for (int i = 0; i < finalTable.data.size(); i++)
		{
			printf("");
		}
	}*/
}
table orderBy(table &Thetable, vector<int>  selectNumber,string orderby_command)
{
	table finaltable;
	for each (int c in selectNumber)
	{
		finaltable.data.push_back(Thetable.data[c]);
	}
	priority.clear();
	//处理priority
	dealWith_priority(Thetable ,priority, orderby_command);
	//
	sort(finaltable.data.begin(), finaltable.data.end(), cmp);
	return finaltable;
}
Priority getPriority(table &theTable,string order[])
{
	Priority addOne;
	if (theTable.fieldmap.count(order[0]) == 0)
	{

	}
	else
	{
		addOne.columnnum = theTable.fieldmap[order[0]];
		addOne.theDataType = theTable.field[addOne.columnnum].theType;
		addOne.judgeUpOrDown = true;
		if (order[1] == "DESC")
			addOne.judgeUpOrDown = false;
		return addOne;
	}
}
void dealWith_priority(table &theTable,vector<Priority> &priority, string orderby_command)//ÏÖÔÚorderby_commandÖ¸µÄÊÇorderbyºóÃæµÄÄÚÈÝ,×îºóµÄ·ÖºÅÒ²ÒªÈ¥µô
{
	string order[2];
	int len = orderby_command.length();
	int first, last, orderID = 0;
	first = last = 0;
	while (orderby_command[first] == ' ')
		first++;
	for (last = first; last < len; last++)
	{
		if (orderby_command[last] != ' ')
			continue;
		orderID %= 2;
		order[orderID] = orderby_command.substr(first, last - first);
		first = last;
		if (orderID == 1 && (order[1] == "ASC" || order[1] == "DESC"))
		{
			priority.push_back(getPriority(theTable, order));
			memset(order, 0, sizeof(order));
		}
		else if (orderID == 1)
		{
			priority.push_back(getPriority(theTable, order));
			order[0] = order[1];
			order[1].clear();
		}
		orderID++;
	}
	order[orderID] = orderby_command.substr(first, last - first);
	priority.push_back(getPriority(theTable, order));
	return;
}