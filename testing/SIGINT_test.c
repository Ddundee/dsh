#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int sig) {
	printf("signal %d\n", sig);

	exit(1);
	
}

int main(void) {
	signal(SIGINT, sigint_handler);
	while (1) {
		printf("Hello World!\n");
		sleep(1);
	}
	return 0;
}
