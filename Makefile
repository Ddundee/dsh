CC = gcc
CFLAGS = 
OUT = dsh
OUT_DIR = out
FILES = src/**/*.c
DEBUG = -DDEBUG -g

all: compile run

compile: clear main.c
	$(CC) $(CFLAGS) -o "$(OUT_DIR)/$(OUT)" $(FILES)

run:
	"./$(OUT_DIR)/$(OUT)"

clear:
	rm -rf $(OUT_DIR)/*

debug:
	$(CC) $(CFLAGS) $(DEBUG) -o $(OUT) $(FILES)

debugger: debug
	lldb "./$(OUT_DIR)/$(OUT)"
