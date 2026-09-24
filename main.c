#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc == 0) return 0;

	// ls reader
	if (strcmp("ls", argv[0])) {
		execv(argv[0], argv);
	}
	
	printf("--END--");
	
	return 0;
}
