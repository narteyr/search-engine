
/**
 * 'crawler.c' - A simple web crawler
 *
 * Author: Richmond Nartey Kwalah Tettey, CS50  May 2025
 *
 * FYI: refer to the README.md file for more information
 * and 'crawler.h' for the function prototypes usage.
 */

#include <stdio.h>
#include <stdlib.h>
#include "crawler.h"

#include <string.h>

#include "webpage.h"
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"
#include "mem.h"
#include "stdbool.h"

/** local variables  **/

int INITIAL_HASHTABLE_SIZE = 200;

void webpage_print(FILE* fp, void* item);
void delete_url(void* item);

int main(const int argc, char* argv[]) {
    char* seedURL = NULL;
    char* pageDirectory = NULL;
    int maxDepth = 0;

    // Parse command line arguments
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);
    return 0;
}


/** =========== Functional prototypes ============= **/

/** parseArgs **/
// refer to 'crawler.h' for more descriptions
static void parseArgs(const int argc, char * argv[],
                      char** seedURL , char** pageDirectory, int* maxDepth) {
    //usage: crawler <seedURL> <pageDirectory> <maxDepth>
    //./crawler seedURL pageDirectory maxDepth
    if (argc == 4) {
        char* url = normalizeURL(argv[1]);
        if (url == NULL) {
            fprintf(stderr, "Error: Invalid seedURL\n");
            exit(1);
        }
        *seedURL = url;
        int depth = 0;

        if (sscanf(argv[3], "%d",&depth) == 1) {
            if (depth >= 0) {
                *maxDepth = depth;
            } else {
                fprintf(stderr, "Error: maxDepth must be a non-negative integer\n");
                exit(1);
            }
        }

        // Check if the pageDirectory is valid
        char* pageDir = argv[2];
        if (pageDir == NULL) {
            fprintf(stderr, "Error: Invalid pageDirectory\n");
            exit(1);
        }

        const bool isValidDirectory = pagedir_init(pageDir);
        if (isValidDirectory) {
            *pageDirectory = pageDir;;
        } else {
            fprintf(stderr, "Error: Invalid pageDirectory\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Usage crawler: ./crawler <seedURL> <pageDirectory> <maxDepth> \n");
        exit(1);
    }
}


/** pageScan **/
// while there is another URL in the page
// if
// that URL is Internal,
//    insert the webpage into the hashtable
// if
// that succeeded,
//        create a webpage_t
// for
// it
//        insert the webpage into the
// bag
// free the URL
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {

    if (page != NULL && pagesToCrawl != NULL && pagesSeen != NULL) {
        // Check if the page is valid
        fprintf(stdout,"%d Scanning: %s\n", webpage_getDepth(page), webpage_getURL(page));
        int pos = 0;
        char* result;

        int currDepth = webpage_getDepth(page);

        while ((result = webpage_getNextURL(page, &pos)) != NULL) {
            char* url = normalizeURL(result);
            if (url == NULL) {
                fprintf(stderr, "Error: Invalid URL\n");
                mem_free(result);
                continue;
            }

            fprintf(stdout, "%d Found: %s\n", webpage_getDepth(page), webpage_getURL(page));

            // Check if the URL is internal
            if (isInternalURL(url)) {
                char* url_copy = mem_malloc(sizeof(char) * (strlen(url) + 1));
                strcpy(url_copy, url);

                // Check if the URL has already been seen
                if (hashtable_insert(pagesSeen, url,url)) {
                    // Create a new webpage_t for the URL

                    int nextDepth = currDepth + 1;
                    webpage_t* newPage = webpage_new(url_copy, nextDepth, NULL);
                    if (newPage != NULL) {
                        // Insert the webpage into the bag
                        bag_insert(pagesToCrawl, newPage);
                    }
                }else {
                    fprintf(stdout, "%d  IgnDupl: %s \n", webpage_getDepth(page), url);
                    mem_free(url_copy);
                }
            }else {
                fprintf(stdout, "%d  IgnExtrn: %s \n", webpage_getDepth(page), url);
            }
            mem_free(url);
            mem_free(result);
        }

    }
}

/** crawl **/
// refer to 'crawler.h' for more descriptions

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) {
    int docID = 0;
    if (seedURL != NULL && pageDirectory != NULL) {

        hashtable_t* new_hashtable = hashtable_new(INITIAL_HASHTABLE_SIZE);
        if (new_hashtable == NULL) {
            fprintf(stderr, "Error: Failed to create hashtable\n");
            exit(1);
        }
        bag_t* pagesToCrawl = bag_new();
        if (pagesToCrawl == NULL) {
            fprintf(stderr, "Error: Failed to create bag\n");
            hashtable_delete(new_hashtable, delete_url);
            exit(1);
        }

        //initialize the bag and add a webpage representing the seedURL at depth 0
        webpage_t* seedPage = webpage_new(seedURL, 0, NULL);
        if (seedPage == NULL) {
            fprintf(stderr, "Error: Failed to create seed webpage\n");
            bag_delete(pagesToCrawl, NULL);
            hashtable_delete(new_hashtable, NULL);
            exit(1);
        }

        bag_insert(pagesToCrawl, seedPage);


        webpage_t* page;
        while ( (page = bag_extract(pagesToCrawl)) != NULL) {
            const bool fetch_success =  webpage_fetch(page);

            if (fetch_success) {
                fprintf(stdout, "%d  Fetched: %s\n", webpage_getDepth(page), webpage_getURL(page));
                pagedir_save(page,pageDirectory, ++docID);
                if (webpage_getDepth(page) < maxDepth) {
                    pageScan(page, pagesToCrawl, new_hashtable);
                }
            }else {
                printf("No page found\n");
            }

            webpage_delete(page);
        }

        bag_delete(pagesToCrawl,NULL);
        hashtable_delete(new_hashtable, NULL);
    }
}

//webpage print
void webpage_print(FILE* fp, void* item) {
    if (item != NULL) {
        fprintf(fp, "URL: %s\n", webpage_getURL(item));
    }
}

void delete_url(void* item) {
    if (item != NULL) {
        mem_free(item);
    }
}
