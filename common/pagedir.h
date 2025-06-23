/**
 * pagedir.h - header file for page directory management
 *
 * This file provides functions to initialize new page directory,
 * and save new webpages to the directory provided
 *
 * Author: Richmond Nartey Kwalah, CS50 May 2025
 */

#ifndef PAGEDIR_H
#define PAGEDIR_H

#include <stdbool.h>
#include "webpage.h"

/** FUNCTION PROTOTYPES **/

/**
 * pagedir_init - Initializes a new page directory.
 *
 * @pageDirectory - The path to the page directory to be initialized.
 *
 * Returns: true if the directory was successfully initialized, false otherwise.
 */
bool pagedir_init(const char* pageDirectory);


/**
 * pagedir_save - Saves a webpage to the page directory.
 *
 * @page: The webpage to be saved.
 * @pageDirectory - The path to the page directory.
 * @docID - The document ID of the webpage.
 *
 * Returns: void
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);


#endif
