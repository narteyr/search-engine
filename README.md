# CS50 Tiny Search Engine (TSE)

## Overview

The Tiny Search Engine (TSE) is a simplified search engine designed for educational purposes. It consists of three main components: `crawler`, `indexer`, and `querier`. These components work together to crawl webpages, build an index of words, and allow users to query the index for relevant results. The project also includes shared libraries (`libcs50`) and utility modules (`commons`) to support the functionality.

### Components

1. **`crawler`**: Crawls a website starting from a seed URL, retrieves webpages, and saves them to a specified directory.
2. **`indexer`**: Reads the saved webpages, builds an index of words, and saves the index to a file.
3. **`querier`**: Reads the index file and allows users to query for words, returning relevant pages.

---

## Crawler

### Description

The `crawler` starts from a seed URL, fetches webpages, extracts internal URLs, and continues crawling up to a specified depth. It avoids revisiting duplicate URLs and saves the fetched pages to a directory.

### Usage

```bash
./crawler <seedURL> <pageDirectory> <maxDepth>
```

- **`seedURL`**: The starting URL for the crawl.
- **`pageDirectory`**: Directory to save crawled pages.
- **`maxDepth`**: Maximum depth to crawl (non-negative integer).

### Example

```bash
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data 3
```

---

## Commons

### Description

The `commons` module provides shared utilities and helper functions used across the TSE components. These include:

- **`pagedir`**: Handles directory initialization and saving pages.
- **`webpage`**: Provides utilities for webpage fetching and URL extraction.
- **`bag`**: Implements a bag data structure for managing pages to crawl.
- **`hashtable`**: Implements a hashtable for tracking seen URLs.

### Key Features

- **Memory Management**: Ensures proper allocation and deallocation of resources.
- **Data Structures**: Provides reusable and efficient data structures.

---

## libcs50

### Description

The `libcs50` library is a collection of utility functions and data structures designed to simplify programming tasks. It includes:

- **`bag`**: A collection of items with no specific order.
- **`hashtable`**: A hash table for efficient key-value storage.
- **`memory`**: Utilities for safe memory allocation and deallocation.

### Key Features

- **Robustness**: Includes error-checking mechanisms.
- **Reusability**: Designed to be used across multiple projects.

---

## Compilation

To compile the project, use the provided `Makefile`:

```bash
make
```

This will build all components (`crawler`, `indexer`, and `querier`) and their dependencies.

---

## Testing

### Crawler

To test the `crawler`, run:

```bash
./crawler <seedURL> <pageDirectory> <maxDepth>
```

### OR:
```bash
    make test
```

### Memory Testing

Use Valgrind to check for memory leaks:

```bash
make valgrind
```

---

## Notes

- Ensure the `pageDirectory` exists and is writable before running the `crawler`.
- The `crawler` only processes internal URLs and ignores external ones.
- Memory management is carefully handled to avoid leaks, as verified by Valgrind.

---

## Author

Richmond Nartey Kwalah Tettey  
CS50, Spring 2025