#ifndef _DB_STRUCTS_H_
#define _DB_STRUCTS_H_

#include <stdio.h>
#include <list>

using namespace std;

#define NAME_MAX 20

class field_t {
public:
	char field_name[NAME_MAX];
	char field_type[NAME_MAX];
	int field_size;
	int primary_key;

/*
	field_t() {
		field_name="";
		field_type="";
		field_size=-1;
		primary_key=0;
	}
*/
};

class table_t {
public:
	char table_name[NAME_MAX];
	list<field_t> field_list;
	list<field_t> pkeys_list;

/*
	table_t() {
		table_name="";
	}
*/
};

extern list<table_t> table_list;

class index_t {
public:
	char index_name[NAME_MAX];
	table_t *on_table;
	list<field_t> on_field_list;
/*
	index_t() {
		index_name="";
	}
*/
};

extern list<index_t> index_list;

#endif //_DB_STRUCTS_H_