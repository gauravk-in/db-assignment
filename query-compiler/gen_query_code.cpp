#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <utility>
#include <unordered_map>
#include <vector>

#include "include/schema.h"
#include "include/storage.h"

class mystring {
public:
	char* str = NULL;

	~mystring() {
	if(str!=NULL)
		free(str);
	}
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
	timeval start_time, end_time, time_taken;

	gettimeofday(&start_time,NULL);

	unordered_map<uint64_t, uint64_t> hash_map_0;
	for(vector<district>::iterator district_iter=district_vect.begin(); district_iter!=district_vect.end(); district_iter++)
	{
		//hash_map_0 should be declared just above
		//generate hash table here
		hash_map_0.insert(make_pair(district_iter->d_id, district_iter->tuple_id));
	}
	for(vector<customer>::iterator customer_iter=customer_vect.begin(); customer_iter!=customer_vect.end(); customer_iter++)
	{
		//Match with Hash Table here
		if(customer_iter->c_w_id==1)
		{
			district* district_iter=&district_vect.at(hash_map_0.at(customer_iter->c_d_id));
			mystring d_name;
			d_name = district_iter->d_name;
			mystring c_first;
			c_first = customer_iter->c_first;
			mystring c_last;
			c_last = customer_iter->c_last;
			mystring c_id;
			c_id = customer_iter->c_id;
			printf("%s\t", d_name.str);
			printf("%s\t", c_first.str);
			printf("%s\t", c_last.str);
			printf("%s\t", c_id.str);
			printf("\n");
		}
	}
	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";
}
