#!/usr/bin/make
# Makefile
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu

CC=gcc
CC_FLAGS=-m32
SYSLIB=-I linux-2.6.23.1/include/
APP1=aptsim
APP2=condvar_test
LIB=condvar.c

all:
	$(CC) $(CC_FLAGS) -o $(APP1) $(SYSLIB) $(APP1).c
	$(CC) $(CC_FLAGS) -o $(APP2) $(SYSLIB) $(APP2).c $(LIB)
clean:
	rm -rf $(APP1)
	rm -rf $(APP2)
