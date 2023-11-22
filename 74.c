#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 10
#define MAX_WRITERS 5

int sharedData = 0; // Shared data that readers and writers access
int readersCount = 0; // Number of active readers
int writersCount = 0; // Number of active writers

sem_t readMutex, writeMutex, resourceAccess;

void* reader(void* arg) {
int readerId = *((int*)arg);
while (1) {
sem_wait(&readMutex);
readersCount++;
if (readersCount == 1) {
sem_wait(&resourceAccess);
}
sem_post(&readMutex);

// Read shared data
printf("Reader %d: Read %d\n", readerId, sharedData);

sem_wait(&readMutex);
readersCount--;
if (readersCount == 0) {
sem_post(&resourceAccess);
}
sem_post(&readMutex);

usleep(100000); // Sleep for a short time to simulate reading
}
return NULL;
}

void* writer(void* arg) {
int writerId = *((int*)arg);
while (1) {
sem_wait(&writeMutex);
writersCount++;
if (writersCount == 1) {
sem_wait(&resourceAccess);
}
sem_post(&writeMutex);

// Write to shared data
sharedData++;
printf("Writer %d: Wrote %d\n", writerId, sharedData);

sem_wait(&writeMutex);
writersCount--;
if (writersCount == 0) {

sem_post(&resourceAccess);
}
sem_post(&writeMutex);

usleep(200000); // Sleep for a short time to simulate writing
}
return NULL;
}

int main() {
int numReaders, numWriters;

printf("Enter the number of readers (1-%d): ", MAX_READERS);
scanf("%d", &numReaders);
if (numReaders < 1 || numReaders > MAX_READERS) {
printf("Invalid number of readers.\n");
return 1;
}

printf("Enter the number of writers (1-%d): ", MAX_WRITERS);
scanf("%d", &numWriters);
if (numWriters < 1 || numWriters > MAX_WRITERS) {
printf("Invalid number of writers.\n");
return 1;
}

// Initialize semaphores
sem_init(&readMutex, 0, 1);
sem_init(&writeMutex, 0, 1);
sem_init(&resourceAccess, 0, 1);

pthread_t readerThreads[MAX_READERS];
pthread_t writerThreads[MAX_WRITERS];

int readerIds[MAX_READERS];
int writerIds[MAX_WRITERS];

// Create reader threads
for (int i = 0; i < numReaders; i++) {
readerIds[i] = i + 1;
pthread_create(&readerThreads[i], NULL, reader, &readerIds[i]);
}

// Create writer threads
for (int i = 0; i < numWriters; i++) {
writerIds[i] = i + 1;
pthread_create(&writerThreads[i], NULL, writer, &writerIds[i]);
}

// Wait for reader and writer threads to finish (not typically done in a real scenario)
for (int i = 0; i < numReaders; i++) {
pthread_join(readerThreads[i], NULL);
}
for (int i = 0; i < numWriters; i++) {
pthread_join(writerThreads[i], NULL);
}

// Destroy semaphores
sem_destroy(&readMutex);
sem_destroy(&writeMutex);

sem_destroy(&resourceAccess);

return 0;
}
