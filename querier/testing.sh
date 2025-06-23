#!/bin/bash

# Integration/System test script for querier
# Author: Richmond Nartey Kwalah Tettey
# Usage: bash -v testing.sh

PAGE_DIR=../data
QUERIER=./querier
INDEX_FILE=../data/index_files/test.index
QUERY_FILE=queries.txt


echo "---------------------------"
echo "Testing: Invalid Arguments"
echo "---------------------------"


echo "----------------------------"
echo "Testing: No Arguments"
echo "----------------------------"
$QUERIER

echo "----------------------------"
echo "Testing: Invalid Crawler Directory"
$QUERIER $PAGE_DIR/invalid_dir $INDEX_FILE
echo "----------------------------"

echo "----------------------------"
echo "Testing: Invalid Index File"
$QUERIER $PAGE_DIR $INDEX_FILE/invalid_file
echo "----------------------------"

echo "----------------------------"
echo "Testing: Valid Arguments"
touch hello.txt
$QUERIER $PAGE_DIR $INDEX_FILE < hello.txt
if [ $? -eq 0 ]; then
    echo "Arguments are valid."
fi
echo "----------------------------"

echo "----------------------------"
echo "Testing: Bad Character in Query"
echo "----------------------------"
$QUERIER $PAGE_DIR $INDEX_FILE <$QUERY_FILE
echo "----------------------------"