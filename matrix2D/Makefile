.PHONY: all debug
all: prog
 
%.o: %.c
	gcc -c -g $< -o $@
my_math.o: my_math.h my_math.c

matrix_2d.o: matrix_2d.c matrix_2d.h errors.h my_math.h
test.o: test.c matrix_2d.h errors.h my_math.h

prog: my_math.o matrix_2d.o test.o
	gcc -o prog my_math.o matrix_2d.o test.o -lm
