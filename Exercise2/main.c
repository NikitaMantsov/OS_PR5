#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signum) {
    int count = 0;
    count++;
    printf("Handler %d: Delaying for 1 second. Signal %d received.\n", count, signum);
    sleep(1);
}

int main(int argc, char *argv[]) {

    int numHandlers;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <numberOfHandlers>\n", argv[0]);
        return 1;
    }

    numHandlers = atoi(argv[1]);

    if (numHandlers < 1) {
        fprintf(stderr, "NumberOfHandlers should be greater than 0.\n");
        return 1;
    }

    for (int i = 0; i < numHandlers; i++) {
        if (signal(SIGINT, signalHandler) == SIG_ERR) {
            fprintf(stderr, "Error registering handler for SIGINT.\n");
            return 1;
        }
    }

    printf("Waiting for signal handlers.\n");

    while (1) {
        // Wait for signals and let the handlers do their job
    }

    return 0;
}