#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "hashtable.h"
#include "counters.h"
#include "mem.h"
#include "file.h"


/**
 * index_load creates a new index_t structure from a saved index file
 * 
 * @param filename path to the index file to load
 * @return pointer to the newly created index_t structure, or NULL on failure
 */
index_t* index_load(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file '%s'\n", filename);
        return NULL;
    }

    // Create a new index
    index_t* index = index_create();
    if (index == NULL) {
        fclose(fp);
        return NULL;
    }

    // Read the index file line by line
    char* line;
    while ( (line = file_readLine(fp)) != NULL) {
        // Parse the line to extract the word and its counters
        
        // split off the word
        char* word = strtok(line, " \t\n");
        if (!word) {
            mem_free(line);
            continue;
        }

        // create your counters_t
        counters_t* ctrs = counters_new();
        if (!ctrs) {
            mem_free(line);
            index_delete(index);
            fclose(fp);
            return NULL;
        }

        // now pull the first docID
        char* token = strtok(NULL, " \t\n");
        if (token) {
            int docID = atoi(token);

            // next token is the count
            token = strtok(NULL, " \t\n");
            if (token) {
                int count = atoi(token);
                counters_set(ctrs, docID, count);
            }
        }

        // and then you can loop pulling subsequent pairs
        while ((token = strtok(NULL, " \t\n")) != NULL) {
            int docID = atoi(token);
            token = strtok(NULL, " \t\n");
            if (!token) break;
            int count = atoi(token);
            counters_set(ctrs, docID, count);
        }

        // finally insert into your index and free the line
        hashtable_insert(index->hashtable, word, ctrs);
        mem_free(line);
    }
    
    fclose(fp);
    return index;
}
