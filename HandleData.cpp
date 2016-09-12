#include "HandleData.h"
#include "Deal_With_Where.h"
void insertData(string databaseName, string tableName, vector<pairData> _dataPair)
{

	table a = openTable(databaseName,tableName);
	rowData newRow;
	int vis[10];
	memset(vis, 0, sizeof(vis));
	newRow.rowNum = (int)a.data.size() + 1;
	//Ê±ÇÂä†map
	for (int i = 0; i<_dataPair.size(); i++)
	{
		int colNum = a.fieldmap[_dataPair[i].fieldName];
		//field_num[_dataPair[i].fieldName];//Á°ÆÂÆöËØ•Â≠óÊÆµÊâÄÂØπÂ∫îÁöÑÂàóÂè?
		vis[i] = 1;//Ê†áËÆ∞ËØ•ÂàóÊèíÂÖ•Êï∞ÊçÆ
		newRow.Data[colNum] = _dataPair[i].data;//Âú®Êñ∞Âª∫ÁöÑË°å‰∏≠ËØ•Âàó‰ΩçÁΩÆÊèíÂÖ•Êï∞ÊçÆ
	}
	for (int i = 0; i<a.field.size(); i++)
	{
		if (vis[i] == 0)
		{
			newRow.Data[i] = "ø’";
		}
	}//‰ª•‰∏äÂàõÂª∫Êñ∞Ë°å
	a.data.push_back(newRow);//Âú®ËØ•Ë°®Ê†º‰∏≠ÊèíÂÖ•Êñ∞Ë°?
	saveTable(databaseName,a);
}
void updateData(string databaseName, string tableName, vector<pairData> updata_data, string where_command)
{
	
	table a = openTable(databaseName,tableName);
	//Ê±ÇÂä†map
	pair<vector<int>, bool> rowNum;
	rowNum = dealWith_Where(a, where_command);//ËøîÂõûÂê´ÊúâË°åÂè∑ÁöÑvector
	if (rowNum.second == false)
	{
		cout << "格式错误" << endl;
		//接下来显示正确格式提示
	}
	else
	{
		if (rowNum.first.size() == 0)
		{
			cout << "未查找到满足条件数据" << endl;
		}
		else
		{
			for (int i = 0; i<rowNum.first.size(); i++)//Êõ¥Êñ∞ÊØè‰∏ÄÁ¨¶ÂêàÊù°‰ª∂Ë°?
			{
				for (int j = 0; j<updata_data.size(); j++)
				{
					int colNum = a.fieldmap[updata_data[j].fieldName];
					a.data[rowNum.first[i]].Data[colNum] = updata_data[j].data;
				}
			}
			cout << "更新成功" << endl;
			saveTable(databaseName,a);

		}
	}

}
void deleteData(string databaseName, string tableName, string where_command)
{
	table a = openTable(databaseName,tableName);
	pair<vector<int>, bool> rowNum;
	rowNum = dealWith_Where(a, where_command);
	//ËøôÈáåÈúÄË¶ÅÊ∑ªÂä†vector‰ªéÂ§ßÂà∞Â∞èÊéíÂ∫è-time
	if (rowNum.second == false)
	{
		cout << "格式错误" << endl;
		//接下来显示正确格式提示
	}
	else
	{
		if (rowNum.first.size() == 0)
		{
			cout << "未查找到满足条件数据" << endl;
		}
		else
		{
			for (int i = 0; i < rowNum.first.size(); i++)
			{
				int len = (int)a.data.size();
				int k = -1;
				for (int j = 0; j < len; j++)
				{
					if (a.data[j].rowNum == rowNum.first[i])
					{
						k = j;
						break;
					}
				}
				vector<rowData>::iterator it = a.data.begin() + k;
				a.data.erase(it);
			}
			cout << "删除成功" << endl;
			saveTable(databaseName,a);


		}
	}

}