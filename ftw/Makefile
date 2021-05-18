.PHONY: all debug
all: a.out

CFLAGS= -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
        -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
        -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
        -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
        -Wno-pointer-sign -std=gnu99 
%.o: %.c
	gcc -c -g $(CFLAGS) $< -o $@

function_file.o: function_file.c function_file.h
test.o: test.c function_file.h

a.out: function_file.o test.o
	gcc -o a.out function_file.o test.o
