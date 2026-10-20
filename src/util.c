#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/builtin.h"
#include "../include/main.h"
#include "../include/parser.h"

void str_trim(char *str) {
    if (str == NULL) return;

    char *start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    size_t length = (start <= end) ? (end - start + 1) : 0;
    if (start != str && length > 0) {
        memmove(str, start, length);
    }

    str[length] = '\0';
}

pid_t dsh_fork_exec(char** cmd) {

    pid_t p = fork();

#ifdef DEBUG
    printf("starting fork(pid: %d)\n", p);
#endif

    if (p < 0) perror("creating fork for process failed\n");
    else if (p == 0) {
        execvp(cmd[0], cmd);
        _exit(0);
    }
    else {
        int status;

        pid_t reaped_pid = waitpid(p, &status, 0);

#ifdef DEBUG
        printf("process finished (reaped_pid = %d, status = %d)\n", reaped_pid, status);
#endif

        return reaped_pid;
    }
    return -1;
}

void trigger_prompt() {
#ifdef DEBUG
    printf("\ntrigger_prompt triggered\n");
#endif

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
    printf("execute_command([");
    for(int i = 0; i < cmdSize; i++) {
        printf(" \"%s\" ", cmd[i]);
    }
    printf("], %zu)\n", cmdSize);
    if (cmd[0] != NULL) printf("cmd[0] = NULL\n");
//    else printf("cmd[0].length = %lu\n", strlen(cmd[0]));
#endif


    if (cmd[0] != NULL && execute_command((char**)cmd, cmdSize) == -1) {
        dsh_fork_exec((char**)cmd);
    }


    free(input);
}
