

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb
LDFLAGS = -lm
OBJ = indexer.o  main.o #removed index.o
SRC = main.c  indexer.c
LIB = ../common/commons.a ../libcs50/libcs50.a 
INCLUDES = -I../common -I../libcs50 

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
INDEX_TEST = indexTest

TARGET = indexer
TEST_TARGET = test_indexer

# This Makefile is used to compile the indexer program for the project.
all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJ)
	$(CC)  $(CFLAGS) -o $@ $^ $(LIB) $(LDFLAGS)

# index.o: index.c index.h
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

indexer.o: indexer.c indexer.h  #removed index.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

main.o: main.c indexer.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

valgrind: $(TARGET)
	$(VALGRIND) ./$(TARGET) ../crawler/data/letters-10 ../data/test.index

$(INDEX_TEST):
	@echo "Running tests..."
	$(VALGRIND) ./$(TEST_TARGET) ../data/test.index ../data/new_test.index
	@echo "Tests completed."

test:
	@echo "Running Test Cases.."
	bash testing.sh
	chmod +x testing.sh
	./testing.sh &> testing.out
	@echo "Test Cases Completed."

$(TEST_TARGET): indexTest.o #removed indexdir.o
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIB) $(LDFLAGS)

# indexdir.o: indexdir.c  #removed indexdir.h
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

indexTest.o: indexTest.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: 	#removed index.o indexdir.o
	rm -f $(OBJ) $(TARGET)
	rm -f $(TEST_TARGET) indexTest.o testing.out
	rm -f ../data/test.index 
	rm -f ../data/new_test.index
	rm -f ../test/foo
	rmdir ../test 

