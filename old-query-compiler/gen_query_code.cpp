#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "include/schema.h"
#include "include/storage.h"

class mystring {
public:
	char* str;

	mystring operator=(char *_str);
	mystring operator=(uint64_t val);
	int operator==(uint64_t val);
	int operator==(const char* _str);
	int operator==(mystring _mystr);
};

mystring mystring::operator=(char *_str) {
	str = (char*)malloc(sizeof(char)*strlen(_str));
	strcpy(str, _str);
	return *this;
}

mystring mystring::operator=(uint64_t val) {
	str = (char*)malloc(sizeof(char)*20);
	sprintf(str, "%llu", val);
	return *this;
}

int mystring::operator==(uint64_t val) {
	char temp_str[20];
	sprintf(temp_str, "%llu", val);
	return !strcmp(str, temp_str);
}

int mystring::operator==(const char* _str) {
	return !strcmp(str, _str);
}

int mystring::operator==(mystring _mystr) {
	return !strcmp(str, _mystr.str);
}

void query2() {
	for(vector<warehouse>::iterator hJ_0_iter=warehouse_vect.begin(); hJ_0_iter<warehouse_vect.end(); hJ_0_iter++)
	{
		mystring w_name;
		w_name = hJ_0_iter->w_name;
		mystring w_id;
		w_id = hJ_0_iter->w_id;
		for(vector<district>::iterator hJ_1_iter=district_vect.begin(); hJ_1_iter<district_vect.end(); hJ_1_iter++)
		{
			mystring d_name;
			d_name = hJ_1_iter->d_name;
			mystring d_w_id;
			d_w_id = hJ_1_iter->d_w_id;
			mystring d_tax;
			d_tax = hJ_1_iter->d_tax;
			if(w_id == d_w_id && w_id == 1)
			{
				printf("%s\t", w_name.str);
				printf("%s\t", d_name.str);
				printf("%s\t", d_tax.str);
				printf("\n");
			}
		}
	}
}
