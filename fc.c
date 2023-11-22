#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int n = 5; // Factorial of 5
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        unsigned long long fact = factorial(n);
        printf("Factorial of %d is %llu\n", n, fact);
    } else {
        // Parent process
        wait(NULL); // Wait for child process to complete
        printf("Child process completed\n");
    }

    return 0;
}
