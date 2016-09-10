#ifndef CHK_DAT_CMD_H
#define CHK_DAT_CMD_H
#include "main.h"
#include "Command.h"

bool deal_update_data(char command[], int & length, string & table_name,
	vector<pairData> & updata_data, string & where_command);
bool deal_delete_data(char command[], int & length, string & table_name, string & where_command);

bool deal_insert_data(char command[], int & length, string & table_name, vector<pairData>& my_data);

bool deal_drop_data(char command[], int & length, string & table_name);



#endif