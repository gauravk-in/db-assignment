#include "hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>

#include <ctime>
#include <sys/time.h>

using namespace std;

int main() 
{
	MyHashMap map;
	timeval start_time, end_time, time_taken;

	gettimeofday(&start_time,NULL);

	for(long int i=0;i<100000;i++)
	{
		map.insert(rand(), rand());
	}

	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";

	unordered_map<uint64_t, uint64_t> hash_map;

	gettimeofday(&start_time,NULL);

	for(long int i=0;i<100000;i++)
	{
		hash_map.insert(make_pair(rand(), rand()));
	}

	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";

	return 0;
}