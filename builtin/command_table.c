#include <string.h>
#include "builtin.h"

typedef int (*CommandHandler)(char** cmd, size_t len);

struct CommandEntry {
	const char* cmd_name;
	CommandHandler handler;
};


static const struct CommandEntry table[] = {
	{"cd", dsh_handle_cd},
	{"exit", dsh_handle_exit}
};

#define COMMAND_COUNT (sizeof(table) / sizeof(table[0]))

int execute_command(char** cmd, size_t len) {
	for(size_t i = 0; i < COMMAND_COUNT; i++) {
		if (strcmp(cmd[0], table[i].cmd_name) == 0) {
			table[i].handler(cmd, len);
			return 0;
		}
	}

	return -1;
}
