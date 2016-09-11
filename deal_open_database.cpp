#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;
bool deal_open_data(char command[], int & length, string & database) {
	int len = strlen(command);
	int now=0;
	database.clear();
	for (; now < len&&command[now] != ' ' ;now++)
		database += command[now];
	while (now < len&&command[now] == ' ')
		now++;
	length = database.length();
	if (now != len)
		return false;
	return true;
}

