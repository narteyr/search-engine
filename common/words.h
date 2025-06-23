
/**
 * @file words.h provides the definition of functions implemented by 'words.c'
 *  to manipulate words
 * 
 * Author: Richmond Nartey Tettey, CS50 Spring 2025
 */

#ifndef WORDS_H
#define WORDS_H


/**
 * Purpose: This function convertes a word to lowercase and removes
 * 
 * we do:
 * We convert the word to lowercase
 * 
 * return:
 * a pointer to the normalized word
 * 
 * @param word is the word to be normalized
 */
char* convert_to_lowercase(char* word);


/**
 * Purpose: This function take a line of text and checks for
 * special characters
 * 
 * We return error message if the line contains special characters.
 * We return NULL if the line is empty
 * 
 * * @param line is the line of text to be checked
 * @return a pointer to the normalized line
 */
char* is_alpha_numeric(char* word);

#endif