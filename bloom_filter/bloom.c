// Hash function taken from: http://www.partow.net/programming/hashfunctions/index.html
// http://www.cse.yorku.ca/~oz/hash.html
// https://www.timdoug.com/etc/bloom_filter.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bloom.h"


int main(){
    // TODO is this how to initialize? How to initialize a table?
    bloom_filter_t bloom = {100, 0, NULL};

    int test_array[6] = {0, 1, 2, 3, 13, 97};

    int size = sizeof(test_array)/sizeof(int);
    // printf("%ld %ld\n", sizeof(test_array), sizeof(test_array)/sizeof(int));
    for(int i = 0; i < size; i++){
        printf("%llu\n", (uint64_t)hash2(&bloom, test_array[i]));
    }

    return 0;
}

/*******************
 Bit Operations
*******************/
// storing into array
void set_bit(bloom_filter_t *B, index_t i){
    // do check here to make sure i < size
    if (i >= B->size){
        printf("Index out of bounds!");
        exit(1);
    }

    // set bit i in table
    // do integer division to find the array location, sizeof gives bytes, multiply by 8 to get bits
    index_t index = i / (sizeof(index_t)*8);
    // do modulo to find the bit offset in the int
    index_t bit = i % (sizeof(index_t)*8);

    index_t mask = 1;

    // create mask for that bit offset... initialize int64 to 1... bitwise left shift i places: << i
    mask = mask << bit;

    // OR mask with current int and store the result of the OR back at the same location of the array
    B->table[index] = mask | B->table[index];
}


// should return 1 if bit is set, 0 if not. Checking if bit is set or not.
index_t get_bit(bloom_filter_t *B, index_t i){
    // do check here to make sure i < size
    if (i >= B->size){
        printf("Index out of bounds!");
        exit(1);
    }

    // get bit i in table
    // do integer division to find the array location, sizeof gives bytes, multiply by 8 to get bits
    index_t index = i / (sizeof(index_t)*8);
    // do modulo to find the bit offset in the int
    index_t bit = i % (sizeof(index_t)*8);

    index_t mask = 1;

    // create mask for that bit offset... initialize int64 to 1... bitwise left shift i places: << i
    mask = mask << bit;

    // OR mask with current int and store the result of the OR back at the same location of the array
    index_t result = mask & B->table[index];

    // If result is 0, then bit was not set. If it is NOT 0, then bit was set
    return result;
}

/****************
 API / Interface
****************/


/****************
 Hash Functions
****************/

// A bitwise hash function written by Justin Sobel
// http://www.partow.net/programming/hashfunctions/index.html#JSHashFunction
// Returns 88 56 8 90 16 27 for 0, 1, 2, 3, 13, and 97
index_t hash1(bloom_filter_t *B, key_t k){
    unsigned int len = sizeof(k);
    char *str = (char *)(&k);

    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for(i = 0; i < len; str++, i++)
    {
        // left-shift over bits so that the 5 right-most bits of the hash are 0's, then add the number value represented by those bits to k
        // then right-shift hash by 2 and adding the associated value
        // then do a bitwise XOR (not equals) with the original hash: same as hash ^=
        hash = hash ^ ( ((hash << 5) + (k) + (hash >> 2)) );
    }

    return hash % B->size;
}


// open source SDBM project: http://www.partow.net/programming/hashfunctions/index.html#SDBMHashFunction
// Returns 0, 48, 96, 44, 24, 56 for 0, 1, 2, 3, 13, and 97
index_t hash2(bloom_filter_t *B, key_t k){
    unsigned int hash = 0;
    unsigned int i    = 0;

    unsigned int len = sizeof(k);
    // cast to char
    char *str = (char *)(&k);

    for(i = 0; i < len; str++, i++)
    {
        hash = (k) + (hash << 6) + (hash << 16) - hash;
    }

    return hash % B->size;
}
