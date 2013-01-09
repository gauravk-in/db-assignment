#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <omp.h>
#include <task_scheduler_init.h>
#include <blocked_range.h>
#include <parallel_for.h>
#include <concurrent_hash_map.h>

#include <utility>
#include <unordered_map>
#include <vector>

#include "include/schema.h"
#include "include/storage.h"

using namespace tbb;

// Structure that defines hashing and comparison operations for user's type.
struct MyHashCompare {
    static uint64_t hash( const uint64_t x ) {
        uint64_t h = 5892;
        h = ((h<<5) + h) * x;
        return h;
    }
//! True if strings are equal
    static bool equal( const uint64_t x, const uint64_t y ) {
        return x==y;
    }
};
typedef concurrent_hash_map<uint64_t,uint64_t,MyHashCompare> HashTable;
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
	task_scheduler_init init;
	timeval start_time, end_time, time_taken;

	gettimeofday(&start_time,NULL);

	HashTable hash_map_0;
	HashTable::accessor hash_map_0_acc;
	uint64_t max_count_district = district_vect[0].count;
	#pragma omp parallel for
	for(uint64_t i = 0; i < max_count_district; i++)
	{
		//hash_map_0 should be declared just above
		//generate hash table here
		hash_map_0.insert(make_pair(district_vect[i].d_id, district_vect[i].tuple_id));
	}
	uint64_t max_count_customer = customer_vect[0].count;
	#pragma omp parallel for
	for(uint64_t i = 0; i < max_count_customer; i++)
	{
		//Match with Hash Table here
		if(customer_vect[i].c_w_id==1)
		{
			hash_map_0.find(hash_map_0_acc, customer_vect[i].c_d_id);
			district* district_iter=&district_vect.at(hash_map_0_acc->second);
			mystring d_name;
			d_name = district_iter->d_name;
			mystring c_first;
			c_first = customer_vect[i].c_first;
			mystring c_last;
			c_last = customer_vect[i].c_last;
			mystring c_id;
			c_id = customer_vect[i].c_id;
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
