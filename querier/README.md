# CS50 Lab4: Querier

## Overview
The `querier` is a program that recieves a query
from user and searches and returns the crawled documents similar to the query provided.


## Features
- normalizes query and converts it to lowercase
- finds results that matches the expressions (AND, OR) provided in the query
- ranks the results based on their relevance
- builds a search result and returns the response to the user

## Usage
The `querier program is executed from the command line with the following syntax:

```bash
./querier <pageDirectory> <indexFileName>
```

### Arguments:
1. **`pageDirectory`**: The directory where crawled pages will be saved. Must be writable and initialized using `pagedir_init`.
2. **`indexFileName`**: A valid directory to the index file

### Example:
```bash
./querier ../data ../data/index_files/test.index
```
This command builds the `index_t*` struct with the index file, takes inputs from the users and
returns similar web documents that contain the keyword.

### Implementation

The `querier` module is implemented in `querier.c` and uses the following key components:

- **`parseArgs`**: Validates and parses command-line arguments.
- **`queryProcess`**: searchs each keyword in query for any document match
- **`rank_results`**: ranks the results after processing query


### Key Data Structures:
- **`index_t`**: use to manage indexes that contains words and docIDs

### Workflow
1. Initialize the `index_t` and load the index from the index file.
2. Validate and normalize the user's query
3. process each key word in query
4. fetch related documents and save the url
5. repeat until key word is check, then return a ranked results

## Files
- **`querier.c`**: Implements the main functionality of the querier.

- **`querier.h`**: provides the function prototypes and documentation on how the
functions in `querier.c` can be used.

- **`main.c`**: main function that calls the functions in `querier.c` to process queries.

- **`fuzz.sh`**: bash file to run the `fuzzquery.c` for testing querier.

- **`fuzzquery.c`**: generates a series of random queries for testing querier.

- **`testing.out`**: contains the result of running `testing.sh`.

- **`fuzz.out`**: contains the result of running `fuzz.sh`.


## Compilation
To compile the `querier`, use the provided `Makefile` in the querier directory:
```bash
  make all
```

## Testing

1. To test the program, run the following command:
    ```bash
    make valgrind
    ```

2. A sampling of tests that should be run:
    ```bash
    make test
    ```

3. To test with "Query Fuzz Testing" that generations random queries and pipes it to the query you can run this command:
    ```bash
    make fuzz
    ```

## Notes
- Ensure the `pageDirectory` exists and is writable before running the program.

- Memory management is handled carefully to avoid leaks, as verified by Valgrind.

## Assumptions
We assume `commons` library and `cs50lib` has been compiled before running the querier

We assume there is a valid directory to the crawled files and a valid index file.

#### Author: 
Richmond Nartey Tettey,

CS50 Spring 2025