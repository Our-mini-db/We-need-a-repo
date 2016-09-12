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
	printf("�����ǰ���ҳ�棬���Ķ�˵���˽���ع���\n");
	printf("���������ֽ��в�ѯ:\n");
	printf("0.�˳�HELP\t1.�������ݿ�\t2.������\t3.����ֶ�\t4.�����¼\t5.��ѯ��¼\t6.���¼�¼\t7.ɾ����¼\t8.ɾ���ֶ�\t9.ɾ����\t10�����ݿ�\t11.ɾ�����ݿ�\n");
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
