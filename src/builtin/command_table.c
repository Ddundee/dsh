#include <stdio.h>
#include <string.h>
#include "../../include/builtin.h"

typedef int (*CommandHandler)(char** cmd, size_t len);

struct CommandEntry {
	const char* cmd_name;
	CommandHandler handler;
};

static const struct CommandEntry table[] = {
	{"cd", dsh_handle_cd},
	{"exit", dsh_handle_exit},
};

#define COMMAND_COUNT (sizeof(table) / sizeof(table[0]))

int execute_command(char** cmd, size_t len) {
#ifdef DEBUG
	printf("| execute_command starting\n");
#endif
	for(size_t i = 0; i < COMMAND_COUNT; i++) {
		if (strcmp(cmd[0], table[i].cmd_name) == 0) {
#ifdef DEBUG
			printf("| | handler %s starting\n", table[i].cmd_name);
#endif
			table[i].handler(cmd, len);
#ifdef DEBUG
			printf("| | handler %s done\n", table[i].cmd_name);
			printf("| execute_command done\n");
#endif
			return 0;
		}
	}
#ifdef DEBUG
	printf("| execute_command done\n");
#endif
	return -1;
}
