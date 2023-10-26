#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void printHelp() {
    printf("Simplified Command Processor\n");
    printf("Options:\n");
    printf("-h or --help: Display this help information\n");
    printf("-b or --buffer [size]: Specify the command buffer size (default is %d)\n", DEFAULT_BUFFER_SIZE);
}

int main(int argc, char *argv[]) {
    char user[100];

    printf("Enter your name: ");
    if (fgets(user, sizeof(user), stdin) == NULL) {
        perror("Error entering name");
        return 1;
    }

    user[strcspn(user, "\n")] = '\0';

    int bufferSize = DEFAULT_BUFFER_SIZE;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            bufferSize = atoi(argv[i + 1]);
            if (bufferSize < 1) {
                printf("Error: Invalid buffer size\n");
                return 1;
            }
            i++;
        }
    }

    char command[bufferSize];
    while (1) {
        printf("[%s]$: ", user);
        if (fgets(command, bufferSize, stdin) == NULL) {
            perror("Error entering a command");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "stop") == 0) {
            printf("Exiting the program\n");
            break;
        } else {
            int result = system(command);
            if (result == -1) {
                perror("Error executing the command");
            }
        }
    }

    printf("Waiting for 3 seconds...\n");
    sleep(3);

    system("clear");

    return 0;
}
