#!/bin/bash

# Integration/System test script for crawler
# Author: Richmond Nartey Kwalah Tettey
# Usage: bash -v testing.sh

CRAWLER=./crawler
DATA=data
SEEDURL_LETTERS="http://cs50tse.cs.dartmouth.edu/tse/letters/index.html"

echo "---------------------------"
echo "Testing: Invalid Arguments"
echo "---------------------------"
$CRAWLER
$CRAWLER $SEEDURL_TOSCRAPE
$CRAWLER $SEEDURL_TOSCRAPE $DATA/toscrape-0
$CRAWLER $SEEDURL_TOSCRAPE $DATA/toscrape-0 -1
$CRAWLER not-a-url $DATA/toscrape-0 1
$CRAWLER $SEEDURL_TOSCRAPE /nonexistent-dir 1
$CRAWLER $SEEDURL_TOSCRAPE $DATA/toscrape-0 notanumber

echo
echo "---------------------------"
echo "Functional Testing: letters"
echo "---------------------------"

for depth in 0 1 2 10; do
    echo "Testing letters at depth $depth"
    mkdir -p $DATA/letters-$depth
    $CRAWLER $SEEDURL_LETTERS $DATA/letters-$depth $depth
    echo
done

echo
echo "---------------------------"
echo "Functional Testing: wikipedia"
echo "---------------------------"

for depth in 0 1 2; do
    echo "Testing wikipedia at depth $depth"
    mkdir -p $DATA/wikipedia-$depth
    $CRAWLER $SEEDURL_WIKIPEDIA $DATA/wikipedia-$depth $depth
done

echo "Testing letters at depth 10"
mkdir -p ../data
$CRAWLER $SEEDURL_LETTERS ../data 10

echo
echo "All tests completed."