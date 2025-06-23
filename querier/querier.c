/**
 * @file querier.c implements the functions in the querier.h file
 * 
 * Author: Richmond Nartey Tettey, CS50 Spring 2025
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "index.h"
#include "counters.h"
#include "mem.h"
#include "querier.h"
#include "file.h"
#include "words.h"
#include "string.h"



/**
 * Helper function to pass data through counters_t iterate
 */

typedef struct{
    counters_t* result;
    counters_t* b;
} intersect_data_t;

typedef struct{
    int key;
    int count;
} max_score_t;

/**
 * Purpose: This Iterator function takes a key and count and
 * 
 * we do:
 *  We check if the key is in the counters_t data structure
 *  We check if the count is greater than 0
 *  We check if the count is less than the count in the second counters_t
 */
static void intersect_helper(void* arg, const int key, const int count);

/**
 * Purpose: This Iterator function joins two counters_t data structures
 */
static void union_helper(void* arg, const int key, const int count);

/**
 * Purpose: An Iterator function to count number of items in counters_t* struct
 */
 void count_items(void* total,const int key, const int count);

/**
 * Purpose: An Iterator function that finds the max count in the counters_t* struct
 */
void find_max_score(void* arg, const int key, int count);

/**
 * Purpose: An Iterator function that gets the id for count
 */
void find_id_by_count(void* arg, const int key, int count);

void parseArgs(const int argc, char* argv[], 
    char** pageDirectory, char** indexFileName){
    // Check if the number of arguments is correct
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pageDirectory> <indexFileName>\n", argv[0]);
        exit(1);
    }

    char buffer[100];

    // Check if the pageDirectory is valid directory containing the .crawler file
    snprintf(buffer,sizeof(buffer), "%s/%s", argv[1], ".crawler");

    FILE *fp = fopen(buffer, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: %s does not exist\n", buffer);
        exit(1);
    }

    // Check if the indexFileName is a valid file
    FILE *fp2 = fopen(argv[2], "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Error: %s does not exist\n", argv[2]);
        fclose(fp);
        exit(1);
    }

    *pageDirectory = argv[1];
    *indexFileName = argv[2];

    // Close the file pointers
    fclose(fp);
    fclose(fp2);
}


void processQuery(index_t *index, char* query, char* pageDirectory, FILE *fp){
    convert_to_lowercase(query);
    fprintf(fp, "Query: %s\n", query);

    is_alpha_numeric(query);
    char* words[200]; // Array to store the words
    int count = split_line(query, words);
    counters_t* final_result = query_express(words,count,index);

    //ranking results
    if (final_result == NULL){
        fprintf(fp,"No documents match.\n");
    }else{
        rank_result(final_result,pageDirectory,fp);
    }
    counters_delete(final_result);
}


counters_t* query_express(char* words[], int word_count, index_t* index){
    counters_t* result = NULL;
    counters_t* temp = NULL;
    bool is_and = false;
    bool is_or = false;

    for (int i = 0; i < word_count; i++){
        char* word = words[i];

        if (strcmp(word, "and") == 0) {
            // Error if 'and' is the last token
            if (is_and) {
                if (temp) counters_delete(temp);
                fprintf(stderr, "bad query: cannot have two adjacent and \n");
                return NULL;
            }

            if (i == word_count - 1 || i == 0) {
                fprintf(stderr, "bad query: 'and' cannot start or end the query\n");
                return NULL;
            }

            // Skip 'and' if no previous matches (temp NULL) or at start
            if (temp == NULL) {
                continue;
            }

            is_and = true;
            continue;
        }
        else if (strcmp(word, "or") == 0) {
            // Skip 'or' if no previous matches (temp NULL) or at start
            if (is_or) {
                fprintf(stderr, "bad query: cannot have two adjacent 'or' in query\n");
                return NULL;
            }

            if (i == 0) {
                fprintf(stderr, "bad query: 'or' cannot start the query\n");
                return NULL;
            }

            if (temp == NULL ) {
                continue;
            }
            // Error if 'or' is the last token
            if (i == word_count - 1) {
                fprintf(stderr, "bad query: 'or' cannot end the query\n");
                return NULL;
            }
            // Union current temp into result
            if (result == NULL) {
                result = counters_new();
                if (result == NULL) return NULL;
            }
            union_counters(temp, result);
            counters_delete(temp);
            temp = NULL;
            is_or = true;
            continue;
        }

        // handle the word
        counters_t* word_counters = index_find(index,word);
        if (word_counters == NULL) {
            if (temp != NULL) {
                counters_delete(temp);
                temp = NULL;
            }
            continue;
        }

        if (is_and || temp == NULL){
            //start new AND sequence or continue existing one
            if (temp == NULL) {
                temp = counters_new();
                if (temp == NULL) {
                    if (result != NULL) counters_delete(result);
                    return NULL;
                }
                counters_iterate(word_counters, temp, union_helper);
            } else{
                counters_t* new_temp = intersect_counters(temp, word_counters);
                counters_delete(temp);
                temp = new_temp;
                if (temp == NULL) break;
            }
            is_and = false;

        }else{
            // Implicit AND
            counters_t* new_temp = intersect_counters(temp, word_counters);
            counters_delete(temp);
            temp = new_temp;
            if (temp == NULL) break;
            is_or = false;
        }
    }

    // Handle the last temp
    if (temp != NULL) {
        if (result == NULL) {
            result = temp;
        }else{
            union_counters(temp, result);
            counters_delete(temp);
        }
    }
    return result;
}




