#include <stdio.h>
#include <pthread.h>
int N=10;
pthread_mutex_t mutex;
pthread_cond_t odd_condition;
pthread_cond_t even_condition;
int next_number = 1;
void* odd_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (next_number > N) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        if (next_number % 2 == 0) {
            pthread_cond_wait(&odd_condition, &mutex);
        } else {
            printf("%d ", next_number);
            next_number++;
        }
        pthread_cond_signal(&even_condition);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void* even_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (next_number > N) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        if (next_number % 2 != 0) {
            pthread_cond_wait(&even_condition, &mutex);
        } else {
            printf("%d ", next_number);
            next_number++;
        }
        pthread_cond_signal(&odd_condition);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&odd_condition, NULL);
    pthread_cond_init(&even_condition, NULL);
    pthread_t odd_tid, even_tid;
    pthread_create(&odd_tid, NULL, odd_thread, NULL);
    pthread_create(&even_tid, NULL, even_thread, NULL);
    pthread_join(odd_tid, NULL);
    pthread_join(even_tid, NULL);
    printf("\n");
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&odd_condition);
    pthread_cond_destroy(&even_condition);
    return 0;
}
