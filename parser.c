#include "main.h"
#include "parser.h"
#include <strings.h>
#include <stdio.h>

char** dsh_parser(char* const input) {
	static char* ret[MAX_BUFFER];

	char *token = strtok(input, " ");
	ret[0] = token;
	for(int i = 1; (token = strtok(NULL, " ")) != NULL && i < MAX_BUFFER; i++) {
		ret[i] = token;
	}

	return ret;
}

