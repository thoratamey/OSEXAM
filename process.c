#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Thorat Amey Arun\n23MCS1004\n");
    pid_t pid = fork(); // create a new process
   
    if (pid == -1)
        printf("Failed to create a new process\n");
    else if (pid == 0)
        printf("PID - %d PPID: %d\n", getpid(), getppid());
    else
        printf("PID %d PID: %d\n", getpid(), pid);

    return 0;
}
