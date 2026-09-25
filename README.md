# dsh

`dsh` is a small Unix shell written in C.

I started this project mainly as a challenge to myself. I wanted to get more comfortable with C and better understand what actually happens when you run commands in a terminal instead of relying on higher-level functions like `system()`.

The goal is to build the core behavior of a shell from scratch using Unix system calls such as `fork()`, `execvp()`, `waitpid()`, `pipe()`, `dup2()`, and `chdir()`.

* Execute normal shell commands

```bash
dsh> ls -la
dsh> gcc main.c -o main
dsh> ./main
```

## Current Progress
* Lowkey just started

## Todo
- [ ] get child processes to persist (ie cd test, mkdir test-inside should make a test-inside inside test)
- [x] Make a input system
- [x] Get normal programs to run (ls, gcc)

## Why I Made This

This is not meant to replace an existing shell like Bash or Zsh.

I mostly wanted a project that would force me to work directly with C, Unix system calls, processes, and file descriptors. Instead of only learning how these concepts work individually, I wanted to combine them into something that I could actually use and gradually make more complex.

The project is intentionally being built piece by piece so I can understand each part rather than relying on libraries that abstract the behavior away.

