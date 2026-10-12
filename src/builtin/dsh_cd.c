#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int dsh_handle_cd(char** cmd, size_t len) {

	for(size_t i = 1; i < len; i++) {
		char* path = cmd[i];
		int count = 0;
		for(int j = 0; j < strlen(path); j++) {
			if (path[i] == '/') count++;
		}
		count++;

		char* splitPath[count];
		splitPath[0] = strtok(path, "/");

		for(int j = 1; (splitPath[j] = strtok(NULL, "/")) != NULL; j++);

		for(int j = 0; j < count; j++) {
			char* env = getenv(splitPath[j]);
			if (env != NULL) splitPath[j] = env;
		}

		int path_len = 0;
		for(int j = 0; j < count; j++) path_len += strlen(splitPath[j]);
		
		char newPath[path_len + count];
		// for(int arr_itr = 0, path_itr = 0; arr_itr < )



		if (chdir(path) == -1) return -1;
	}

	return 0;
}
