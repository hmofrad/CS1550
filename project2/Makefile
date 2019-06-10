#!/usr/bin/make
CC=gcc
CC_FLAGS=-m32
SYSLIB=linux-2.6.23.1/include/
APP=aptsim

all:
	gcc $(CC_FLAGS) -o $(APP) $(SYSLIB) $(APP).c
clean:
	rm -rf $(APP)
