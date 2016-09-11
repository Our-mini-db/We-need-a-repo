#ifndef CHK_Table_CMD_H
#define CHK_Table_CMD_H
#include "main.h"

bool deal_create_data(char command[], int & length, string & table_name, vector<fieldType> &field,int & flag);

bool deal_add_data(char command[], int &length, string & table_name, fieldType & my_field);

bool deal_cancel_data(char command[], int &length, string & table_name, vector<string> & field_name);



bool deal_open_data(char command[], int & length, string & database);

#endif