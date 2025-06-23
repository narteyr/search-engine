#!/bin/bash
#author: Richmond Nartey Tettey

seed="http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html"
pdir="../data/toscrape-2"
indx="../data/toscrape-2/toscrape-2.index"

if [ ! -d "$pdir" ];then
    echo "============ CRAWLER =========="
    echo "Running crawler"
    cd ../crawler
    mkdir $pdir
    if [ ! -f "./crawler" ];then
        make all
    fi
    if [ ! -d "../data" ];then
        mkdir ../data
        mkdir ../data/toscrape-2
    fi
    ./crawler $seed $pdir 1
    echo "crawler complete"
    echo "============ CRAWLER =========="
    echo
fi

if [ ! -f "$indx" ];then
    echo "============ INDEXER ============"
    cd ../indexer
    touch $indx
    if [ ! -f "./indexer" ];then
        make all
    fi
    echo "indexing might take a while"
    echo "indexing..."
    ./indexer $pdir $indx
    echo "indexer complete"
    echo "============ INDEXER ============"
    echo
fi

echo "============ FUZZ QUERY ============"
cd ../querier
if [ ! -f "./querier" ];then
    make all
fi
./fuzzquery $indx 10 0 | ./querier $pdir $indx &>fuzz.out
echo "result passed to fuzz.out"
echo "query complete"
echo "============ FUZZ QUERY ============"
