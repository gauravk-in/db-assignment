#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <omp.h>
#include "include/hash_map.h"
#include <utility>
#include <unordered_map>
#include <vector>

#include "include/schema.h"
#include "include/storage.h"

typedef MyHashMap HashTable;

class mystring {
public:
	char str[50];

	mystring operator=(char *_str);
	mystring operator=(uint64_t val);
	int operator==(uint64_t val);
	int operator==(const char* _str);
	int operator==(mystring _mystr);
};

mystring mystring::operator=(char *_str) {
	strcpy(str, _str);
	return *this;
}

mystring mystring::operator=(uint64_t val) {
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

	HashTable hash_map_0;
	uint64_t max_count_item = item_vect[0].count;
	#pragma omp parallel for
	for(uint64_t i = 0; i < max_count_item; i++)
	{
		//hash_map_0 should be declared just above
		//generate hash table here
		hash_map_0.insert(item_vect[i].i_id, item_vect[i].tuple_id);
	}
	uint64_t max_count_orderline = orderline_vect[0].count;
	#pragma omp parallel for
	for(uint64_t i = 0; i < max_count_orderline; i++)
	{
		//Match with Hash Table here
		if(orderline_vect[i].ol_w_id==1)
		{
			item* item_iter=&item_vect.at(hash_map_0.find(orderline_vect[i].ol_i_id));
			mystring i_name;
			i_name = item_iter->i_name;
			mystring ol_o_id;
			ol_o_id = orderline_vect[i].ol_o_id;
			mystring ol_quantity;
			ol_quantity = orderline_vect[i].ol_quantity;
			mystring ol_amount;
			ol_amount = orderline_vect[i].ol_amount;
			printf("%s\t", i_name.str);
			printf("%s\t", ol_o_id.str);
			printf("%s\t", ol_quantity.str);
			printf("%s\t", ol_amount.str);
			printf("\n");
		}
	}
	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";
}
