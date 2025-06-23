
/**
 *  @file 'querier.h' is a standard header file that contains the functional
 * prototypes for the 'querier.c' file to implement. This functions are implemented
 * to query the indexer and return the results based on the user input.
 * 
 *  Author: Richmond Nartey Tettey, CS50 Spring 2025
 * 
 * 
 */

#ifndef QUERY_H
#define QUERY_H

#include <stdio.h>
#include "index.h"
#include "counters.h"


/**
 * Purpose: This function takes a query string and an index_t data structure
 * and returns a list of document IDs that match the query.
 * 
 * Caller:
 *    caller provides a valid index_t data structure and a query string
 * 
 * We do:
 *   validate to see if the pageDirectory contains the .crawler file
 *   validate to see if the index file exists
 *   we print to error message if the file does not exist
 *  
 * @param index is the index_t data structure to search
 * @param query is the query string to search for
 * @return a list of document IDs that match the query
 */

void parseArgs(const int argc, char* argv[], 
    char** pageDirectory, char** indexFileName);


/**
 * Purpose: This function takes a query string and an index_t data structure
 * and returns a list of document IDs that match the query.
 * 
 * Caller:
 *    caller provides a valid index_t data structure and a query string
 *    caller is responsible for freeing the memory allocated to the index_t
 * 
 * We do:
 *   validate to see if the pageDirectory contains the .crawler file
 *   validate to see if the index file exists
 *   we print to valid file stream if the file exists
 *   we print to error message if the file does not exist
 *  
 * @param index is the index_t data structure to search
 * @param pageDirectory is the directory containing the pages
 * @param fp is the file pointer to the ouput file
 * @param pageDirectory is the path to the directory that contains crawled files
 * @param fp is the output stream to print out the result of the query
 */
void processQuery(index_t *index, char* query, char* pageDirectory, FILE *fp);


/**
 * Purpose: This functions takes a line of text and splits it into words
 * based on whitespace and punctuation. It returns the number of words
 * found and stores the words in the provided array.
 * 
 * Caller:
 *   caller provides a line of text and a valid pointer to array of strings to store the words
 * 
 * We do:
 *  we split the line into words based on whitespace and punctuation
 *  we store the words in the provided array
 * 
 * @param line is the line of text to split
 * @param words is the array of strings to store the words
 * @return the number of words found
 */
int split_line(char* line, char* words[]);


/**
 * Purpose: This function process query expression according to
 * precedence rules, especially for AND and OR operators.
 * 
 * Caller:
 *   caller provides a valid index_t data structure and a query string
 *   caller is responsible for freeing the memory allocated to the index_t
 * 
 * We do:
 *  We Implement AND(intersection) and OR(union) operations
 *  We return a valid and combined counters structure with scores
 */
counters_t* query_express(char* words[], int word_count,
    index_t* index);


/**
 * Purpose: This function takes two counters_t data structures and returns
 * a new counters_t data structure that contains the intersection of the two.
 * 
 * Caller:
 *   caller provides two valid counters_t data structures
 *      caller is responsible for freeing the memory allocated to the counters_t
 * 
 * We do:
 *  
 *  We Implement AND(intersection) operations
 *  We add similar counts from first pointer of counters_t to second pointer
 *  Thus: intersect(a, b) => a => a * b
 *  We return a valid and combined counters structure with scores
 * 
 * @param a is the first counters_t data structure
 * @param b is the second counters_t data structure
 */
counters_t* intersect_counters(counters_t* a, counters_t* b);


/**
 * Purpose: This function takes two counters_t data structures and returns
 * a new counters_t data structure that contains the union of the two.
 * 
 * Caller:
 *   caller provides two valid counters_t data structures
 *   caller is responsible for freeing the memory allocated to the counters_t
 * 
 * We do:
 *  
 *  We Implement OR(union) operations
 *  We add similar counts from first pointer of counters_t to second pointer
 *  Thus: union(a, b) => a => a + b
 *  We return a valid and combined counters structure with scores
 * 
 * @param a is the first counters_t data structure
 * @param b is the second counters_t data structure
 */
counters_t* union_counters(counters_t* a, counters_t* b);


/**
 * Purpose: This function takes a counters_t data structure and a file pointer
 * and prints the document IDs and their scores to the file.
 * 
 * Caller:
 *   caller provides a valid counters_t data structure and a file pointer
 * 
 * We do:
 *  We rank the results by using slection sort algorithm in descending order
 *  We use sort via counters_iterate
 *  We print the document IDs and their scores to the file
 * 
 * @param counters is the counters_t data structure to print
 * @param fp is the file pointer to print to
 */
void rank_result(counters_t* results, const char* pageDirectory, FILE* fp);

#endif