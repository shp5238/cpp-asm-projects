/****************************************************************
Project #2, COMP 280
Building a Shell
Author: Shreya Pasupuleti
****************************************************************/

#include "command_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
void sigchld_handler(int sig) {
    int saved_errno = errno;
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Background process %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Background process %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
    errno = saved_errno;
}
int main() {
    char cmdline[1024];
    struct CommandLine command;
    signal(SIGINT, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
    while (1) {
        printf("$ ");
        fflush(stdout);
        if (fgets(cmdline, sizeof(cmdline), stdin) == NULL) {
            printf("\n");
            break;
        }
        cmdline[strcspn(cmdline, "\n")] = '\0';
        if (!parseLine(&command, cmdline)) {
            continue;
        }
        if (command.argCount == 0) {
            freeCommand(&command);
            continue;
        }
        // Built-in: cd
        if (strcmp(command.arguments[0], "cd") == 0) {
            if (command.argCount > 2) {
                fprintf(stderr, "cd: usage: cd [1 argument only] \n");
            } else {
                char *target = NULL;
                if (command.argCount == 1) {
                    target = getenv("HOME");
                    if (!target) {
                        fprintf(stderr, "cd: HOME not set\n");
                        freeCommand(&command);
                        continue;
                    }
                } else {
                    target = command.arguments[1];
                    if (strchr(target, ' ')) {
                        fprintf(stderr, "cd: usage: cd [directory]\n");
                        freeCommand(&command);
                        continue;
                    }
                }
                if (chdir(target) != 0) {
                    perror("cd");
                }
            }
            freeCommand(&command);
            continue;
        }
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            freeCommand(&command);
            continue;
        }
        if (pid == 0) {
            signal(SIGINT, SIG_DFL);
            execvp(command.arguments[0], command.arguments);
            fprintf(stderr, "%s: command not found\n", command.arguments[0]);
            exit(1);
        }
        if (!command.background) {
            waitpid(pid, NULL, 0);
        }
        freeCommand(&command);
    }
    return 0;
}
