#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t index_t; // output of hash fxn
typedef uint64_t key_t; // input to hash fxn
typedef struct {
  index_t size; // in bits TODO is this the size of the whole table?
  index_t count; // in bits TODO is this the count of elements in the table? (x N_HASHES to get total)
  index_t *table; // TODO what is this? Pointer to the hash table?
} bloom_filter_t;
// # of hash functions we will have
#define N_HASHES 3

void set_bit(bloom_filter_t *B, index_t i); // TODO what is this?
index_t get_bit(bloom_filter_t *B, index_t i); // TODO what is this?

index_t hash1(bloom_filter_t *B, key_t k);
index_t hash2(bloom_filter_t *B, key_t k);

void bloom_init(bloom_filter_t *B, index_t size_in_bits);
void bloom_destroy(bloom_filter_t *B);
int bloom_check(bloom_filter_t *B, key_t k);
void bloom_add(bloom_filter_t *B, key_t k);
