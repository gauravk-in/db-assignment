/**
 * author Gaurav Kukreja
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <functional>

 using namespace std;

#define DEFAULT_BUCKET_INIT_SIZE pow(2, DEFAULT_BUCKET_INIT_LOG_SIZE)
#define DEFAULT_BUCKET_INIT_LOG_SIZE 10

#define ENOTEXIST -2


 class Pair
 {
 public:
 	uint64_t hashedKey;
 	uint64_t key;
 	uint64_t value;
 	Pair *next;

 	Pair(uint64_t _hashedKey, uint64_t _key, uint64_t _value)
 	{
 		hashedKey= _hashedKey;
 		key = _key;
 		value = _value;
 		next = NULL;
 	}

 	~Pair()
 	{
 		next = NULL;
 	}
 };

 class Bucket 
 {
 public:
 	Pair *pairList;
 	int num_pairs;

 	Bucket()
 	{
 		pairList = NULL;
 		num_pairs = 0;
 	}

 	uint64_t insert(uint64_t hashedKey, uint64_t key, uint64_t value);
 	uint64_t at(uint64_t key);

 };

 uint64_t Bucket::insert(uint64_t hashedKey, uint64_t key, uint64_t value)
 {
 	Pair *temp = new Pair(hashedKey, key, value);

 	num_pairs++;
 	temp->next = pairList;
 	pairList = temp;
 }

 uint64_t Bucket::at(uint64_t hashedKey)
 {
 	for(Pair *temp=pairList; temp != NULL; temp=temp->next)
 	{
 		if(temp->hashedKey == hashedKey)
 		{
 			return temp->value;
 		}
 	}
 }

 class MyHashMap
 {
 private:
 	Bucket *bucketArray;
 	int bucketLogSize;


 	int rehash();
 	uint64_t generate_hash(uint64_t key);

 public:
 	uint64_t num_pairs;

 	MyHashMap()
 	{
 		bucketArray = (Bucket*)malloc(sizeof(Bucket)*DEFAULT_BUCKET_INIT_SIZE);
 		bucketLogSize = DEFAULT_BUCKET_INIT_LOG_SIZE;
 		num_pairs = 0;
 	}

 	uint64_t insert(uint64_t key, uint64_t value);
 	uint64_t insert(uint64_t hashedKey, uint64_t key, uint64_t value);
 	uint64_t at(uint64_t key);

 };

 uint64_t MyHashMap::generate_hash(uint64_t key)
 {
 	/*
 	hash<uint64_t> hash_func;
 	uint64_t hashedKey = hash_func(key);
 	//printf("Hash Value = %llu\n", hashedKey);
	*/
 	
 	//uint64_t hashedKey = 5381;

    //hashedKey = ((hashedKey << 5) + hashedKey) + key; /* hashedKey * 33 + c */
    //printf("Hash Value = %llu\n", hashedKey);

 	return key;
 }

 int MyHashMap::rehash()
 {
 	Bucket *oldBucketArray;
 	oldBucketArray = bucketArray;

 	bucketLogSize++;

 	//printf("rehashing : bucketLogSize = %d\n", bucketLogSize);
 	//printf("rehashing : num_pairs = %llu\n", num_pairs);

 	bucketArray = (Bucket*)malloc(sizeof(Bucket)*pow(2, bucketLogSize));
	/*for(int i=0; i<pow(2, bucketLogSize); i++)
	{
		bucketArray[i] = new Bucket();
	}*/

		for(int i=0; i<pow(2, bucketLogSize-1); i++)
		{
			if(oldBucketArray[i].num_pairs!=0)
			{
				for(Pair *iter=oldBucketArray[i].pairList; iter != NULL; iter=iter->next)
				{
					insert(iter->hashedKey, iter->key, iter->value);
				}
			//free((void*)&oldBucketArray[i]);
			}
		}
	}

	uint64_t MyHashMap::insert(uint64_t key, uint64_t value) 
	{
		if(num_pairs > pow(2, bucketLogSize)+pow(2, bucketLogSize-6))
		{
			rehash();
		}

		uint64_t hashedKey = generate_hash(key);
		insert(hashedKey, key, value);
	}

	uint64_t MyHashMap::insert(uint64_t hashedKey, uint64_t key, uint64_t value) 
	{
		int bucketNum = (int)((uint64_t)hashedKey % (uint64_t)pow(2, bucketLogSize));
		//printf("Bucket Number = %d\n", bucketNum);
		num_pairs++;
		bucketArray[bucketNum].insert(hashedKey, key, value);
	}

	uint64_t MyHashMap::at(uint64_t key)
	{
		uint64_t hashedKey = generate_hash(key);

		int bucketNum = (int)((uint64_t)hashedKey % (uint64_t)pow(2, bucketLogSize));
		return bucketArray[bucketNum].at(hashedKey);
	}




