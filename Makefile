CC = gcc
CFLAGS = -Wall -Werror -Wextra
OUT = dsh
FILES = main.c parser.c
DEBUG = -DDEBUG -g

all: compile

compile: clear main.c
	$(CC) $(CFLAGS) -o $(OUT) $(FILES)

run: compile
	./dsh

clear:
	rm -rf $(OUT)*

debug:
	$(CC) $(CFLAGS) $(DEBUG) -o $(OUT) $(FILES)

debugger: debug
	lldb $(DSH)
