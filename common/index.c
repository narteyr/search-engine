/**
 * @file index.c implements the functions
 * in 'index.h' that are used create and manage
 * indexes of webpages
 *
 * Author: Richmond Nartey Kwalah Tettey
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "hashtable.h"
#include "counters.h"
#include "mem.h"

int HASHTABLE_SIZE = 200; // size of the hashtable

// helper function declarations
void print_counters(void* fp, const int docID, const int count);
void print_hashtable(void* fp, const char* word, void* item);

/**
 * index_create creates a new index_t structure
 * and initializes the hashtable within it.
 *
 * Caller:
 *  caller is responsible for freeing the index_t structure and hashtable
 *
 * @return pointer to the newly created index_t structure
 */
index_t* index_create(void) {
    hashtable_t* ht = hashtable_new(HASHTABLE_SIZE);
    if (ht == NULL) {
        fprintf(stderr, "Error: could not create hashtable\n");
        return NULL;
    }
    index_t* index = mem_malloc(sizeof(index_t));
    if (index == NULL) {
        fprintf(stderr, "Error: could not allocate memory for index_t\n");
        hashtable_delete(ht, NULL);
        return NULL;
    }
    index->hashtable = ht;
    return index;
}

bool index_insert(index_t* index, char* word, int docID) {
    if (index == NULL || word == NULL || docID < 0) {
        return false;
    }

    // Look up the word in the hashtable
    counters_t* counters = hashtable_find(index->hashtable, word);

    if (counters == NULL) {
        // new word in docID: create new counters_t and insert into hashtable
        counters_t* ctrs = counters_new();
        if (ctrs == NULL) {
            fprintf(stderr, "Error: could not create counters_t for word '%s'\n", word);
            return false;
        }
        counters_add(ctrs, docID); // initialize with docID count = 1
        hashtable_insert(index->hashtable, word, ctrs);
    } else {
        // Word exists: increment count for this docID
        counters_add(counters, docID);
    }

    return true;
}


counters_t* index_find(index_t* index, char* word) {
    if (index == NULL || word == NULL) return NULL;
    return hashtable_find(index->hashtable, word);
}

bool index_save(index_t* index, const char* filename) {
    if (index == NULL || filename == NULL) return false;

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file '%s'\n", filename);
        return false;
    }

    hashtable_iterate(index->hashtable, fp, print_hashtable);
    fclose(fp);
    return true;
}

void print_counters(void* fp, const int key, const int value) {
    if (fp != NULL)
        fprintf((FILE*)fp, " %d %d", key, value);
}

void print_hashtable(void* fp, const char* key, void* item) {
    if (fp != NULL && key != NULL && item != NULL) {
        fprintf((FILE*)fp, "%s", key);
        counters_t* counters = (counters_t*)item;
        counters_iterate(counters, fp, print_counters);
        fprintf((FILE*)fp, "\n");
    }
}

void index_delete(index_t* index) {
    if (index != NULL) {
        hashtable_delete(index->hashtable, (void (*)(void*))counters_delete);
        mem_free(index);
    }
}
