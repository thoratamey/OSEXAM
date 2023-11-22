#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void Kill(int signal) {
    printf("Parent is Terminated\n");
    exit(-1);
}

void child_task() {
    int counter = 0;
    while (counter!=11) {
        printf("Counter: %d\n", counter);
        counter++;
        // Simulate some work or processing here
        for (int i = 0; i < 11; i++) {
        }
    }
    printf("Child process: Task completed!\n");
    kill(getppid(), SIGTERM); // Send termination signal to parent
}

int main() {
    signal(SIGTERM, Kill);
    printf("Parent process started\n");

    pid_t child_pid = fork();
   
    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }
   
    if (child_pid == 0) {
        // Child process
        child_task();
        exit(0);
    } else {
        // Parent process
        while (1) {
            printf("Parent process running...\n");
            sleep(2); // Simulate some parent activity
        }
    }

    return 0;
}
