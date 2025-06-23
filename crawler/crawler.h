/**
 * 'crawler.h' provides the definition of the Crawler class, which is responsible for
 * crawling web pages, extracting links, and managing the crawling process.
 *
 * Author: Richmond Nartey Kwalah Tettey , CS50 2025
 */


#ifndef CRAWLER_H
#define CRAWLER_H

#include "webpage.h"
#include "bag.h"
#include "hashtable.h"
/**
 *  Caller:
 *  provides 4 arguments:
 *      seedURL: the URL to start crawling from
 *      pageDirectory: the directory to save crawled pages
 *      maxDepth: the maximum depth to crawl
 *
 * We return:
 *  nothing if the arguments are not valid
 *
 * @param argc
 * @param argv
 * @param seedURL
 * @param pageDirectory
 * @param maxDepth
 */
static void parseArgs(const int argc, char * argv[],
                      char** seedURL , char** pageDirectory, int* maxDepth);


/**
 *
 * Caller provides valid arguments:
 * @param seedURL
 * @param pageDirectory
 * @param maxDepth
 *
 * We do:
 *  initialize the hashtable and add the seedURL
 *  initialize the bag and add webpage representing the seedURL
 *  we crawl the page and add the links to the bag
 *  we delete hashtable and bag, if it reaches maxDepth or
 *  no webpage to crawl
 */
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);


/**
 * Caller:
 *  provides a webpage and a hashtable
 *
 * Purpose:
 *  Given a webpage, scan the given page to
 *  extract any links (URLS), ignoring non-internal
 *  URLS; for any URL not already seen before, add
 *  the URL to both the hashtable and to the bag.
 *
 * We do:
 *  extract the links from the webpage
 *  add the links to the hashtable
 *  create a webpage for each link and inset to bag
 *
 * finally:
 *     we free the URL
 *
 *We return:
 * nothing if the webpage is NULL
 * @param page
 * @param pagesSeen
 */
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

#endif
