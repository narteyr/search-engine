/**
 * 'indexer.c' - main function to index webpages, build
 * and creat an index file
 *
 * Author: Richmond Nartey Kwalah, CS50 2025
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "index.h"
#include "hashtable.h"
#include "indexer.h"
#include "file.h"
#include "mem.h"
#include "webpage.h"

/** ====== FUNCTIONAL PROTOTYPES ====== **/
static char* normalizeWord(char* word);

/** ==== validate and parse args === **/
//refer to 'indexer.h' for more description

bool parseArgs(int argc, char* argv[], char** pageDirectory, char** fileName) {
    if (argc == 3 && argv != NULL) {

        // validate that pageDirectory contains the .crawler file
        char buffer[255];
        snprintf(buffer, sizeof(buffer), "%s/.crawler", argv[1]);

        FILE *fp = fopen(buffer, "r");
        if (fp == NULL) {
            // not a valid crawler directory
            fprintf(stderr, "invalid crawler directory\n");
            return false;
        }
        fclose(fp);

        // check if fileName exists inside the pageDirectory
        char filePath[255];
        snprintf(filePath, sizeof(filePath), "%s", argv[2]);
        fp = fopen(filePath, "r");
        if (fp == NULL) {
            //file does not exist in directory
            fprintf(stderr, "file does not exist in directory\n");
            return false;
        }
        fclose(fp);

        // if both checks pass, assign values
        *pageDirectory = argv[1];
        *fileName = argv[2];
        return true;
    }
    fprintf(stderr, "Usage: ./indexer <pageDirectory> <fileName>\n");
    return false;
}

/** ====== indexBuild ====== **/
//refer to 'indexer.h' for more description
bool indexBuild(char* pageDirectory, char* fileName) {
    if (pageDirectory == NULL || fileName == NULL) return false;

    index_t* index = index_create();
    if (index == NULL) return false;

    int currID = 1;
    FILE* fp;
    char buffer[255];

    while (true) {
        //build the path for document currID
        snprintf(buffer, sizeof(buffer), "%s/%d", pageDirectory,currID);
        fp = fopen(buffer, "r");
        if (!fp) break; //no more documents
        
        //check if the file is empty
        //skip the first two lines in each webpage(metadata)
        char* url = file_readLine(fp);
        webpage_t* ne_webpage = webpage_new(url, 0, NULL);
        bool webpage_success = webpage_fetch(ne_webpage);
        if (!webpage_success) {
            fprintf(stderr, "webpage unsuccessfully fetched\n");
            return false;
        }
        indexPage(index, ne_webpage, currID);

        webpage_delete(ne_webpage);
        fclose(fp);
        currID++;
    }
    // close the index
    index_save(index, fileName);
    index_delete(index);
    return true;
}

/** ====== indexPage ====== **/
//refer to 'indexer.h' for more description
void indexPage(index_t* index, webpage_t* webpage, int docID) {
    int pos = 0;
    char* result;
    while ((result = webpage_getNextWord(webpage, &pos)) != NULL) {

        if (strlen(result) >= 3) {
            char* normalized_word = normalizeWord(result);
            if (normalized_word != NULL) {
                // add the normalized word to the index
                if (!index_insert(index, normalized_word, docID)) {
                    fprintf(stderr, "index_insert failed\n");
                    mem_free(normalized_word);
                    return;
                }
                mem_free(normalized_word);
            }
        }
        mem_free(result);
    }
}


/** === normalizeWord === **/
/**
 * Purpose: converts every character in 'word' to lowercase
 *
 * Caller:
 *  provides valid pointer to word
 *  responsible for freeing the word
 *
 * We do:
 *    convert every character in 'word' to lowercase
 *    allocated memory for the new word
 *    returns the new word
 *
 * We return:
 *      we return NULL if pointer is invalid, or
 *      failed to allocate memory, or unable to convert
 * @param word
 * @return normalized word
 */
static char* normalizeWord(char* word) {
    if (word == NULL) return NULL;

    // convert to lowercase
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }

    // remove punctuation
    char* result = mem_malloc(strlen(word) + 1);
    int j = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i]) || isdigit(word[i])) {
            result[j++] = word[i];
        }
    }
    result[j] = '\0';
    return result;
}
