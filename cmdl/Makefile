CC     = gcc
CFLAGS = -Wall -Wextra -g

.PHONY: all run clean

all: unit_test

# Build unit_test
unit_test: unit_test.c cmdl.c cmdl.h
	$(CC) $(CFLAGS) -o unit_test unit_test.c

# Compile cmdl.c to object (smoke-check it builds cleanly)
cmdl.o: cmdl.c cmdl.h
	$(CC) $(CFLAGS) -c cmdl.c -o cmdl.o

# Run
run: unit_test
	./unit_test

# Clean
clean:
	rm -f unit_test cmdl.o
