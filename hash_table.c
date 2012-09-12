/**
 * An simple hashtable implementation for strings
 * using Pearson Hashing http://en.wikipedia.org/wiki/Pearson_hashing
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int T[] = {2, 159, 207, 125, 75, 95, 161, 57, 128, 195, 80, 252, 202, 145, 208, 27, 197, 243, 68, 250, 81, 228, 73, 98, 137, 249, 205, 113, 143, 56, 199, 86, 191, 186, 49, 134, 52, 220, 196, 160, 206, 229, 150, 136, 87, 169, 9, 216, 131, 107, 165, 24, 234, 225, 133, 3, 185, 105, 236, 103, 78, 54, 147, 188, 25, 6, 61, 84, 82, 166, 42, 237, 200, 239, 187, 88, 32, 162, 39, 156, 15, 85, 16, 148, 213, 106, 214, 175, 233, 13, 93, 66, 20, 218, 76, 179, 230, 102, 63, 135, 51, 64, 104, 203, 100, 223, 174, 40, 138, 90, 140, 224, 60, 157, 89, 94, 77, 226, 232, 238, 67, 28, 177, 167, 30, 212, 146, 204, 247, 189, 246, 50, 210, 181, 8, 154, 53, 37, 149, 168, 121, 71, 241, 141, 58, 244, 255, 240, 17, 65, 118, 178, 170, 12, 1, 99, 221, 29, 120, 209, 18, 116, 153, 176, 158, 235, 248, 173, 115, 117, 31, 184, 242, 164, 190, 231, 97, 130, 172, 92, 180, 72, 183, 144, 217, 34, 7, 44, 41, 38, 110, 139, 0, 201, 132, 215, 22, 70, 74, 119, 5, 59, 33, 193, 253, 108, 219, 91, 222, 163, 151, 171, 192, 251, 101, 198, 245, 43, 69, 35, 129, 23, 46, 122, 124, 114, 96, 79, 227, 19, 142, 4, 155, 112, 109, 83, 126, 48, 21, 26, 111, 194, 45, 36, 127, 182, 55, 14, 211, 254, 152, 123, 47, 11, 62, 10};

/**
 * Hash a NULL terminated string
 */
int hash(char *string) 
{
	int h = 0;
	char c;
	while ( c = *(string++) )
		h = T[h ^ c];
	return h;
}

struct hash_table 
{
	linked_list buckets[256];
	int size;
};

struct record
{
	char *key;
	void *value;
	size_t size;
};

/**
 * Create a new record making a copy of the arguments
 * used to build it and return it.
 */
struct record *re_new(char *key, void *value, size_t value_size)
{
	struct record *re = (record *) malloc(sizeof(record));
	if (re == NULL)
		return NULL;
	re->key = strdup(key);
	value = malloc(value_size);
	if (value == NULL)
		return NULL;
	memcpy(re->value, value, value_size); 
	re->size = value_size;
	return re;
}

/**
 * Remove a record.
 */
void re_dispose(struct record *re)
{
	free(re->key);
	free(re->value);
	free(re);
}

int compare_records(void *r1, void *r2) 
{
	return strcmp(((struct record *) r1)->key,\
			((struct record *) r2)->key);
}

/**
 * Create a new Hash Table and return it.
 */
struct hash_table *ht_new()
{
	struct hash_table *ht = (hash_table *) malloc(sizeof(hash_table));
	if (ht == NULL)
		return NULL;

	int i = 0;
	for (i = 0; i < 256; i++)
		buckets[i] = ll_new();
	return ht;
}

/**
 * Removes a hash table
 */
void ht_dispose(struct hash_table *ht)
{
	int i = 0;
	for (i = 0; i < 256; i++)
		ll_dispose(buckets[i], re_dispose);
	free(ht);
}
/**
 * Get an entry from the hash table
 */
record *ht_get_entry(struct hash_table *ht, cconst char *key)
{
	int hash = hash(key);
	return ll_find(ht->buckets[hash], (void *) key, compare_records);
}

int ht_put_entry(struct hash_table *ht, const char *key, void *value)
{
	ll_add_last(ht->buckets[hash(key)], (void *) re_new(key, value));
}

int ht_remove_entry(struct hash_table *ht, const char *key)
{
	ll_remove(ht->buckets[hash(key)], (void *) key, compare_records);
}

int ht_contains(struct hash_table *ht, const char *key)
{
	return NULL != ht_get_entry(ht, key);
}


int main(void)
{
	printf("%d\n",hash("hello"));
}






































