# CS50 TSE Querier 

## Implementation Spec
In this document we reference [Requirements Specifications](REQUIREMENTS.md) and [Design Specification](DESIGN.md) and focus on the implementation-specific decisions. The `implementation spec` includes relevant subsets of the `querier` such as:

- Data structures
- Control flow: pseudo code for overall flow, and for each of the functions
- Detailed function prototypes and their parameters
- Error handling and recovery
- Testing plan

## Data Structures

The Querier uses these primary data structures:

1. **counters_t** (from libcs50)
   - Used to track document IDs and their associated scores
   - Key: document ID (int)
   - Value: score (int)

2. **index_t** (from common library)
   - Inverted index mapping words to (docID, count) pairs
   - Used to look up word occurrences

3. **hashtable_t** (from libcs50)
   - Underlying structure for the index
   - Key: normalized word (string)
   - Value: counters_t of document IDs and counts

## Control Flow

The Querier is implemented in `querier.c` with these key functions:

### Main Functions

#### main
The `main` function simply calls `parseArgs` and `query`, then exits zero.


### Helper Functions

#### split_line
The `split_line` function tokenizes input file into words array, handles whitespaces and returns count of words found. 
The parameters passed are:
- `char* line`: pointer to validate query

- `char* words`: valid pointer array that stores pointers to the words found

```c
   static int split_line(char* line, char* words[])
```


#### query_express
1. The `query_express` processes query expression according to precedence rules
2. Implements AND (intersection) and OR (union) operations
3. Returns combined counters structure with scores

```c
   static counters_t* query_express(char* words[], int word_count, index_t* index)
```

#### intersect_counters
1. Computes intersection of two counters
2. for each docID, takes minimum count
3. Returns a new counters structure with results

- `counters_t* a`: valid pointer to counters_t struct for a word

- `counters_t* b`: valid pointer to counters_t struct for a word

```c
   static counters_t* intersect_counters(counters_t* a, counters_t* b)
```
#### union_counters
1. Computes union of two counters
2. For each docID, sums counts

```c
   static counters_t* union_counters(counters_t* a, counters_t* b)
```

#### rankResults
1. Sorts results by score (descending)
2. Prints formatted results with URL, score, and docID
3. Uses selection sort via counters_iterate

```c
static void rankResults(counters_t* results, const char* pageDirectory)
```

## Pseudocode

### Main Execution Flow
```bash
   1. Parse and validate command line arguments

   2. Load index from file into memory

   3. While more queries:
      a. Read and normalize query
      b. Validate query syntax
      c. Process query into counters structure
      d. Rank and display results

   4. Clean up and exit
```

### Query Processing
```bash
   function process_query(query, index):
      normalize query to lowercase
      validate no invalid characters
      split into words array
      if empty query or syntax error:
         return error
      
      result = NULL
      temp = NULL
      for each word in words:
         if word is not "and" or "or":
               word_counters = lookup in index
               if temp is NULL:
                  temp = word_counters
               else:
                  temp = intersect(temp, word_counters)
         else if word is "or":
               result = union(result, temp)
               temp = NULL
      result = union(result, temp)
      return result
```

### query_express
```c
   set result and temp to NULL //result and temp are counters_t* struct

   for word in words:
      if word is "OR" then
         if temp is NULL then
            error message Two ORs in a row
         else
            result = result v temp
            temp = NULL
      else if word is "AND" then
         continue
      else
         find counters of word in index
         if temp is NULL then
            copy counters ctr in temp
         else then
            intersect counters temp and counters ctr
            delete temp
            temp = new_temp
   if temp is not NULL:
      result = union between counters result and temp
   return result
```


### insersect_counters
```c
   create new counters_t* struct
   for each document id in first counters:
   get the count for document id (count_a)
   get the count for the document id in the second counters_t* (count_b)

   if count_b > 0:
      get minimum value between count_a and count_b
      insert into counters witht the min_count and key as docID

   return result
```

### union_counters
```c
   takes two parameters counters_t *a and counters_t *b
   initialize new counters_t struct to result

   if a is not NULL:
      for each document id in a:
         add count to result with id as key
   if b is not NULL:
      for each docID in b:
         get the old count from counters //counters_get(result, docID)
         add the sum of old and count in b to the new counters with docID as the key
   return result
```


### Ranking Algorithm
```bash
   function rank_results(counters, pageDirectory):
      while counters has entries:
         find docID with maximum score
         if score > 0:
               lookup URL from docID in pageDirectory
               print formatted result
         set that docID's score to 0
```

## Other Modules
The Querier interacts with:
- `pagedir` (common): For validating pageDirectory and mapping docIDs to URLS

- `index.c` (common): For loading/saving the index

- `word.c` (common): for word normalization

- `libcs50` utitlities: counters, hashtable, file modules

## Function Prototypes
```c
int main(const int argc, char* argv[]);

static void parseArgs(const int argc, char* argv[], char** pageDirectory, char** indexFileName);

static void processQuery(index_t* index, const char* pageDirectory);

static int split_line(char* line, char* words[]);

static counters_t* query_express(char* words[], int word_count, index_t* index);

static counters_t* intersect_counters(counters_t* a, counters_t* b);

static counters_t* union_counters(counters_t* a, counters_t* b);

static void rankResults(counters_t* results, const char* pageDirectory);
```

## Error Handling and Recovery
1. Invalid Arguments:
   - Verify Correct number of arguments
   - Validate pageDirectory is crawler-produced
   - Validate indexFile exists and is readable
2. Query Validation:
   - Check for invalid characters
   - Verify proper AND/OR syntax
   - Handly empty queries gracefully
3. Memory Management:
   - All counters structures are properly freed
   - Index is properly closed
   - Handle failed memory allocations

## Testing Plan
### Unit Testing
1. Argument Validation:
 - Testing with missing arguments

2. Query Processing:
   - Test simple one-word queries
   - Test AND queries
   - Test OR queries
   - Test complex combinations
   - Test invalid queries

3. Edge cases:
   - Empty queries
   - Queriers with no matches
   - Queries with special characters
   - Very long queries