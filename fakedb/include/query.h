#ifndef _QUERY_H_
#define _QUERY_H_

#include <vector>

using namespace std;

// details of fields in the projection
class proj_field {
public:	
	char name[20];
	char table_name[20];
};

//details of tables in the projection
class proj_table {
public:
	char table_name[20];
};

//details of the conditions to be checked for the projection
class proj_cond {
public:
	char cond_str[50];
};

class select_query {
public:
	vector<proj_field> field_list;
	vector<proj_table> table_list;
	vector<proj_cond> cond_list;

	int push_field();
	int push_table();
	int push_cond();
};

void run_query();

#endif // _QUERY_H_