#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
// Function to be executed in the thread
void* thread_function(void* arg) {
char* name = (char*)arg;
printf("Thread '%s' started\n", name);
printf("Thread ID: %ld\n", pthread_self());
// Thread logic goes here
return NULL;
}
int main() {
char rn[] = "23MCS1004";
printf("Main thread\n");
printf("Main thread ID: %ld\n",pthread_self());
printf("Registration Number: %s\n", rn);
char t[] = "THORAT AMEY ARUN";
pthread_t thread;
pthread_create(&thread, NULL, thread_function, (void*)t);
pthread_join(thread, NULL);
return 0;
}
