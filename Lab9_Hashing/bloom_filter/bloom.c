// Hash function taken from: http://www.partow.net/programming/hashfunctions/index.html
// and http://www.cse.yorku.ca/~oz/hash.html

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bloom.h"
// function declaration
int* create_random_numbers(int count);


int main(){
    /*********************
     * Test Hash Functions
     * *******************/
//    bloom_filter_t bloom = {100, 0, NULL};
//
//    int test_array[6] = {0, 1, 2, 3, 13, 97};
//
//    int size = sizeof(test_array)/sizeof(int);
//    // printf("%ld %ld\n", sizeof(test_array), sizeof(test_array)/sizeof(int));
//    for(int i = 0; i < size; i++){
//        printf("%llu\n", (uint64_t)hash2(&bloom, test_array[i]));
//    }
    /**********************
     * Test Bit Operations
     * ********************/
//    bloom_filter_t bloom;
//    bloom_init(&bloom, 66);
//
//    // set_bit is expecting a pointer, so make the struct a pointer
//    set_bit(&bloom, 64);
//
//    printf("%llu\n", get_bit(&bloom, 64));
//
//    bloom_destroy(&bloom);

    /**********************
     * Test API Check & Add
     * ********************/
//    bloom_filter_t bloom;
//    bloom_init(&bloom, 100);
//
//    bloom_add(&bloom, 5);
//
//    printf("%d\n", bloom_check(&bloom, 6));
//
//    uint64_t counter = 0;
//    for (index_t j=0; j < 100; j++){
//        index_t set = get_bit(&bloom, j);
//        if (set != 0){
//            counter++;
//        }
//    }
//
//    printf("Total bits set: %llu\n", counter);
//
//    bloom_destroy(&bloom);

    /*************
     * Smoke Test
     * ***********/
//    // create bloom filter with 1000 elements (bits)
//    bloom_filter_t bloom;
//    bloom_init(&bloom, 1000);
//
//    // add the first 70 positive integers to filter
//    for (int i=1; i <= 70; i++){
//        bloom_add(&bloom, i);
//    }
//
//    // count the actual number of of  bits set in table
//    // Write a quick function that counts the actual number of bits set in your table. (This doesn't need to be clever, a
//    // brute force loop calling get_bit is fine.)
//    uint64_t counter = 0;
//    for (index_t j=0; j < 1000; j++){
//        index_t set = get_bit(&bloom, j);
//        if (set != 0){
//            counter++;
//        }
//    }
//
//    printf("Total bits set: %llu\n", counter);
//    // here bloom is no longer a pointer, just a struct, so use '.' instead of '->'
//    printf("Counter: %llu\n", bloom.count);
//    bloom_destroy(&bloom);

    /**************************
     * Understanding Trade-offs
     * ************************/

    // First, write a function that generates an array of 100 random number between 0 and 1000000. You might find the rand() function helpful.
    // The input should be two arrays of 100 numbers, just like the ones generated from the previous function.
    int* array1 = create_random_numbers(100);
    int* array2 = create_random_numbers(100);

    // First, have the function create a new Bloom filter with 1000 elements and add all the elements of the first input array to it.
    bloom_filter_t bloom;
    bloom_init(&bloom, 1000);

    for (int i = 0; i < 100; i++){
        bloom_add(&bloom, array1[i]);
    }

    // Second, create a loop that counts the number of bits, just like your smoke test.
    uint64_t counter = 0;
    for (index_t j=0; j < 1000; j++){
        index_t set = get_bit(&bloom, j);
        if (set != 0){
            counter++;
        }
    }
    printf("Total bits set: %llu\n", counter);

    // Finally, create a loop that checks whether the numbers in the second array are in the table.
    // Recall that we never added them, so if our hash table was perfecst, there would be a very small number of collisions
    uint64_t in_array_count = 0;
    for (index_t j=0; j < 100; j++){
        index_t check = bloom_check(&bloom, array2[j]);
        if (check != 0){
            in_array_count++;
        }
    }
    // Count up and print out how many of the numbers in the second array returned true.
    printf("Total false positive count: %llu\n", in_array_count);

    free(array1);
    free(array2);
    bloom_destroy(&bloom);
    return 0;
}
//As the number of hash functions goes up, the occupancy rate increases and and the false positive rate decreases.
// However this is assuming the table size is large enough -- after a certain point when the number of hashes becomes too large, the false positive rate actually increases.
/* N_HASHES    bits set     false positive count
 * 1            93          10
 * 2            173         3
 * 3            256         2
 * 4            318         1
 * 5            378         4
 */


