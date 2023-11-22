#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function
void stopSignalHandler(int signum) {
    printf("\nStop signal received. Stopping...\n");
    exit(0);
}

int main() {
    // Set up the signal handler
    signal(SIGTSTP, stopSignalHandler);

    printf("Running... Press Ctrl-Z to send a stop signal.\n");
    int counter=0;
    while (1) {
        printf("Counter: %d\n", counter);
        counter++;
        // Simulate some work or processing here
        for (int i = 0; i < 100000000; i++) {
            
        }
    }

    return 0;
}
