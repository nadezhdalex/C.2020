.PHONY: all debug
all: prog
 
%.o: %.c
	gcc -c -g $< -o $@
 
root_finding.o: root_finding.c root_finding.h
test.o: test.c root_finding.h
 
prog: root_finding.o test.o
	gcc -o prog root_finding.o test.o -lm
