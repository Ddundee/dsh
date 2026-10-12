#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/builtin.h"

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
