//
// Created by f007b2s on 4/20/25.
//

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "stdbool.h"
#include "mem.h"
#include "string.h"

/**************** local types ****************/
typedef struct setnode{
    const char *key;
    void *value;
    struct setnode *next;
} setnode_t;

/**************** global types ****************/
typedef struct set{
    setnode_t* root;
} set_t;

/**************** local functions ****************/
/* not visible outside this file */
// instantiate new node for set
static setnode_t* setnode_new(const char *key, void * value){
    setnode_t *new = mem_malloc_assert(sizeof(setnode_t), "failed to create set node");

    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}
/**************** global functions ****************/

/**************** new set ****************/
/* refer to set.h for description */
set_t* set_new(void){
    set_t *new_set = mem_malloc_assert(sizeof(set_t), "failed to create new set");

    if (new_set == NULL) {
        return NULL; // error allocate set
    }

    new_set->root = NULL;
    return new_set;
}

/**************** insert value in set ****************/
/* refer to set.h */
bool set_insert(set_t* set, const char* key, void* item){

    //we return false if key exists, any parameter is NULL, or error;
    if(set == NULL || key == NULL || item == NULL) return false;

    //create node if first insert
    if (set->root == NULL){
        set->root = setnode_new(key, item);
    }else {
        setnode_t* node = set->root;

        //set curr to last node when there is no duplicate
        setnode_t* new_node = setnode_new(key, item);

        if (new_node != NULL) {
            new_node->next = node->next;
            node->next = new_node;
            return true;
        }

        return false;
    }

#ifdef MEMTEST
    mem_report(stdout, "End of set_delete");
#endif

    return true;
}

/**************** set_print ****************/
void set_print(set_t* set, FILE* fp,
               void (*itemprint)(FILE* fp, const char* key, void* item)) {

    if (fp != NULL){
        if (set != NULL){
            for(setnode_t* node = set->root; node != NULL; node = node -> next){
                //print this node
                if (itemprint != NULL){ //prints the node's key and value
                    (*itemprint)(fp, node->key, node->value);
                }
                fputs("---->", fp);
            }
            fputs("[NULL]\n", fp);
        }else {
            fputs("null", fp);
        }
    }
}

/**************** set_delete ****************/
/* refer to set.h for description */
void set_delete(set_t* set, void (*itemDelete)(void* item)) {

    if (set != NULL) {
        for(setnode_t* node = set->root; node != NULL;) {

            setnode_t* temp = node->next; //remember what comes next

            // mem_free(node); //free the node
            if (itemDelete != NULL) {
                (*itemDelete) (node);
            }
            node = temp; //and move on to the next
        }

        mem_free(set);
        set = NULL;
    }

#ifdef MEMTEST
    mem_report(stdout, "End of set_delete");
#endif
}


/**************** set_find ****************/
/* refer to set.h for more description */

void* set_find(set_t* set, const char* key) {
    const char* find_key = key;

    if (set != NULL && key != NULL) {
        for (setnode_t *node = set->root; node != NULL; node = node -> next) {
            if (strcmp(node->key,find_key) == 0) return node->value;
        };
    }

    return NULL; //return null if key is not found/or key is null
}


/**************** set_iterate ****************/
/* refere to set.h for more description */


/* Iterate over the set, calling a function on each item.
 *
 * Caller provides:
 *   valid set pointer,
 *   arbitrary argument (pointer) that is passed-through to itemfunc,
 *   valid pointer to function that handles one item.
 * We do:
 *   nothing, if set==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc on each item, with (arg, key, item).
 * Notes:
 *   the order in which set items are handled is undefined.
 *   the set and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */

void set_iterate(set_t* set, void* arg,
                 void (*itemfunc)(void* arg, const char* key, void* item)) {

    if (set != NULL && itemfunc != NULL) {
        for (setnode_t* node = set->root; node != NULL;) {
            (*itemfunc)(arg, node->key, node->value);
            node = node -> next;
        }
    }
}
