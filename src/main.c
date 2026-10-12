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

		if (execute_command((char**)cmd, cmdSize) != -1) continue;

		dsh_fork_exec((char**)cmd);

		free(input);
	}

	return 0;

}


struct Info initialize() {
	struct Info info;
	info.user = getenv("USER");

	return info;
}

