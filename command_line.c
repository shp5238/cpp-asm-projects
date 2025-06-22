/****************************************************************
Project #2, COMP 280
Building a Shell
Author: Shreya Pasupuleti
****************************************************************/
//include statements
#include "command_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARGS 64

// Parses the input line into a CommandLine structure
// Returns 1 on success, 0 if input is empty or invalid
int parseLine(struct CommandLine *cmd, const char *input) {
    cmd->argCount = 0;
    cmd->background = 0;

    if (input == NULL) return 0;

    // Make a modifiable copy of input
    char *line = strdup(input);
    if (!line) {
        perror("strdup");
        return 0;
    }

    // Trim trailing spaces
    size_t len = strlen(line);
    while (len > 0 && isspace((unsigned char)line[len - 1])) {
        line[len - 1] = '\0';
        len--;
    }
    if (len == 0) {
        free(line);
        return 0;
    }

    // Check if last character is '&' (background)
    if (len > 0 && line[len - 1] == '&') {
        cmd->background = 1;
        line[len - 1] = '\0';  // Remove &
        // Remove trailing whitespace again after &
        len--;
        while (len > 0 && isspace((unsigned char)line[len - 1])) {
            line[len - 1] = '\0';
            len--;
        }
    }

    // Tokenize by whitespace
    char *token;
    char *rest = line;

    while ((token = strtok_r(rest, " \t", &rest)) != NULL) {
        if (cmd->argCount >= MAX_ARGS - 1) {
            fprintf(stderr, "Too many arguments (max %d)\n", MAX_ARGS);
            break;
        }
        cmd->arguments[cmd->argCount] = strdup(token);
        if (!cmd->arguments[cmd->argCount]) {
            perror("strdup");
            free(line);
            return 0;
        }
        cmd->argCount++;
    }

    cmd->arguments[cmd->argCount] = NULL;  // Null-terminate argv

    free(line);
    return cmd->argCount > 0;
}

// Frees memory allocated in CommandLine structure
void freeCommand(struct CommandLine *cmd) {
    for (int i = 0; i < cmd->argCount; i++) {
        free(cmd->arguments[i]);
        cmd->arguments[i] = NULL;
    }
    cmd->argCount = 0;
    cmd->background = 0;
}
