#include "HandleData.h"
#include "Deal_With_Where.h"
void insertData(string tableName, vector<pairData> _dataPair)
{
	
	table a = openTable(tableName);
	rowData newRow;
	int vis[10];
	memset(vis, 0, sizeof(vis));
	newRow.rowNum = (int)a.data.size() + 1;
	//求加map
	for (int i = 0; i<_dataPair.size(); i++)
	{
		if (a.fieldmap.count(_dataPair[i].fieldName) == 0)
		{

		}
		else
		{
			int colNum = a.fieldmap[_dataPair[i].fieldName];
			//field_num[_dataPair[i].fieldName];//确定该字段所对应的列�?
			vis[i] = 1;//标记该列插入数据
			newRow.Data[colNum] = _dataPair[i].data;//在新建的行中该列位置插入数据
		}
	}
	for (int i = 0; i<a.field.size(); i++)
	{
		if (vis[i] == 0)
		{
			newRow.Data[i] = "��";
		}
	}//以上创建新行
	a.data.push_back(newRow);//在该表格中插入新�?
	saveTable(a);
}
void updateData(string tableName, vector<pairData> updata_data, string where_command)
{
	openTable(tableName);
	table a;
	//求加map
	vector<int> rowNum;
	rowNum = dealWith_Where(a, where_command);//返回含有行号的vector
	for (int i = 0; i<rowNum.size(); i++)//更新每一符合条件�?
	{
		for (int j = 0; j<updata_data.size(); j++)
		{
			int colNum = a.fieldmap[updata_data[j].fieldName];
			a.data[i].Data[colNum] = updata_data[j].data;
		}
	}
	saveTable(a);
}
void deleteData(string tableName, string where_command)
{
	table a = openTable(tableName);
	vector<int> rowNum;
	rowNum = dealWith_Where(a, where_command);
	//这里需要添加vector从大到小排序-time
	for (int i = 0; i < rowNum.size(); i++)
	{
		int len = a.data.size();
		int k = -1;
		for (int j = 0; j < len; j++)
		{
			if (a.data[j].rowNum == rowNum[i])
			{
				k = j;
				break;
			}
		}
		vector<rowData>::iterator it = a.data.begin() + k;
		a.data.erase(it);
		/*for (int j = rowNum[i]; j < a.data.size(); j++)
		{
			if (j == a.data.size() - 1)
			{
				a.data.pop_back();
				continue;
			}
			a.data[j] = a.data[j + 1];
		}*/
	}
	saveTable(a);
}