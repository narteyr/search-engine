
/**
 * 'pagedir.c' implements the functions for managing a page directory.
 * refer to header file 'pagedir.h' for more information.
 * Author: Richmond Nartey Kwalah Tettey
 */

#include <stdio.h>
#include "pagedir.h"
#include "stdbool.h"
#include "webpage.h"

bool pagedir_init(const char* pageDirectory) {
    // Initialize the page directory with the given path
    if (pageDirectory == NULL) {
        fprintf(stderr, "Error: Page directory path is NULL.\n");
        return false;
    }

    // Here you would typically set up the page directory structure
    // For example, create a directory if it doesn't exist, etc.
    // This is a placeholder for actual implementation.
    char filepath[200];
    snprintf(filepath, sizeof(filepath), "%s/.crawler",pageDirectory);

    FILE *fp = fopen(filepath, "w");

    if (fp == NULL) {
        return false;
    }

    fclose(fp);
    return true;
}

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {

    if (page != NULL && pageDirectory != NULL && docID > 0) {

        char filepath[200];
        snprintf(filepath, sizeof(filepath), "%s/%d", pageDirectory, docID);
        FILE *fp = fopen(filepath, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error: Could not open file %s for writing.\n", filepath);
            return;
        }

        //write the page content to the file in this format
        /**
         * first line: URL
         * second linge: depth
         * third line: HTML content
         */

        fprintf(fp, "%s\n", webpage_getURL(page));
        fprintf(fp, "%d\n", webpage_getDepth(page));
        fprintf(fp, "%s\n", webpage_getHTML(page));
        fclose(fp);
    }
}
