/**
 * @file main.c is the main terminal that calls
 * indexer.c to build a new index object
 *
 * Author: Richmond Nartey Tettey, CS50 2025
 *
 */


// Project: indexer

#include <stdio.h>
#include "indexer.h"


int main(int argc, char *argv[]) {
    char* pageDirectory = NULL;
    char* fileName = NULL;

    if (!parseArgs(argc, argv, &pageDirectory, &fileName)) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }

    indexBuild(pageDirectory,fileName);
    return 0;
}

