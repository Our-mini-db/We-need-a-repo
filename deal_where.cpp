#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;
struct part
{
	string listName;//�ֶ�����
	string mark;//and or
	string constant;//���� �ֶ�ֵ
	string judge;//���ַ���
};
bool judgeJudge(string judge) {
	if (judge == "=" || judge == ">" || judge == "<" || judge == "!=" || judge == ">=" || judge == "<=")
		return true;
	return false;
}
bool judgeMark(string mark)
{
	if (mark == "AND" || mark == "OR")
		return true;
	else
		return false;
}
bool deal_where(char command[])//����where��䲻���ϸ�ʽ 
{
	int commandLen = strlen(command);
	int first, last,commandNum;
	part content;
//	memset(&content, 0, sizeof(content));
	//bool withMarks=false;//˫���ŵı�ʶ��
	first = last = commandNum=0;
	for (; last<commandLen;last++) {
		if (commandNum ==0 && command[last] != ' '&&command[last] != '!'&&command[last]!='>'&&command[last] != '<'&&command[last]!='=')//get the name
			content.listName+=command[last];
		else if (commandNum == 0)
		{
			while(command[last]==' '&&last<commandLen)
				last++;
			if(last>=commandLen)
				return false;
			if (command[last] != ' ') //consider the string judge
				commandNum = 1;
		}
		if (commandNum == 1 && command[last] != ' '&&command[last]!='"')//consider judge
			content.judge += command[last];
		else if (commandNum == 1) {
			if (command[last] != ' '&&command[last] != '"')//not space or double marks
				return false;
			else if (command[last] == ' ')//deal with space
			{
				while (last < commandLen&&command[last] == ' ')
					last++;
				if (command[last] != '"'||last>=commandLen)
					return false;
			}
			if(commandNum==1&&command[last]=='"')//deal with the first "
			{
				commandNum = 2;
				last++;
				if (last >= commandLen)
					return false;
			}
		}
		if (commandNum == 2 && command[last] != '"'&&command[last]!='\\')//�Ѿ��������һ��˫����
			content.constant += command[last];
		else if (command[last] == '\\')//����ת���ַ����д���
		{
			last++;
			if (last >= commandLen)
				return false;
			content.constant += command[last];
		}
		else if (command[last]=='"')
		{
			commandNum = 3;
			last++;
		}
		if(commandNum==3&&last<commandLen){
			while (command[last] == ' '&&last<commandLen)
				last++;
			if (last >= commandLen)
				return false;
			while (last < commandLen&&command[last] != ' ')
				content.mark += command[last++];
			if(last>=commandLen)
				return false;
			if (judgeJudge(content.judge) && judgeMark(content.mark))
			{
				content.listName.clear();
				content.judge.clear();
				content.constant.clear();
				content.mark.clear();
				commandNum = 0;
				while (command[last] == ' '&&last < commandLen)
					last++;
				last--;
			}
			else
				return false;
		}
	}
	return judgeJudge(content.judge) && !content.mark.length();
}
