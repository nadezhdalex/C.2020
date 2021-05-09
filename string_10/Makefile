.PHONY: all debug
all: prog
 
%.o: %.c
	gcc -c -g $< -o $@
my_string.o: my_string.h my_string.c

function_string.o: function_string.c function_string.h my_string.h
test.o: test.c function_string.h my_string.h

prog: my_string.o function_string.o test.o
	gcc -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    	-Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
    	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
    	-Wno-pointer-sign -std=gnu99 -o prog my_string.o function_string.o test.o
