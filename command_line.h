/****************************************************************
Project #2, COMP 280
Building a Shell
Author: Shreya Pasupuleti
****************************************************************/
#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

struct CommandLine {
    char *arguments[64];  // argument list (null terminated)
    int argCount;         // number of arguments
    int background;       // 1 if command ends with &, else 0
};

int parseLine(struct CommandLine *cmd, const char *input);
void freeCommand(struct CommandLine *cmd);

#endif // COMMAND_LINE_H
