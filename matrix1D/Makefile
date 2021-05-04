.PHONY: all debug
all: prog
 
%.o: %.c
	gcc -c -g $< -o $@
my_math.o: my_math.h my_math.c

matrix_1d.o: matrix_1d.c matrix_1d.h errors.h my_math.h
test.o: test.c matrix_1d.h errors.h my_math.h

prog: my_math.o matrix_1d.o test.o
	gcc -o prog my_math.o matrix_1d.o test.o -lm
