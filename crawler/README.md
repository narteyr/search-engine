# CS50 Lab 4: Crawler

## Overview

The `crawler` is a program that crawls a website starting from a specified seed URL. It retrieves webpages, extracts embedded URLs, and continues crawling up to a specified depth. The program avoids revisiting the same URL and only processes internal URLs. The retrieved pages are saved to a specified directory for further processing, such as indexing.

## Features

- Crawls webpages starting from a seed URL.
- Extracts and processes internal URLs.
- Avoids revisiting duplicate URLs.
- Saves crawled pages to a specified directory.
- Limits crawling to a user-defined maximum depth.

## Usage

The `crawler` program is executed from the command line with the following syntax:

```bash
./crawler <seedURL> <pageDirectory> <maxDepth>
```

### Arguments:
1. **`seedURL`**: The starting URL for the crawl. Must be a valid and normalized URL.
2. **`pageDirectory`**: The directory where crawled pages will be saved. Must be writable and initialized using `pagedir_init`.
3. **`maxDepth`**: The maximum depth to crawl. Must be a non-negative integer.

### Example:
```bash
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data 10
```

This command starts crawling from the given seed URL, saves pages in the `data` directory, and limits the crawl depth to 10.

## Implementation

The `crawler` module is implemented in `crawler.c` and uses the following key components:

- **`parseArgs`**: Validates and parses command-line arguments.
- **`crawl`**: Manages the crawling process, including fetching pages, saving them, and scanning for new URLs.
- **`pageScan`**: Extracts URLs from a webpage, checks if they are internal, and adds them to the crawl queue if not already seen.

### Key Data Structures:
- **`bag_t`**: Used to manage the queue of pages to crawl.
- **`hashtable_t`**: Tracks URLs that have already been seen to avoid duplicates.

### Workflow:
1. Initialize the `bag` and `hashtable`.
2. Add the seed URL to the `bag`.
3. Fetch and save each page from the `bag`.
4. Extract and process URLs from the fetched page.
5. Repeat until the `bag` is empty or the maximum depth is reached.

## Files

- **`crawler.c`**: Implements the main functionality of the crawler.
- **`crawler.h`**: Provides function prototypes and documentation.
- **`pagedir.c`**: Handles directory initialization and page saving.
- **`webpage.c`**: Provides utilities for webpage fetching and URL extraction.
- **`bag.c`**: Implements a bag data structure for managing pages to crawl.
- **`hashtable.c`**: Implements a hashtable for tracking seen URLs.

## Compilation

To compile the `common` library, use the provided `Makefile` in the common directory:
```bash
  make all
```
### Note: common and libcs50 library needs to be compiled before the crawler.

The common library includes the `bag`, `hashtable`, and `pagedir` modules, which are essential for the crawler's functionality.
To compile the crawler, use the provided `Makefile` in the crawler directory.:
```bash
  make
```

## Testing

To test the program, run the following command:
```bash
make valgrind
```

A sampling of tests that should be run:
```bash
make test
```

This will execute the program with Valgrind to check for memory leaks and other issues.

### Example Test:
```bash
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data 2
```

This test crawls the seed URL up to a depth of 2 and saves the pages in the `data` directory.

## Notes

- Ensure the `pageDirectory` exists and is writable before running the program.
- The program only processes internal URLs and ignores external ones.
- Memory management is handled carefully to avoid leaks, as verified by Valgrind.

## Author

Richmond Nartey Kwalah Tettey  
CS50, Spring 2025
