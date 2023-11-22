#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void divByZeroHandler(int signal) {
    printf("\nDivide by Zero Error (SIGFPE) occurred.\n");
    exit(-1);
}

int main() {
    signal(SIGFPE, divByZeroHandler);
    int numerator = 10;
    int denominator = 0;
    printf("10/0");
    int result = numerator / denominator; // Division by zero
    raise(SIGFPE);
    return 0;
}
