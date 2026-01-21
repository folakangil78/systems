/* I Francis Olakangil certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus. */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _cache {
	int size;
	int blockSize;
	int hits;
	int misses;
	int sets;
	int blocks;
	int * cacheInfo;
} Cache;

int computeTag(int address, Cache* cache) {
	int set = log2(cache -> sets);
	int offset = log2(cache -> blockSize);
	return address >> (set + offset);
	// >> operator shifts current address right by given value, denoted by sum of offset and tag
}

int computeSet(int address, Cache* cache) {
	int set = log2(cache -> sets);
	int offset = log2(cache -> blockSize);
	return (address >> offset) & ((1 << set) - 1);
	// creates mask based on offset and tag to isolate set
}

int addItem(int address, Cache * cache) {
	int tag = computeTag(address, cache);
	int index_of_set = computeSet(address, cache);

	int size_of_set = cache -> blocks / cache -> sets;
	int start_of_set = index_of_set * (cache -> blocks / cache -> sets);

	int i = 0;
	for (i = 0; i < size_of_set; i++) {
		if (cache -> cacheInfo[start_of_set + i] == -1) {
			cache -> cacheInfo[start_of_set + i] = tag;
			return 1;
			// assumes empty spot to populate tag at
		}
	}

	int replace_at_index = start_of_set + rand() % size_of_set;
	cache -> cacheInfo[replace_at_index] = tag;
	// replaces with tag at random location if no availability

	return 0;
}

int inCache(int address, Cache* cache) {
	int tag = computeTag(address, cache);
	int index_of_set = computeSet(address, cache);

	int size_of_set = cache -> blocks / cache -> sets;
	int start_of_set = index_of_set * (cache -> blocks / cache -> sets);

	int i = 0;
	for (i = 0; i < size_of_set; i++) {
		if (cache -> cacheInfo[start_of_set + i] == tag) {
			cache -> hits++;
			return 1;
		} // iterates through set values and checks for match, incrementing hits attrib if the case
	}

	cache -> misses++;
	addItem(address, cache);
	// increments misses attrib if for loop ends and inserts new cache block

	return 0;
}

double hitRatio(Cache * cache) {
	int access_total_count = cache -> misses + (cache -> hits);
	
	// misses = data calls for data not in cache and needing to access main memory

	if (access_total_count != 0.0) {
		return (double)(cache -> hits) / access_total_count;
	} // calculates ratio as long as total access > 0 (prevent division by 0 and undefined behavior)

	return 0.0;
	// only returns here if total access count is 0
}

double missRatio(Cache* cache) {
	int total_access_count = cache -> misses + (cache -> hits);

	if (total_access_count != 0.0) {
		return (double)(cache -> misses) / total_access_count;
	}

	return 0.0;
}

int main(int argc, char * argv[]) {
	if (argc < 3) {
		return 1;
	}

	int total_size = atoi(argv[1]);
	int num_of_sets = atoi(argv[2]);
	// accesses arg values from argv char array

	Cache cache;
	cache.size = total_size;
	cache.blockSize = 16;
	cache.hits = 0;
	cache.misses = 0;
	cache.sets = num_of_sets;
	cache.blocks = total_size / 16;
	// dividing by block size to find number of blocks

	cache.cacheInfo = (int *)malloc(cache.blocks * sizeof(int));
	// allocating adequate memory based on block num

	int i = 0;
	for (i = 0; i < cache.blocks; i++) {
		cache.cacheInfo[i] = 0;
	} // setting each elem in cache information array to def val to represent empty cache

	// cache ready...for method testing


	free(cache.cacheInfo);

	return 0;
}
