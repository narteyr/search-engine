#!/bin/bash

#TESTING PLAN

# 1. Test indexer with various invalid arguments

#no arguments
#one argument
#three or more arguments
#invalid pageDirectory (non-existent path)
#invalid pageDirectory (not a crawler directory)
#invalid indexFile (non-existent path)
#invalid indexFile (read-only directory)
#invalid indexFile (existing, read-only file)

DATA_DIRECTORY=../data
TEST_DIRECTORY=../test
INDEXER=./indexer
INDEX_TEST=./test_indexer
VALID_INDEX_FILE=test.index
mkdir -p ../data/index_files


echo "---------------------------"
echo "Testing: NO Arguments"
echo "---------------------------"
$INDEXER
echo

echo "---------------------------"
echo "Testing: 1 Arguments"
echo "---------------------------"
$INDEXER foo
echo


echo "---------------------------"
echo "Testing: 3 or more Arguments"
echo "---------------------------"
$INDEXER a b c
echo


echo "---------------------------"
echo "Testing: Invalid pageDirectory (non-existent path)"
echo "---------------------------"
$INDEXER $TEST_DIRECTORY invalid.index
echo

echo "---------------------------"
echo "Testing: Invalid pageDirectory (missing .crawler file)"
echo "---------------------------"
mkdir -p $TEST_DIRECTORY
echo "foo" > $TEST_DIRECTORY/foo
$INDEXER $TEST_DIRECTORY/invalid2 invalid.index
echo

echo "---------------------------"
echo "Invalid indexFile"
$INDEXER $DATA_DIRECTORY test.index
echo "---------------------------"
echo

echo "---------------------------"
echo "Testing: IndexBuilder"
touch ../data/index_files/$VALID_INDEX_FILE
$INDEXER $DATA_DIRECTORY ../data/index_files/$VALID_INDEX_FILE
echo "---------------------------"
echo "---------------------------"



echo "---------------------------"
echo "Testing: IndexRebuilder (inverse index data structure test )"
touch ../data/index_files/new_test.index
$INDEX_TEST $DATA_DIRECTORY/index_files/$VALID_INDEX_FILE ../data/index_files/new_test.index
echo "---------------------------"
echo

echo "Testing Complete" 
echo