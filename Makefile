CC = gcc
CFLAGS = 
OUT = dsh
OUT_DIR = out
FILES = $(shell find src -name '*.c')
DEBUG = -DDEBUG -g

all: compile run

.PHONY: compile
compile: clear 
	$(CC) $(CFLAGS) -o "$(OUT_DIR)/$(OUT)" $(FILES)

.PHONY: run
run:
	"./$(OUT_DIR)/$(OUT)"

.PHONY: clear
clear:
	rm -rf $(OUT_DIR)/*

.PHONY: debug
debug:
	$(CC) $(CFLAGS) $(DEBUG) -o "$(OUT_DIR)/$(OUT)" $(FILES)

.PHONY: debugger
debugger: debug
	lldb "./$(OUT_DIR)/$(OUT)"

.PHONY: register
register: compile
	sudo mkdir -p /usr/local/bin
	sudo install -m 755 out/dsh /usr/local/bin/dsh
	grep -qxF '/usr/local/bin/dsh' /etc/shells || printf '%s\n' '/usr/local/bin/dsh' | sudo tee -a /etc/shells
