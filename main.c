#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include "parser.h"

typedef struct {
	char program[MAX_BUFFER];
	char* flags;
} Command;

int main() {
	char* input;
	while(TRUE) {
		input = calloc(MAX_BUFFER, sizeof(char));

		printf("dsh> ");

		if (fgets(input, MAX_BUFFER, stdin) == NULL) return 1;
		input[strcspn(input, "\n")] = 0;

		char** cmd = dsh_parser(input);
#ifdef DEBUG
		printf("Program name: %s\n", cmd[0]);
		for(int itr = 1; cmd[itr] != NULL; itr++) {
			printf("flag: %s\n", cmd[itr]);
		}
		printf("running: \n");
#endif
		
		if (strcasecmp(cmd[0], "exit") == 0) {
			return 0;
		}

		pid_t p = fork();
#ifdef DEBUG
		printf("starting fork(pid: %d)\n", p);
#endif
		if (p < 0) perror("creating fork for process failed\n");
		else if (p == 0) {
			execvp(cmd[0], cmd);
		}
		else {
			int status;
#ifdef DEBUG
			pid_t reaped_pid = waitpid(p, &status, 0);
			printf("process finished (reaped_pid = %d, status = %d)\n", reaped_pid, status);
#else
			waitpid(p, &status, 0);
#endif

		}

		
		
		free(input);
	}

	return 0;

}

