src = $(wildcard ./src/*.c)
targets = $(patsubst ./src/%.c, ./targets/%.o, $(src))
inc_path = ./include/

CC = gcc
CFLAGS = -Wall -g
CPPFLAGS = -I

all:main

./targets/%.o:./src/%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(inc_path) $(CFLAGS)

main:$(targets)
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets) main

