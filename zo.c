#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
printf("Thorat Amey Arun\n23MCS1004\n");
pid_t child_pid = fork();
if (child_pid == 0) { // Child process
printf("Child process is sleeping\n");
sleep(5);
printf("Child process completed\n");
} else if (child_pid > 0) { // Parent process
printf("Parent process created a child with PID: %d\n",
child_pid);
wait(NULL); // Wait for the child to complete
printf("Parent process completed\n");
} else {
perror("Fork failed");
exit(1);
}
return 0;
}
