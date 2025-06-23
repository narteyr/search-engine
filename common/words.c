/**
 * @file words.c provides the implementation of functions by 'words.h'
 * 
 * @author: Richmond Nartey Tettey, CS50 Spring 2025
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char* convert_to_lowercase(char* word) {

    if (word == NULL) {
        return NULL;
    }

    // Convert the word to lowercase
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}

/**
 * Purpose: This function take a line of text and checks for
 * special characters
 * 
 * We return error message if the line contains special characters.
 * We return NULL if the line is empty
 * 
 * @param line is the line of text to be checked
 * @return true if the line is alphanumeric, false otherwise
 */

bool is_alpha_numeric(char* word) {
    if (word == NULL) {
        return false;
    }

    for (int i = 0; word[i] != '\0'; i++) {
        // Allow letters, digits, spaces, and tabs
        if (!isalpha(word[i]) && !isdigit(word[i]) && 
            !isspace(word[i]) && word[i] != '\t') {
            fprintf(stderr, "Error: Bad character '%c' in query.\n", word[i]);
            return false;
        }
    }
    return true;
}
