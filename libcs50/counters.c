/**
* counters.c - 'CS50' counters module
*
* see counters.h for more information
*
* Richmond Nartey Kwalah Tettey, April 19, 2025
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "counters.h"
#include "stdbool.h"

/**************** file-local global variables ****************/
/* none */

// structure to store attributes of key in the counters array
typedef struct entry{
    int key;
    int count;
    struct entry *next;
} entry_t;

//struct for counters arrays
typedef struct counters{
    entry_t *head;
} counters_t;

/**************** entries new ****************/
entry_t * counters_new_entry(const int key, int count) {
    entry_t* new_node = mem_malloc(sizeof(entry_t));
    new_node->key = key;
    new_node->count = count;

    return new_node;
}

/**************** counters new ****************/
// see counters.h for description
counters_t* counters_new(void){
    counters_t *counters = mem_malloc(sizeof(counters_t));
    if (counters == NULL) {
        return NULL;
    }
    counters-> head = NULL;
    return counters;
}


/**************** add new key to counters ****************/
// see counters.h for description
int counters_add(counters_t* ctrs, const int key)
{
    if (ctrs != NULL && key >= 0) {

        for (entry_t* curr_entry = ctrs->head; curr_entry != NULL; curr_entry = curr_entry -> next) {

            if (curr_entry->key == key) {
                curr_entry->count++;
                return curr_entry->count;
            }
        }

        //adds a new node when key is not found in counters
        entry_t* n_node = counters_new_entry(key,1);

        n_node -> next = ctrs -> head;
        ctrs -> head = n_node; //updates the header to new node
        return 1;
    }

    return 0;
}


/**************** counters_get ****************/
int counters_get(counters_t* ctrs, const int key) {
    if (ctrs != NULL && key >= 0) {
        for (entry_t *node = ctrs->head; node != NULL;) {
            if (node->key == key) return node->count;
            node = node->next;
        }
    }
    return 0;
}

/**************** counters_set ****************/
/* refer from counters.h for description */

/* Set the current value of counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to counterset,
 *   key(must be >= 0),
 *   counter value(must be >= 0).
 * We return:
 *   false if ctrs is NULL, if key < 0 or count < 0, or if out of memory.
 *   otherwise returns true.
 * We do:
 *   If the key does not yet exist, create a counter for it and initialize to
 *   the given value.
 *   If the key does exist, update its counter value to the given value.
 */
bool counters_set(counters_t* ctrs, const int key, const int count) {
    // Validate arguments
    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    }

    // If the list is empty, insert as head
    if (ctrs->head == NULL) {
        entry_t* new_node = counters_new_entry(key, count);
        if (new_node == NULL) {
            return false;
        }
        new_node->next = NULL;
        ctrs->head = new_node;
        return true;
    }

    // Otherwise, walk the list looking for the key
    for (entry_t* node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key) {
            // Key already exists: update its count
            node->count = count;
            return true;
        }
    }

    // Key not found: prepend a new entry
    entry_t* new_node = counters_new_entry(key, count);
    if (new_node == NULL) {
        return false;
    }
    new_node->next = ctrs->head;
    ctrs->head = new_node;
    return true;
}


/**************** counters_print ****************/
/* refer to counters.h for descript */
void counters_print(counters_t* ctrs, FILE* fp) {

    if (ctrs != NULL && fp != NULL) {
        bool first = true;

        for (entry_t* node = ctrs->head; node != NULL;) {
            if (!first) fputc(',',fp);
            first = false;

            char buffer[256]; //temporary buffer to hold string
            snprintf(buffer,sizeof(buffer),
                "{%d = %d}", node->key,node->count);

            fputs(buffer,fp);
            node = node->next;
        }

        fputs("\n",fp);
    }else if (fp != NULL) {
        fputs("(null)\n", fp);
    }
}

/**************** counters_iterate ****************/
/* Iterate over all counters in the set.
 *
 * Caller provides:
 *   valid pointer to counterset,
 *   arbitrary void*arg,
 *   valid pointer to itemfunc that can handle one item.
 * We do:
 *   nothing, if ctrs==NULL or itemfunc==NULL.
 *   otherwise, call itemfunc once for each item, with (arg, key, count).
 * Note:
 *   the order in which items are handled is undefined.
 *   the counterset is unchanged by this operation.
 */
void counters_iterate(counters_t* ctrs, void* arg,
                      void (*itemfunc)(void* arg,
                                       const int key, const int count)) {
    if (ctrs != NULL && itemfunc != NULL) {
        for (entry_t* node = ctrs->head; node != NULL;) {
            (*itemfunc)(arg,node->key,node->count);
            node = node->next;
        }
    }
}


/**************** counters_delete ****************/
/* refer to counters.h for more description */
void counters_delete(counters_t* ctrs) {

    if (ctrs != NULL) {
        for (entry_t* node = ctrs->head; node != NULL;) {
            entry_t* temp = node->next;
            mem_free(node);
            node = temp;
        }
        mem_free(ctrs);
    }else {
        printf("counter is null \n");
    }

    #ifdef MEMTEST
        mem_report(stdout, "End of set_delete");
    #endif
}
