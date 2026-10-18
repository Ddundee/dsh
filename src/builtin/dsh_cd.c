#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int dsh_handle_cd(char** cmd, size_t len) {
#ifdef DEBUG
	printf("| | | cd starting (len = %zu)\n", len);
#endif
	char* home_ptr = getenv("HOME");
	if (len == 1) chdir(home_ptr);

	if (cmd[1][0] == '~') {
		int cmd_len = strlen(cmd[1]);
		int home_len = strlen(home_ptr);
		char path[cmd_len + home_len + 2];

		for(int i = 0; i < cmd_len; i++) path[i] = home_ptr[i];
		path[cmd_len] = '/';
		for(int i = 0; i < home_len; i++) path[i + cmd_len + 1] = cmd[1][i];
		path[cmd_len + home_len + 1] = '\0';
	}
#ifdef DEBUG
	printf("| | | cd parsed; running chdir (len = %zu)\n", len);
#endif
	return chdir(cmd[1]);
}
