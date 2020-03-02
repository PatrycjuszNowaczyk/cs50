# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CC = gcc                        # compiler to use

LINKERFLAG = -lm

SRCS := resize.c
BINS := resize

all: resize

resize: resize.o
	@echo "Checking.."
	gcc resize.o -o resize -lm

resize.o: resize.c
	@echo "Creating object.."
	gcc -c resize.c

clean:
	@echo "Cleaning up..."
	rm -rvf resize.o resize