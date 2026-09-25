#include "parser.h"
#include <string.h>
#include <stdio.h>

void dsh_parser(char* const input, size_t len, char** output, size_t* outputSize) {

	char *token = strtok(input, " ");
	output[0] = token;
	size_t i = 1;
	for(;(token = strtok(NULL, " ")) != NULL && i < len; i++) {
		output[i] = token;
	}
	output[i] = NULL;
	*outputSize = i;

}

