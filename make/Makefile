#!/usr/bin/make
# Multiple files development
# (C) Mohammad H. Mofrad, 2016

LIB=lib
MAIN=main

install: $(LIB).o $(MAIN).o
	gcc -o $(MAIN) $(MAIN).o $(LIB).o

$(LIB).o: $(LIB).h $(LIB).c
	gcc -o $(LIB).o -c $(LIB).c

$(MAIN).o: $(MAIN).c
	gcc -o $(MAIN).o -c $(MAIN).c

clean:
	rm -f $(LIB).o
	rm -f $(MAIN).o
	rm -f $(MAIN)
