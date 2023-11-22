#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void segFaultHandler(int signal) {
    printf("\nSegmentation Fault (SIGSEGV) occurred.\n");

    exit(-1);
} 


int main() {
    signal(SIGSEGV, segFaultHandler);
    int arr[5];
    arr[10] = 42; // Accessing an element outside the bounds of the array
    printf("In array of 5 element we have access element on 9th pointer.\n");
    raise(SIGSEGV);
    return 0;
} 
