/**
 * The 'indexer.h' provides the definitions of the functions
 * builds an in-memory index from webpage files it finds,
 * and scans a webpage document to add its words to index.
 *
 * Author: Richmond Nartey kwalah Tettey, CS50 2025
 */



#ifndef INDEXER_H
#define INDEXER_H

#include "index.h"
#include "stdbool.h"
#include "webpage.h"

//$ indexer ../data/letters ../data/letters.index


/**
 *
 * Purpose: parses the command line arguments
 *
 * Caller:
 *    provides valid arguments for indexing
 *    responsible for freeing all allocated arguments
 *
 * Usage:
 *  indexer <directory> <index file>
 * we return:
 *      true if the arguments are valid or else false
 * @param argc
 * @param argv
 * @param pageDirectory valid pointer to the directory path
 * @param pageFileName valid pointer to the index file name
 * @return
 */
bool parseArgs(int argc, char* argv[], char** pageDirectory, char** pageFileName);



/**
 * Purpose: creates a new 'index' object
 *          loops over document ID numbers,
 *          loads a webpage from the document file
 *          and passes the webpage and docID to indexPage
 * Caller:
 *        provides a valid directory path that contains .crawler
 *        file
 *        provides a valid index file path
 * We do:
 *  save the index object to a file
 *  free the index object
 *
 *  We return:
 *      true if index was built successfully or false
 *
 * @param pageDirectory
 */
bool indexBuild(char* pageDirectory, char* fileName);


/**
 * Purpose: scans a webpage document to add its words to index
 *          and normalizes the words
 *          and adds the words to the index
 *          
 * Caller:
 *  provides valid index object, webpage and docID (greater than 0)
 *  responsible for freeing the index_object
 *
 *  We return:
 *      nothing
 *
 * 
 * @param index
 * @param webpage
 * @param docID
 */
void indexPage(index_t* index, webpage_t* webpage, int docID);
#endif
