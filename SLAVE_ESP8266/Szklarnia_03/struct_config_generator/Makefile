CC = gcc
CFLAGS = -Wall -g -std=c99

all: struct_config_generator

struct_config_generator: struct_config_generator.o

struct_config_generator.o: struct_config_generator.c

clean:
	rm -f *.o struct_config_generator core core.*