int* create_random_numbers(int count){
    int *array = (int *) malloc(count * sizeof(int));
    for (int i=0; i < count; i++){
        array[i] = rand();
    }

    return array;
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
    // do integer division to find the array location; sizeof gives bytes, multiply by 8 to get bits
    index_t index = i / (sizeof(index_t)*8);
    // do modulo to find the bit offset in the int
    index_t bit = i % (sizeof(index_t)*8);

    index_t mask = 1;

    // create mask for that bit offset... initialize int64 to 1... bitwise left shift i places: << i
    mask = mask << bit;

    // OR bitwise comparison with mask against current int and store the result of the OR back at the same location of the array
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
    // do integer division to find the array location; sizeof gives bytes, multiply by 8 to get bits
    index_t index = i / (sizeof(index_t)*8);
    // do modulo to find the bit offset in the int
    index_t bit = i % (sizeof(index_t)*8);

    index_t mask = 1;

    // create mask for that bit offset... initialize int64 to 1... bitwise left shift i places: << i
    mask = mask << bit;

    // AND bitwise comparison mask with against current int
    index_t result = mask & B->table[index];

    // If result is 0, then bit was not set. If it is NOT 0, then bit was set
    return result;
}

/****************
 API / Interface
****************/

void bloom_init(bloom_filter_t *B, index_t size_in_bits){
    B->size = size_in_bits;

    B->count = 0;

    // add 1 extra byte for remainder after integer division
    index_t size_of_array = (size_in_bits / sizeof(index_t)) + 1;

//    B->table = (index_t *) malloc(sizeof(index_t) * size_of_array);
    // free empty space set to 0
    B->table = (index_t *) calloc(size_of_array, sizeof(index_t));
}


void bloom_destroy(bloom_filter_t *B){
    free(B->table);
}


int bloom_check(bloom_filter_t *B, key_t k){
    // create N_HASHES of k
    for (int i=0; i < N_HASHES; i++){
        // TODO  have to mod again since adding hash functions?
        index_t hash = (hash1(B, k) + i*hash2(B, k)) % B->size;
        index_t outcome = get_bit(B, hash);
        // check each hash location with get_bit. If any one of them is 0, then return 0 (definitely not in bloom filter).
        if (outcome == 0){
            return 0;
        }
    }
    // If none are 0, then return 1 (most likely in bloom filter).
    return 1;
}

void bloom_add(bloom_filter_t *B, key_t k){
    // create N_HASHES of k
    for (int i=0; i < N_HASHES; i++){
        // TODO  have to mod again since adding hash functions?
        index_t hash = (hash1(B, k) + i*hash2(B, k)) % B->size;
        set_bit(B, hash);
    }
    // Make sure to add up count
    B->count++;
}


/****************
 Hash Functions
****************/

// A bitwise hash function written by Justin Sobel
// http://www.partow.net/programming/hashfunctions/index.html#JSHashFunction
// Returns 88 56 8 90 16 27 for 0, 1, 2, 3, 13, and 97
index_t hash1(bloom_filter_t *B, key_t k){
    unsigned int len = sizeof(k);
    // cast to char
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
    unsigned int len = sizeof(k);
    // cast to char
    char *str = (char *)(&k);

    unsigned int hash = 0;
    unsigned int i    = 0;

    for(i = 0; i < len; str++, i++)
    {
        hash = (k) + (hash << 6) + (hash << 16) - hash;
    }

    return hash % B->size;
}
