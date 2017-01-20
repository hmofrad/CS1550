#!/usr/bin/make
# Graphics Library Makefile
# (c) Mohammad H. Mofrad, 2017

LIB = library
MAIN = square
GCC = gcc

install:
	$(GCC) -o $(LIB).o -c $(LIB).c
	$(GCC) -o $(MAIN).o -c $(MAIN).c
	$(GCC) -o $(MAIN) $(MAIN).o $(LIB).o

clean:
	rm -f $(LIB).o
	rm -f $(MAIN).o
	rm -f $(MAIN)
