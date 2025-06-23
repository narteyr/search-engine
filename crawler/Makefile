

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb
LIB = ../libcs50/libcs50.a ../common/commons.a
INCLUDES = -I../libcs50 -I../common

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all


SRC = crawler.c
OBJ = crawler.o
ARGS =  http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data 10

TARGET = crawler

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(OBJ): $(SRC) crawler.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


valgrind:
	@echo "Running with Valgrind..."
	$(VALGRIND) ./$(TARGET) $(ARGS)
	@echo "Valgrind completed."

test:
	@echo "Running tests..."
	make $(TARGET)
	bash -v testing.sh
	chmod +x testing.sh
	./testing.sh &> testing.out
	@echo "Tests completed."

clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf data
	rm -rf ../data/*
	rm -f  ../data/.crawler 
	rmdir ../data