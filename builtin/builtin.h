#include <stddef.h>

#ifndef BUILTIN_H

int dsh_handle_cd(char** cmd, size_t len);
int dsh_handle_exit(char** cmd, size_t len);
int execute_command(char** cmd, size_t len);

#endif
