/**
 * @file indexdir.h provides the definition of the IndexDir class.
 * To rebuild index object from a file into a new index_t
 *
 *  Author: Richmond Nartey Kwalah Tettey
 */


#ifndef INDEXDIR_H
#define INDEXDIR_H

#include "index.h"
#include "hashtable.h"
#include "counters.h"
#include "stdbool.h"
#include "mem.h"
#include "file.h"
#include "string.h"
/**
 *  Rebuild index from a file into a new index_t
 *  The caller must free the index after use.
 *
 * @param filename - the path to the index file
 * @return pointer to the rebuilt index or NULL
 */
index_t* index_load(const char* filename);

#endif
