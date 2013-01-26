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

	for(long int i=0;i<1000000;i++)
	{
		map.insert(rand(), rand());
	}

	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;
	if(time_taken.tv_usec < 0)
	{
		time_taken.tv_sec--;
		time_taken.tv_usec = 1000000+time_taken.tv_usec;
	}
	printf("MyHashMap::insert()\n");
	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";

	unordered_map<uint64_t, uint64_t> hash_map;

	gettimeofday(&start_time,NULL);

	for(long int i=0;i<1000000;i++)
	{
		hash_map.insert(make_pair(rand(), rand()));
	}

	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;
	if(time_taken.tv_usec < 0)
	{
		time_taken.tv_sec--;
		time_taken.tv_usec = 1000000+time_taken.tv_usec;
	}
	printf("unordered_map::insert()\n");
	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";

	gettimeofday(&start_time,NULL);

	for(long int i=0;i<1000000;i++)
	{
		map.find(rand());
	}

	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;
	if(time_taken.tv_usec < 0)
	{
		time_taken.tv_sec--;
		time_taken.tv_usec = 1000000+time_taken.tv_usec;
	}
	printf("MyHashMap::find()\n");
	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";

	//unordered_map<uint64_t, uint64_t> hash_map;

	gettimeofday(&start_time,NULL);

	for(long int i=0;i<1000000;i++)
	{
		hash_map.find(rand());
	}

	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;
	if(time_taken.tv_usec < 0)
	{
		time_taken.tv_sec--;
		time_taken.tv_usec = 1000000+time_taken.tv_usec;
	}
	printf("unordered_map::find()\n");
	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";


	return 0;
}