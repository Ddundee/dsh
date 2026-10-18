#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"

void sigint_handler(int sig) {
#ifdef DEBUG
	printf("esignal %d\n", sig);
#endif

	trigger_prompt();
}

void dsh_startup_signal() {
	// signal(SIGINT, sigint_handler);
	signal(SIGINT, SIG_IGN);
}
