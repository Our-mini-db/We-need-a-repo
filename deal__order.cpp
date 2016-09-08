#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
void deleteSpace(char *first,char *last) {
	if(*first==' '&&*(last-1)==' ')
	{
		first++;
		deleteSpace(first,last);
	}
		else if(!*first)
		{
			*last=0;
			return;
		}
			else
			{
				*last=*first;
				first++;
				last++;
				deleteSpace(first,last);
				return;
			}
}
bool deal_Order(char command[]) {
	pair<string, string> forSort;
	int commandLen = strlen(command);
	int commandNum = 0;
	int now=0;
	for (; now < commandLen; now++) {
		if (!commandNum) {
			while (command[now] != ' '&&now < commandLen)
				forSort.first += command[now++];
			commandNum = 1;
		}
		while (command[now] == ' '&&now < commandLen)
			now++;
		if(now==commandLen)
			return false;
		if (commandNum)
		{
			while (command[now] != ' '&&now < commandLen)
				forSort.second += command[now++];
			while (now < commandLen&&command[now] == ' ')
				now++;
			transform(forSort.first.begin(), forSort.first.end(), forSort.first.begin(), ::toupper);
			if (forSort.first!="TOP") {
				if (forSort.second != "ASC"&&forSort.second != "DESC")
					return false;
			}
				else if(now!=commandLen)
					return false;
			if (now == commandLen)
				break;
			now--;
			commandNum=0;
			forSort.first.clear();
			forSort.second.clear();
		}
	}
	deleteSpace(command,command);
	return true;
}
