//
// Created by f007b2s on 4/20/25.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string.h"
#include "hashtable.h"
#include "mem.h"
#include "hash.h"


/**************** local global variables ****************/
typedef struct hash_node {
    const char* key;
    void *item;
    struct hash_node* next;
}hash_node_t;

/**************** global types ****************/
typedef struct hashtable {
    int number_of_slots;
    int size; //number of items in the hashtable
    void **hash_array; //initialize new array when struct is instantiated
} hashtable_t;

/**************** helper functions ****************/
void hashtable_delete_node(hash_node_t* node, void (*itemdelete)(void* item));
hash_node_t* hashtable_new_node(const char* key, void* item, hash_node_t* next);

/**************** hashtable_new ****************/
//refer to hashtable.h for description
hashtable_t* hashtable_new(const int num_slots){
    hashtable_t* new_table = mem_malloc(sizeof(hashtable_t));

    //create new array
    if (new_table != NULL) {
        int slots = (num_slots > 0) ? num_slots : 10;
        new_table->number_of_slots = slots;
        new_table->size= 0;

        void **hash_array = mem_calloc(slots, sizeof(hash_node_t*));

        if (hash_array != NULL) {
            new_table->hash_array = hash_array;
        }else {
            mem_free(new_table);
            return NULL;
        }
    }

    return new_table;
}


/**************** hashtable_insert ****************/
/* refer to hashtable.h  for description */
bool hashtable_insert(hashtable_t* ht, const char* key, void* item) {

    if (ht != NULL && key != NULL && item != NULL) {
        const int index = hash_jenkins(key,ht->number_of_slots); //hash to get index for key

        //check for duplicate keys
        const hash_node_t* curr = ht->hash_array[index];
        while (curr != NULL) {
            if (strcmp(curr->key,key) == 0) {
                return false;
            }
            curr = curr->next;
        }

        //insert when there is no duplicate
        size_t length = strlen(key) + 1;
        char* cp_key = mem_malloc(length);
        if (cp_key == NULL) {
            return false;
        }
        //copy the string into the new buffer
        strcpy(cp_key, key);


        //insert at the head of the list
        hash_node_t* new_node = hashtable_new_node(cp_key,item,NULL);
        if (new_node == NULL) {
            mem_free(cp_key);
            return false;
        }

        //insert at head
        new_node->next = ht->hash_array[index];
        ht->hash_array[index] = new_node;
        return true;
    }

    return false;
}

/**************** hashtable_find ****************/
/* refer to hashtable.h for description */
void* hashtable_find(hashtable_t* ht, const char* key) {
    if (ht != NULL && key != NULL) {
        const int index = hash_jenkins(key, ht->number_of_slots);
        if (ht->hash_array[index] != NULL) {
            for (hash_node_t* curr = ht->hash_array[index]; curr != NULL;) {
                if (strcmp(curr->key,key) == 0) {
                    return curr->item;
                }
                curr = curr->next;
            }
        }
    }
    return NULL;
}

/**************** hashtable_print ****************/
/* refer to hashtable.h for descriptions */
void hashtable_print(hashtable_t* ht, FILE* fp,
                     void (*itemprint)(FILE* fp, const char* key, void* item)) {

    if (fp == NULL) return; //do nothing if file is null

    if (ht == NULL) {
        fputs("(null)\n",fp);
        return;
    }

    //print items when ht and fp are valid
    for (int i = 0; i < ht->number_of_slots;i++) {
        fprintf(fp,"[%d] -> ", i);

        hash_node_t* node = ht->hash_array[i];
        if (node == NULL) {
            fputs(" (empty)\n",fp); //if no nodes, print empty
            continue;
        }

        for (; node != NULL; node = node->next) {
            if (itemprint != NULL) {
                fputc(' ', fp);
                (*itemprint)(fp, node->key,node->item);
            }
        }

        fputc('\n',fp);
    }
}


/**************** hashtable_iterate ****************/
/* refer to hashtable.h for description */
void hashtable_iterate(hashtable_t* ht, void* arg,
                       void (*itemfunc)(void* arg, const char* key, void* item)) {

    if (ht != NULL && itemfunc != NULL) {
        for (int i = 0; i < ht->number_of_slots; i++) {
            for (hash_node_t* node = ht->hash_array[i]; node != NULL;node = node->next) {
                (*itemfunc)(arg,node->key,node->item);
            }
        }
    }
}

/**************** hashtable_delete ****************/
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item)) {

    if (ht != NULL) {
        int size = ht->number_of_slots;
        for (int i = 0; i < size; i++) {
            hashtable_delete_node(ht->hash_array[i], itemdelete);
        }

        mem_free(ht->hash_array); //free the array of pointers
        mem_free(ht); //finally free the hashtable itself
    }

    #ifdef MEMTEST
        mem_report(stdout, "End of set_delete");
    #endif
}


/**************** helper functions ****************/

hash_node_t* hashtable_new_node(const char* key, void* item, hash_node_t* next) {
    if (key != NULL && item != NULL) {
        hash_node_t* new_node = mem_malloc(sizeof(hash_node_t));
        new_node->key = key;
        new_node->item = item;
        new_node->next = next;
        return new_node;
    }
    return NULL;
}

//delete all nodes in the hash table at specific index
void hashtable_delete_node(hash_node_t *node, void (*itemdelete)(void* item)) {
    for (hash_node_t* curr = node; curr != NULL;) {
        hash_node_t* temp = curr->next;

        if (curr->item != NULL && itemdelete != NULL) {
            itemdelete(curr->item);
        }
        if (curr->key != NULL) {
            mem_free((char*) curr->key);
        }
        mem_free(curr);
        curr = temp;
    }
}