int split_line(char* line, char* words[]){
    
    if (line == NULL || words == NULL) return 0;

    int count = 0; // Number of words found
    char* ptrs = line; // Pointer to the current position in the line

    while (*ptrs != '\0'){

        while (isspace(*ptrs)) ptrs++; // Skip leading whitespace
        if (*ptrs == '\0') break; // End of line

        words[count++] = ptrs;
        while(!isspace(*ptrs) && *ptrs != '\0') ptrs++; // Find end of word

        if (*ptrs != '\0'){
            *ptrs = '\0';
            ptrs++;
        }
    }

    if (count == 0) {
        fprintf(stderr, "Error: No words found in query\n");
    }
    return count;
}


/**
 * Creates a new counters structure that is the intersection of two counters
 * @param a first counters set (caller retains ownership)
 * @param b second counters set (caller retains ownership)
 * @return new counters set with keys present in both a and b, with min counts
 *         NULL if either input is NULL or memory allocation fails
 * @note Caller is responsible for freeing the returned counters_t
 */
counters_t* intersect_counters(counters_t* a, counters_t* b) {
    // Validate inputs
    if (a == NULL || b == NULL) {
        return NULL;
    }

    // Allocate result counter
    counters_t* result = counters_new();
    if (result == NULL) {
        return NULL;
    }

    // Create helper structure
    intersect_data_t data = {result, b};

    // Perform intersection
    counters_iterate(a, &data, intersect_helper);
    
    return result;
}

/**
 * Helper function that performs intersection for each key-count pair
 * @param arg The intersect_data_t containing both counters sets
 * @param key The current key being processed
 * @param count_a The count from the first counter set
 */
static void intersect_helper(void* arg, const int key, const int count_a) {
    if (arg == NULL) return;
    
    intersect_data_t* data = arg;
    
    int count_b = counters_get(data->b, key);
    if (count_b > 0) {
        int min_count = count_a < count_b ? count_a : count_b;
        counters_set(data->result, key, min_count);
    }
}


/**
 * Creates a new counters structure that is the union of two counters
 * @param temp first counters set (caller retains ownership)
 * @param result second counters set (caller retains ownership)
 * @return new counters set with keys present in either a or b, with max counts
 *         NULL if either input is NULL or memory allocation fails
 * @note Caller is responsible for freeing the returned counters_t
 */
counters_t* union_counters(counters_t* temp, counters_t* result){
   if (temp == NULL || result == NULL) return NULL;

    // Handle case where one counter is NULL
    counters_iterate(temp, result, union_helper);

    return result;
}

/**
 * Helper function to pass data through counters_t iterate
 * @param arg is the result counters_t
 * @param key is the key to be added
 * @param count is the count to be added
 */
static void union_helper(void* arg, const int key, const int count){
    if (arg == NULL) return;
    counters_t* result = (counters_t*) arg;
    int old_count = counters_get(result, key);
    counters_set(result, key, old_count + count);
}



void rank_result(counters_t* results, const char* pageDirectory, FILE* fp){
    if (results == NULL || pageDirectory == NULL || fp == NULL) return;
    //output the number of matches in this format: Matches <no> documents ranked:
    int count_doc = 0;
    counters_iterate(results,(void*) &count_doc,count_items);
    fprintf(fp,"Matches %d documents (ranked):\n", count_doc);


    for(int i = 0; i < count_doc; i++){
        //find document with the highest score
        int max_score = 0;
        counters_iterate(results, (void*)&max_score,find_max_score);
        if (max_score == 0) break;

        max_score_t* curr_entry = mem_malloc(sizeof(max_score_t));
        curr_entry->count = max_score;
        counters_iterate(results, curr_entry, find_id_by_count);
        counters_set(results,curr_entry->key,0);

        //get the url from file at that docID
        char filename[256];
        sprintf(filename, "%s/%d",pageDirectory,curr_entry->key);
        FILE *file = fopen(filename,"r");

        char* url = file_readLine(file);
        fprintf(fp,"score\t%d doc\t%d: %s\n",curr_entry->count,curr_entry->key,url);

        mem_free(curr_entry);
        mem_free(url);
        fclose(file);
    }
    fprintf(fp,"\n");
}


void find_id_by_count(void* arg, const int key, int count){
    
    if (count == ((max_score_t*)arg)->count){
        //we open and read the url to get the docID
        ((max_score_t*)arg)->key = key;
    }
}

void find_max_score(void* arg, const int key, int count){
    if (count > (*(int*)arg)){
        (*(int*)arg) = count;
    }
}

void count_items(void* total,const int key, const int count){
    (*(int*)total)++;
}