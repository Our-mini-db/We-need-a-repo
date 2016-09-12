#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
void outHelp(string FileName) {	
//	FILE *fp;
//	const char *const str = FileName.c_str();
//	fp = fopen(str, "r");
//	string forHelp ;
//	cin.getline(forHelp.c_str(),200);
//	while (forHelp!=""){
//		cout << forHelp <<endl;
//		forHelp = cin.getline();
//	}
//	fclose(fp);
	FILE *fp;
	const char *const str = FileName.c_str();
	if((fp = fopen(str, "r"))==NULL){
		printf("This command doesn't exist!");
		return;
	}
	char  out;
	while ((out = fgetc(fp)) != EOF)
		printf("%c", out);
	fclose(fp);
//	fcloseall();
}
void out_Help()
{
	int commandID;
	printf("这里是帮助页面，请阅读说明了解相关功能\n");
	printf("请输入数字进行查询:\n");
	printf("0.退出HELP\t1.创建数据库\t2.创建表单\t3.添加字段\t4.插入记录\t5.查询记录\t6.更新记录\t7.删除记录\t8.删除字段\t9.删除表单\t10打开数据库\t11.删除数据库\n");
	scanf("%d", &commandID);
	while (commandID)
	{
		stringstream toStr;
		string fileName;
		toStr << commandID;
		toStr >> fileName;
		fileName += ".txt";
		outHelp(fileName);
		printf("\n");
		scanf("%d", &commandID);
	}
}
