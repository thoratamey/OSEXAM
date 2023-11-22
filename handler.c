#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler for Ctrl-Z (SIGTSTP)
void stopSignalHandler(int signal) {
    printf("\nCtrl-Z Signal (SIGTSTP) received. Stopping...\n");
    // Add your custom handling code here
    exit(0);
}

// Signal handler for Segmentation Fault (SIGSEGV)
void segFaultHandler(int signal) {
    printf("\nSegmentation Fault (SIGSEGV) occurred.\n");
    // Add your custom handling code here
    exit(-1);
}

// Signal handler for Divide by Zero Error (SIGFPE)
void divByZeroHandler(int signal) {
    printf("\nDivide by Zero Error (SIGFPE) occurred.\n");
    // Add your custom handling code here
    exit(-1);
}

int main() {
    // Install signal handlers
    signal(SIGTSTP, stopSignalHandler);  // Ctrl-Z
    signal(SIGSEGV, segFaultHandler);   // Segmentation fault
    signal(SIGFPE, divByZeroHandler);   // Divide by zero error

    printf("Running. Press Ctrl-Z to stop.\n");

    // Example code that triggers signals
    int a = 5;
    int b = 0;
    //Uncomment these lines to trigger signals
    raise(SIGSEGV);  // Uncomment to simulate Segmentation Fault
    raise(SIGFPE);   // Uncomment to simulate Divide by Zero Error
    int result = a / b;  // Uncomment to simulate Divide by Zero Error

    // Loop to keep the program running
    int counter = 0;
    while (1) {
        printf("Counter: %d\n", counter);
        counter++;
        // Simulate some work or processing here
        for (int i = 0; i < 100000000; i++) {
            // Just waste some time
        }
    }

    return 0;
}
