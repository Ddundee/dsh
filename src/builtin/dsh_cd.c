#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int dsh_handle_cd(char** cmd, size_t len) {
	char* home_ptr = getenv("HOME");
#ifdef DEBUG
	printf("home ptr = %s\n", home_ptr);
	printf("| | | cd starting (len = %zu)\n", len);
#endif
	if (len == 1) {
		chdir(home_ptr);
		return 0;
	}

	if (cmd[1][0] == '~') {
		int cmd_len = strlen(cmd[1]);
		int home_len = strlen(home_ptr);
		char path[cmd_len + home_len + 1];

		for(int i = 0; i < home_len; i++) path[i] = home_ptr[i];
		for(int i = 0; i < cmd_len - 1; i++) path[i + home_len] = cmd[1][i + 1];
		path[cmd_len + home_len] = '\0';
#ifdef DEBUG
		printf("| | | cd path = %s\n", path);
#endif
		return chdir(path);
	}
#ifdef DEBUG
	printf("| | | cd parsed; running chdir (len = %zu)\n", len);
#endif
	return chdir(cmd[1]);
}
