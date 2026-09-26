#include <unistd.h>

int dsh_handle_cd(char** cmd, size_t len) {

	for(size_t i = 1; i < len; i++) {
		if (chdir(cmd[i]) == -1) return -1;
	}

	return 0;
}
