#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void createChildProcess(const char *fileName, int number);

void handleError(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}

void writeToFile(FILE *file, int number) {
    for (int i = 0; i < number; i++) {
        double randomNumber = (double)rand() / RAND_MAX;
        fprintf(file, "%lf\n", randomNumber);
    }
    fclose(file);
}

void createChildProcess(const char *fileName, int number) {
    pid_t pid = fork();

    if (pid == 0) {
        char filename[100];
        snprintf(filename, sizeof(filename), "%s_%d.txt", fileName, number);

        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            writeToFile(file, number);
        } else {
            handleError("Unable to open file for writing");
        }
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    const char *fileName = "default";
    int numChildren = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                fileName = argv[i + 1];
                i++;
            } else {
                handleError("Argument expected for option -f");
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                numChildren = atoi(argv[i + 1]);
                i++;
            } else {
                handleError("Argument expected for option -n");
            }
        }
    }

    for (int i = 1; i <= numChildren; i++) {
        createChildProcess(fileName, i);
    }

    for (int i = 1; i <= numChildren; i++) {
        wait(NULL);
    }

    return 0;
}