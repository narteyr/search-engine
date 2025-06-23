/**
 * @file main.c is the main file for the querier program.
 * 
 * Author: Richmond Nartey Tettey, CS50 Spring 2025
 */

#include <stdio.h>
#include "querier.h"
#include "indexdir.h"
#include "mem.h"
#include "unistd.h"

// function prototype
int fileno(FILE* stream);
static void prompt(void);  

int main(int argc, char* argv[]){

    char* pageDirectory;
    char* indexFileName;

    parseArgs(argc, argv, &pageDirectory, &indexFileName);

    fprintf(stdin, "Page Directory: %s\n", pageDirectory);
    fprintf(stdin, "Index File Name: %s\n", indexFileName);


    index_t* index = index_load(indexFileName);
    if (index == NULL) {
        fprintf(stderr, "Error: Could not load index from %s\n", indexFileName);
        return 1;
    }    

    char* query = NULL;
    while (true) {
        prompt();
        query = file_readLine(stdin);
        if (query == NULL || query[0] == '\0') {
            printf("\n");
            break;
        }
        // Process the query
        processQuery(index, query,pageDirectory,stdout);

        mem_free(query);
    }

    index_delete(index);
    return 0;
}

static void prompt(void){
    if(isatty(fileno(stdin))) printf("Query? ");
}