#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
#include "parser.h"

int main() {
	// initialize env
	struct Info info = initialize();
	
	while(TRUE) {
		char* input = calloc(MAX_BUFFER, sizeof(char));
		size_t inputSize = 0;

		printf("%s$dsh > ", info.user);

		if (getline(&input, &inputSize, stdin) == -1) exit(1);
		input[strcspn(input, "\n")] = 0;

		char* cmd[MAX_BUFFER];
		size_t cmdSize = 0;
		dsh_parser(input, inputSize, cmd, &cmdSize);
		

#ifdef DEBUG
		printf("program name: %s\n", cmd[0]);
		for(size_t itr = 1; itr < cmdSize; itr++) {
			printf("flag: %s\n", cmd[itr]);
		}
		printf("running: \n");
#endif

		if (strcmp(cmd[0], "exit") == 0) {
			exit(0);
		}
		else if (strcmp(cmd[0], "cd") == 0 && cmdSize == 2) {
			chdir(cmd[1]);
			continue;
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


struct Info initialize() {
	struct Info info;
	info.user = getenv("USER");

	return info;
}

