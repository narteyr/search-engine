/**
 * @file index.h provides the interface for the 'index_t' data
 * structure and its associated functions.
 *
 * Author: Richmond Nartey Tettey CS50, 2025
 */


#ifndef INDEX_H
#define INDEX_H


#include <stdio.h>
#include "hashtable.h"
#include "counters.h"
#include "stdbool.h"

/**
 * Purpose: the index data structure is the index,
 * mapping from word to (docID, #occurences) pairs.
 * The index is a hashtable keyed by word and storing
 * counters as items. The counters is keyed by docID
 * and stores a count of the number of occurences of that
 * word in the document with that ID.
 * the hashtable's key is word, and its value will be counters_t
 * in counters_t will have linked list of docID and the word occurence
 *
 */
typedef struct index {
    hashtable_t *hashtable;
} index_t;

/**
 * Caller:
 *  caller provides nothing
 *  caller is responsible for freeing the memory allocated to the index_t
 *
 * @return a pointer to an index_t data structure
 */
index_t *index_create(void);


/**
 * Caller:
 *  caller provides a pointer to an index_t data structure
 *  caller is responsible for freeing the memory allocated to the index_t
 *
 * @param index a pointer to an index_t data structure
 * @param word is the word to be inserted
 * @param docID is the id of the Document to increment the counter of key
 */
bool index_insert(index_t *index, char *word, int docID);

/**
 *  Caller:
 *      provides valid pointer to index_t, and valid word
 *  We do:
 *      call hashtable_find that returns the item represented
 *      by the key.
 *  We return:
 *      NULL when pointer to counters_t is not found
 *      we return counters_t if it is found in index
 * @param index
 * @param word
 * @return
 */
counters_t* index_find(index_t *index, char *word);

/**
 * Caller:
 *  provides valid pointer to index, and valid pointer to filename
 *
 *  We do:
 *      try to append index object to file
 *
 *  Ownership:
 *      responsible for opening and closing the file after
 *      saving
 *
 * @param index  pointer to the index_t struct
 * @param filename pointer to the file to save index object
 * @return true if saved successfully, or else false
 */
bool index_save(index_t* index, const char* filename);

/**
 * Caller:
 *  provides valid pointer to filename
 *
 *  We do:
 *      try to load index object from file
 *
 *  Ownership:
 *      responsible for opening and closing the file after
 *      loading
 *
 * @param filename pointer to the file to load index object
 * @return a pointer to the index_t struct, or NULL if failed
 */
index_t* index_load(const char* filename);


/**
 * Caller:
 *  provides valid pointer to index_t
 *
 *  We do:
 *      free the memory allocated to the index_t struct
 *
 * @param index a pointer to an index_t data structure
 */
void index_delete(index_t* index);

#endif
