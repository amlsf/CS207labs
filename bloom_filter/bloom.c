// Hash function taken from: http://www.partow.net/programming/hashfunctions/index.html
// http://www.cse.yorku.ca/~oz/hash.html
// https://www.timdoug.com/etc/bloom_filter.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(){
    // TODO is this how to initialize? How to initialize a table?
    bloom_filter_t bloom = {100};

    int *test_array[6] = {0, 1, 2, 3, 13, 97};

    return 0;
}

/****************
 Hash Functions
****************/

// A bitwise hash function written by Justin Sobel
// http://www.partow.net/programming/hashfunctions/index.html#JSHashFunction
index_t hash1(bloom_filter_t *B, key_t k){
    unsigned int len = sizeof(k);
    char *str = (char *)(&k);

    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for(i = 0; i < len; str++, i++)
    {
        // TODO what is this doing again?
        hash = hash ^ ( ((hash << 5) + (k) + (hash >> 2)) );
    }

    // TODO B or *B?
    return hash % B->size;
}

/*
unsigned int JSHash(unsigned char *str, unsigned int len)
{
    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for(i = 0; i < len; str++, i++)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}
**/

// open source SDBM project: http://www.partow.net/programming/hashfunctions/index.html#SDBMHashFunction
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

/*
unsigned int SDBMHash(unsigned char *str, unsigned int len)
{
    unsigned int hash = 0;
    unsigned int i    = 0;

    for(i = 0; i < len; str++, i++)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
**/
