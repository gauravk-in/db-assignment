/**
 * author Gaurav Kukreja
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
 #include <atomic>

#include <functional>

using namespace std;

#define DEFAULT_BUCKET_INIT_LOG_SIZE 6
#define DEFAULT_BUCKET_INIT_SIZE (1 << DEFAULT_BUCKET_INIT_LOG_SIZE)

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
 	Pair* pairList;

 	Bucket()
 	{
 		pairList = NULL;
 	}

 	uint64_t insert(uint64_t hashedKey, uint64_t key, uint64_t value);
 	uint64_t find(uint64_t key);

 };

 uint64_t Bucket::insert(uint64_t hashedKey, uint64_t key, uint64_t value)
 {
 	Pair *temp = new Pair(hashedKey, key, value);

 	temp->next = pairList;
 	pairList = temp; }

 uint64_t Bucket::find(uint64_t hashedKey)
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

 	atomic<int> rehashing_lock;

 	int rehash();
 	uint64_t generate_hash(uint64_t key);

 public:
 	atomic<uint64_t> num_pairs;

 	MyHashMap()
 	{
 		int i;
 		bucketArray = (Bucket*)malloc(sizeof(Bucket)*DEFAULT_BUCKET_INIT_SIZE);
 		for(i=0;i<DEFAULT_BUCKET_INIT_SIZE;i++)
 			bucketArray[i].pairList = NULL;
 		bucketLogSize = DEFAULT_BUCKET_INIT_LOG_SIZE;
 		num_pairs = 0;
 		rehashing_lock=0;
 	}

 	uint64_t insert(uint64_t key, uint64_t value);
 	uint64_t insert(uint64_t hashedKey, uint64_t key, uint64_t value);
 	uint64_t find(uint64_t key);

 };

 uint64_t MyHashMap::generate_hash(uint64_t key)
 {
 	uint64_t hashedKey = 5381;
    hashedKey = ((hashedKey << 5) + hashedKey) + key; /* hashedKey * 33 + c */ 	return hashedKey;
 }

 int MyHashMap::rehash()
 {
 	Bucket *oldBucketArray;
 	int oldBucketSize = (1 << bucketLogSize);
 	oldBucketArray = bucketArray;
 	bucketLogSize++;
 	bucketArray = (Bucket*)malloc(sizeof(Bucket)*(1 << bucketLogSize));
 	for(int i=0; i < (1 << bucketLogSize); i++)
 		bucketArray[i].pairList = NULL;

 	for(int i=0; i<oldBucketSize; i++)
 	{
 		for(Pair *iter=oldBucketArray[i].pairList; iter != NULL; iter=iter->next)
 		{ 			insert(iter->hashedKey, iter->key, iter->value);
 		}
 	}
 	free(oldBucketArray);
 }

 uint64_t MyHashMap::insert(uint64_t key, uint64_t value) 
 {
 	/*while(rehashing_lock);
 	rehashing_lock++;
 	if(num_pairs > (1 << bucketLogSize) + (1 << (bucketLogSize -2)))
 	{ 		rehash();
 	}
 	rehashing_lock--;*/
 	uint64_t hashedKey = generate_hash(key);
 	num_pairs++;
 	uint64_t bucketNum = (hashedKey & ((1 << bucketLogSize)-1));
 	bucketArray[bucketNum].insert(hashedKey, key, value);
 }

 uint64_t MyHashMap::insert(uint64_t hashedKey, uint64_t key, uint64_t value) 
 {
 	uint64_t bucketNum = (hashedKey & ((1 << bucketLogSize)-1)); 	
 	bucketArray[bucketNum].insert(hashedKey, key, value);
 }

 uint64_t MyHashMap::find(uint64_t key)
 {
 	uint64_t hashedKey = generate_hash(key);

 	uint64_t bucketNum = (hashedKey & ((1 << bucketLogSize)-1));
 	return bucketArray[bucketNum].find(hashedKey);
 }