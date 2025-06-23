# CS50 CS50 INDEXER

### Overview
The `indexer` is a program that indexes crawled web documents at a specified
`pageDirectory`, retrieves each word in the webdocument counts the occurence
of each word and appends it to a `index_t` data structure. The data structure is saved to a file called `test.index`.

### Features
- builds indexes for each webpage documents
- normalizes each words and counts the occurence of words in each document

## Usage
The `indexer` program is executed from the command line with the following 
syntax

```bash
    ./indexer <pageDirectory> <indexFileName>
```
## Arguments
- `pageDirectory`: path to the directory that contains the crawled web documents
- `indexFileName`: path to the indexfile to save the index object

## Implementation
The `indexer` is a module implemented in `indexer.c` and uses the following key components

- **`parseArgs`**: Validates and parses command line arguments

- **`indexBuild`**: creates a new 'index' object, loops over document ID, and passes the webpage and docID to indexPage.

- **`indexPage`**: scans a webpage document to add its words to index, normalizes the words, and adds the words to the index.

## Files
- **`index.c`**: implements the functions in `index.h` that provides the interface for the `index_t` data structure.
- **`index.h`**: provides the interface for `index.c` to implements

- **`indexdir.c`**: implements the function in `indexdir.h` to rebuild index
object from a file into a new index_t
- **`indexdir.h`**: provides the interface for `indexdir.c` to implements.

- **`indexTest.c`**: a file that tests the index object file, by converting
the index object to an inverted index-data-structure, creates a new file and writes the inverted index to it.

## Assumptions
We assume that `commons` and `libcs50` libraries are compiled. We also assume the caller has crawled webpages and provided valid directory to the crawled files.

## Testing
To test indexer, we simply run this syntax:

### Memory Testing
```bash
    make valgrind
```

### Testing (index_building & index_rebuilding)
```bash
    make test
```

### NB:
`testing.out`: file that contains the output of testing.sh

`new_testing.index`: the inverted-index data structure located in `../data/index_files` directory

`test.index`: the file that contains the index data structure located in `../data/index_files` directory

## Author
Richmond Nartey Kwalah Tettey

CS50, 2025