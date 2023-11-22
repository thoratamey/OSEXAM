#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READERS 10
#define MAX_WRITERS 5

int shared_resource = 0;
int reader_count = 0;

pthread_mutex_t mutex;
pthread_cond_t reader_condition;
pthread_cond_t writer_condition;

void* reader(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (reader_count == -1) {
            pthread_cond_wait(&reader_condition, &mutex);
        }
        reader_count++;
        if (reader_count == 1) {
            pthread_cond_wait(&writer_condition, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Reading from the shared resource
        printf("Reader %ld read: %d\n", (long)arg, shared_resource);
        usleep(100000); // Simulate some reading

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            pthread_cond_signal(&writer_condition);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* writer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (reader_count != 0) {
            pthread_cond_wait(&writer_condition, &mutex);
        }
        reader_count = -1;
        pthread_mutex_unlock(&mutex);

        // Writing to the shared resource
        shared_resource++;
        printf("Writer %ld wrote: %d\n", (long)arg, shared_resource);
        usleep(100000); // Simulate some writing

        pthread_mutex_lock(&mutex);
        reader_count = 0;
        pthread_cond_broadcast(&reader_condition);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[MAX_READERS];
    pthread_t writers[MAX_WRITERS];
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&reader_condition, NULL);
    pthread_cond_init(&writer_condition, NULL);

    int num_readers, num_writers;

    printf("Enter the number of readers (up to %d): ", MAX_READERS);
    scanf("%d", &num_readers);
    if (num_readers > MAX_READERS) {
        printf("Number of readers exceeds the limit.\n");
        return 1;
    }

    printf("Enter the number of writers (up to %d): ", MAX_WRITERS);
    scanf("%d", &num_writers);
    if (num_writers > MAX_WRITERS) {
        printf("Number of writers exceeds the limit.\n");
        return 1;
    }

    for (long i = 0; i < num_readers; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }

    for (long i = 0; i < num_writers; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&reader_condition);
    pthread_cond_destroy(&writer_condition);

    return 0;
}
