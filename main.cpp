#pragma warning(disable:4996)
#include "main.h"
#include "HandleData.h"
#include "HandleTable.h"
#include "SelectData.h"
#include "Chk_Dat_Cmd.h"
#include "Chk_SD_Cmd.h"
#include "Chk_Table_Cmd.h"
#include "Command.h"
int name_length = 20;
table openTable(string tableName)//打开磁盘中的表
{
	table answerTable;
	answerTable.name = tableName;
	string tempStr = tableName + ".wow";
	FILE *file = fopen(tempStr.c_str(), "r");
	char temp[26000];
	while (fscanf(file, "%s", temp) != EOF)
	{
		int len = strlen(temp);
		char str1[26000];
		char str2[26000];
		int flag = 0;
		int j = 0;
		for (int i = 0; i < len; i++)
		{
			if (temp[i] == '#')
			{
				bool tempflag = true;
				for (int j = i; j < len&&j < i + 4; j++)
				{
					if (temp[j] != '#')
					{
						tempflag = false;
						break;
					}
				}
				if (tempflag)break;
			}
			if (flag == 0)
			{
				if (temp[i] != ':')
				{
					str1[i] = temp[i];
				}
				else
				{
					str1[i] = '\0';
					flag = 1;
				}
			}
			else
			{
				str2[j++] = temp[i];
			}
		}
		str2[j] = '\0';
		int Num = atoi(str2);
		if (strcmp(str1, "field") == 0)
		{
			for (int n = 0; n < Num; n++)
			{
				fieldType tempField;
				fscanf(file, "%s", temp);
				len = strlen(temp);
				int tempflag = 0;
				char temp1[256], temp2[256], temp3[256];
				for (int i = 0, j = 0, k = 0; i < len; i++)
				{
					if (tempflag == 0)
					{
						if (temp[i] == '|'&&temp[i + 1] == '|')
						{
							temp1[i] = '\0';
							tempflag++;
							i++;
							continue;
						}
						temp1[i] = temp[i];
					}
					else if (tempflag == 1)
					{
						if (temp[i] == '|'&&temp[i + 1] == '|')
						{
							temp2[j] = '\0';
							tempflag++;
							i++;
							continue;
						}
						temp2[j++] = temp[i];
					}
					else if (tempflag == 2)
					{
						if (temp[i] == '|'&&temp[i + 1] == '|')
						{
							temp3[k] = '\0';
							tempflag++;
							i++;
							continue;
						}
						temp3[k++] = temp[i];
					}
					else break;
				}
				string tempName(temp1);
				tempField.fieldName = tempName;
				tempField.limitation = atoi(temp3);
				if (strcmp(temp2, "INT") == 0)tempField.theType = INT;
				else if (strcmp(temp2, "STRING") == 0)tempField.theType = STRING;
				else if (strcmp(temp2, "DOUBLE") == 0)tempField.theType = DOUBLE;
				else if (strcmp(temp2, "DATE") == 0)tempField.theType = DATE;
				tempField.fieldNum = answerTable.field.size();
				answerTable.fieldmap.insert(pair<string, int>(tempField.fieldName, tempField.fieldNum));
				answerTable.field.push_back(tempField);
			}
		}
		else if (strcmp(str1, "data") == 0)
		{
			for (int n = 0; n < Num; n++)
			{
				fscanf(file, "%s", temp);
				int len = strlen(temp);
				rowData tempRowData;
				char str[260];
				int p = 0;
				int Datap = 0;
				for (int i = 0; i < len; i++)
				{
					if (temp[i] == '|'&&temp[i + 1] == '|')
					{
						str[p] = '\0';
						string tempStr(str);
						tempRowData.Data[Datap++] = tempStr;
						p = 0;
						i++;
						continue;
					}
					str[p++] = temp[i];
				}
				tempRowData.rowNum = answerTable.data.size();
				answerTable.data.push_back(tempRowData);
			}
		}
	}
	fclose(file);
	return answerTable;
}
void saveTable(table _theSavingTable)//保存磁盘中的表
{
	string tempStr = _theSavingTable.name + ".wow";
	FILE *file = fopen(tempStr.c_str(), "w");
	fprintf(file, "field:%d####\n", _theSavingTable.field.size());
	for each (fieldType var in _theSavingTable.field)
	{
		fprintf(file, "%s||", var.fieldName.c_str());
		switch (var.theType)
		{
		case INT:{
			fprintf(file, "INT||");
			break;
		}
		case STRING:{
			fprintf(file, "STRING||");
			break;
		}
		case DOUBLE:{
			fprintf(file, "DOUBLE||");
			break;
		}
		case DATE:{
			fprintf(file, "DATE||");
			break;
		}
		default:
			break;
		}
		switch (var.limitation)
		{
		case 1:{
			fprintf(file, "01||###\n");
			break;
		}
		case 0:{
			fprintf(file, "00||###\n");
			break;
		}
		case 11:{
			fprintf(file, "11||###\n");
			break;
		}
		default:
			break;
		}
	}
	fprintf(file, "data:%d####\n", _theSavingTable.data.size());
	for each (rowData var in _theSavingTable.data)
	{
		int len = _theSavingTable.field.size();
		for (int i = 0; i < len; i++)
		{
			fprintf(file, "%s||", var.Data[i].c_str());
		}
		fprintf(file, "###\n");
	}
	fclose(file);
}
int main()
{
	char ch = 0;
	char* command = new char[name_length];

    int bitnum = 0;
	string database = "";
	int flag = 0;
	while ((ch = getchar()) != EOF)//°¤¸ö×Ö·û½øÐÐ´¦Àí
	{
		if (ch == ';')//Èç¹û¶Áµ½ ; ±íÊ¾ÊäÈëÒ»ÌõÃüÁî   Ö§²»Ö§³Ö ·ÖºÅµÄÊäÈë
		{
			int cmd = -1;
			command[bitnum] = '\0';	//¸Õ²ÅÊäÈëµÄÖ¸Áî(½ö½«»Ø³µ³Ôµô)

			int check = deal_with_command(command, bitnum, flag, database);	//处理这条命令
			if (check == -1)
			{
				printf("Please open a database or CREATE a database!\n");
			}

			bitnum = 0;

			//ÖØÐÂ·ÖÅäcommandµÄÄÚ´æ´óÐ¡
			delete command;
			name_length = name_length_bak;
			command = new char[name_length];
		}
		else
		{
			if (bitnum == name_length - 2)//µ±×Ö·û´®³¤¶È²»¹»Ê±ÖØÐÂ·ÖÅä
			{
				command = add_char_size(command);
			}
			if (ch == '\n')	ch = ' ';
			command[bitnum++] = ch;
			command[bitnum] = '\0';
		}
	}
	delete command;
	return 0;
}