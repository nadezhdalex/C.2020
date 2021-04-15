.PHONY: all debug
all: prog
 
%.o: %.c
	gcc -c -g $< -o $@
 
find_log.o: find_log.c find_log.h
test.o: test.c find_log.h

prog: find_log.o test.o
	gcc -o prog find_log.o test.o -lm
