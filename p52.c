#include <stdio.h>
#include <pthread.h>
void *addition_thread(void *arg) {
printf("Addition Thread: Thread ID = %ld\n", (long)pthread_self());
int result = 2 + 3;
printf("Addition Thread: Result = %d\n", result);
pthread_exit(NULL);
}
void *odd_even_thread(void *arg) {
printf("Odd Even Thread: Thread ID = %ld\n", (long)pthread_self());
int number = 7;
if (number % 2 == 0) {
printf("Odd/Even Thread: %d is even.\n", number);
} else {
printf("Odd/Even Thread: %d is odd.\n", number);
}
pthread_exit(NULL);
}
int main() {
pthread_t thread1, thread2;
pthread_create(&thread1, NULL, addition_thread, NULL);
pthread_create(&thread2, NULL, odd_even_thread, NULL);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
return 0;
}
