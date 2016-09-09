#ifndef CHK_SD_CMD_H
#define CHK_SD_CMD_H
#include "main.h"
#include "Command.h"

bool deal_select_data(char command[], int & length, string & table_name,
	string & where_command, string & order_command, vector<string> & field_name);

#endif