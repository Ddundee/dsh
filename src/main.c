#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/main.h"
#include "../include/parser.h"
#include "../include/builtin.h"
#include "../include/util.h"
#include "../include/signals.h"

struct Info info;

int main() {
	// initialize env
	info = initialize();

	// signal: sigint doesnt exit
	dsh_startup_signal();
	
	while(TRUE) {
		trigger_prompt();
	}

	return 0;

}


struct Info initialize() {
	struct Info info;
	info.user = getenv("USER");

	return info;
}

