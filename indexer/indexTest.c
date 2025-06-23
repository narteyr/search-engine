/***
 * @indexTest.c is a file that tests the index object file, by converting
 * the index object to an inverted index-data-structure, creates a new file
 * and writes the inverted index to it.
 *
 * Author: Richmond Nartey Kwalah Tettey
 */

//./indextest oldIndexFilename newIndexFilename

#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include "indexdir.h"
#include "mem.h"

/** ==== local functions ==== **/
void parseArgs(int argc, char* oldIndexFilename, char* newIndexFilename);

int main(int argc, char* argv[]) {
    char* oldIndexFilename = argv[1];
    char* newIndexFilename = argv[2];
    parseArgs(argc, oldIndexFilename, newIndexFilename);
    index_t* index = index_load(oldIndexFilename);
    if (index == NULL) {
        printf("Error: Could not load index from file %s\n", oldIndexFilename);
        return 1;
    }
    index_save(index, newIndexFilename);
    index_delete(index);
    return 0;
}


/**
 *  Purpose: This function parses the command line arguments and checks if the
 *
 *  We return:
 *      nothing
 * @param argc valid integer value that represents the number of command line arguments
 * @param oldIndexFilename  valid pointer to a string that represents the old index file name
 * @param newIndexFilename  valid pointer to a string that represents the new index file name
 */
void parseArgs(int argc, char* oldIndexFilename, char* newIndexFilename) {
    if (argc == 3) {

        FILE* oldIndexFile = fopen(oldIndexFilename, "r");
        if (oldIndexFile == NULL) {
            printf("Error: Could not open old index file %s\n", oldIndexFilename);
            return;
        }

        FILE* newIndexFile = fopen(newIndexFilename, "w");
        if (newIndexFile == NULL) {
            printf("Error: Could not open new index file %s\n", newIndexFilename);
            return;
        }
        fclose(oldIndexFile);
        fclose(newIndexFile);
        return;
    }
    printf("Usage: ./indexTest <oldIndexFilename> <newIndexFilename>\n");;
}

