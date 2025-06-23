

CC = gcc
CFLAGS = -g -Wall -Werror -std=c11 -ggdb
LDFLAGS = -lm
OBJ = main.o querier.o
SRC= main.c querier.c
LIBS = ../common/commons.a ../libcs50/libcs50.a 
INCLUDES = -I../libcs50 -I../common
TARGET = querier
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS) $(LDFLAGS)

main.o: main.c querier.h
	$(CC) $(CFLAGS) -c $< $(INCLUDES)

querier.o: querier.c querier
	$(CC) $(CFLAGS) -c $< $(INCLUDES)


fuzz: fuzzquery
	@echo "Running Querier Fuzz testing..."
	bash fuzz.sh
	@echo "Fuzz Test Completed."

fuzzquery: fuzzquery.o
	$(CC) $(CFLAGS) -o fuzzquery fuzzquery.o $(LIBS) $(LDFLAGS)

fuzzquery.o:fuzzquery.c
	$(CC) $(CFLAGS) -c $< $(INCLUDES)


.PHONY: test valgrind fuzz clean

test:
	@echo "Running Test Cases.."
	bash testing.sh
	chmod +x testing.sh
	./testing.sh &> testing.out
	@echo "Test Cases Completed."
	
valgrind: $(TARGET)
	$(VALGRIND) ./$(TARGET) ../data ../data/index_files/test.index

clean:
	rm -f $(OBJ) $(TARGET)
	rm -f fuzzquery.o fuzzquery
	rm -f fuzzquery
	rm -rf ../data/toscrape-2/*
	rm -rf ../data/toscrape-2/.crawler
	rmdir ../data/toscrape-2
