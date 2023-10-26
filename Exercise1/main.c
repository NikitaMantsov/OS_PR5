#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"commands\"\n", argv[0]);
        return 1;
    }

    char *commands = argv[1];
    char *token = strtok(commands, ";");

    while (token != NULL) {
        int returnCode = system(token);

        if (returnCode == -1) {
            perror("Command execution error");
        } else {
            printf("Command executed with exit code: %d\n", returnCode);
        }

        token = strtok(NULL, ";");
    }

    return 0;
}

