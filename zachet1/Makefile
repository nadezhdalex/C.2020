.PHONY: all debug
all: a.out

CFLAGS= -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
        -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
        -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
        -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
        -Wno-pointer-sign -std=gnu99 
%.o: %.c
	gcc -c -g $(CFLAGS) $< -o $@

my_string.o: my_string.h my_string.c
task43.o: task43.c task43.h my_string.h errors.h
test.o: test.c task43.h my_string.h errors.h

a.out: my_string.o task43.o test.o
	gcc -o a.out my_string.o task43.o test.o
