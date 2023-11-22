#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// Function to compute factorial
unsigned long long factorial(int n) {
if (n <= 1)
return 1;
return n * factorial(n - 1);
}
// Function to compute Fibonacci
unsigned long long fibonacci(int n) {
if (n <= 0)
return 0;
else if (n == 1)
return 1;
else
return fibonacci(n - 1) + fibonacci(n - 2);
}
int main() {
int n;
printf("Thorat Amey Arun\n23MCS1004\n");
printf("Enter a number: ");
scanf("%d", &n);
pid_t pid = fork();
if (pid == -1) {
perror("Fork failed");
exit(1);
} else if (pid == 0) { // Child process
// Compute factorial
unsigned long long fact = factorial(n);
printf("Child process: Factorial of %d is %llu\n", n, fact);
} else { // Parent process
wait(NULL); // Wait for the child process to complete
// Compute Fibonacci
unsigned long long fib = fibonacci(n);
printf("Parent process: Fibonacci of %llu :", fib);
for (int i = 0; i < n; i++) {
            printf("%llu ", fibonacci(i));
        }
        printf("\n");
}
return 0;
}
