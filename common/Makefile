
# This Makefile is used to compile the commons library for the project.
# Author: Richmond Nartey Tettey, CS50 May 2025


CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
INCLUDES = -I../libcs50
LIB = commons.a 

SRC = pagedir.c index.c indexdir.c words.c
OBJ = pagedir.o index.o indexdir.o words.o

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: testing.sh
	@echo "Running 'pagedir.c' tests..."
	bash -v ./testing.sh
	chmod +x testing.sh
	./testing.sh
	@echo "Tests completed."

clean:
	rm -f $(OBJ) $(LIB)