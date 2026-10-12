#ifndef UTIL_H

#include <sys/types.h>
#include <unistd.h>

void str_trim(char *str);
pid_t dsh_fork_exec(char** cmd);

#endif
