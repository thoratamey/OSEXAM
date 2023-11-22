#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }
   
    pid_t pid = atoi(argv[1]);
   
    if (kill(pid, SIGTERM) == 0) {
        printf("Termination signal sent to PID %d\n", pid);
    } else {
        perror("kill");
        return 1;
    }
   
    return 0;
}


