# CS50 TSE QUERIER
## Design Spec

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and focus on the implementation-independent design decisions.

Here we focus on the core subset:

- User interface
- Inputs and Outputs
- Functional decomposition into modules
- Pseudo code (plain English-like language) for
logic/algorithmic flow
- Major data structures
- Testing plan

### User interface
As described in the [Requirements Spec](REQUIREMENTS.md), the querier's only interface
with the user is on the command-line; it must
always have three arguments.

```bash
    $ querier pageDirectory indexFileDirectory
```


## Inputs and Outputs
*Input:* The program accepts two command-line parameters:
- `pageDirectory`: a path to the directory produced by the crawler.
- `indexFilename`: a file created by the indexer, containing word-document frequency data.

## Functional decomposition into modules
We anticipate the following modules or functions:

1. **main**, which parses arguments and initializes other modules.
2. **querier**, which normalizes and validates query and provides search results.
3. **fuzzyquery**, for testing purposes that provides randome search queries.

And some helper modules that provide data structures:
1. **index_t** that contains the words and where it can be found in their documents.

## Pseudo code for logic/algorithmic flow
```bash
    parse the command line and validate parameters
    load the index from indexFilename
    loop:
        read a line from stdin
        normalize input to lowercase
        check for non-alphanumeric characters
        split line into individual words
        for each word:
            if word is "and" or "or":
                validate logic (cannot start, end, or repeat operators)
            else:
                lookup counters for the word in the index
                compute intersection or union with running result
        if result is NULL:
            print "No documents match."
        else:
            rank and print results by document score
    exit when EOF is reached
```
## Major data structures
- **index_t**: A hashtable mapping words to counters_t
- **counters_t**: A mapping of document ID to count (frequency of word)
- **max_score_t**: A struct for tracking the highest score per document
- **array of char* words[]**: For storing parsed query words

## Testing plan
1. Run the program with various invalid command-line arguments to test argument validation.
2. Use valid pageDirectory and indexFile, input well-formed queries and verify correct results.
3. Test queries with bad characters and confirm appropriate error handling.
4. Test edge cases: 
   - query with only one word,
   - queries starting or ending with AND/OR,
   - repeated operators,
   - mixed-case queries.
5. Use Valgrind to ensure no memory leaks.
6. Compare output with manually expected results.
