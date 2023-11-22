#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
printf("Thorat Amey Arun\n23MCS1004\n");
pid_t pid[3];
// Create three child processes
for (int i = 0; i < 3; i++) {
pid[i] = fork();
if (pid[i] == -1) {
perror("Fork failed");
exit(1);
} else if (pid[i] == 0) { // Child process
printf("Child %d started\n", i + 1);
if (i == 2) {
printf("Child 3 terminates\n");
exit(0);
} else {
sleep(3 - i);
printf("Child %d terminates\n", i + 1);
exit(0);
}
}
}
// Parent process
for (int i = 0; i < 3; i++) {
waitpid(pid[i], NULL, 0);
}
printf("Parent process terminates\n");
return 0;
}
