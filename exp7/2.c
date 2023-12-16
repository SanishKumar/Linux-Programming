#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h> 

#define NUM_READERS 3
#define NUM_WRITERS 1

pthread_t readers[NUM_READERS];
pthread_t writers[NUM_WRITERS];

sem_t mutex;
sem_t wsem;
int read_count = 0;
bool terminate = false;

void *reader_thread(void *arg) {
    while (!terminate) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wsem);
        }
        sem_post(&mutex);

        // Reading
        printf("Reader is reading...\n");

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wsem);
        }
        sem_post(&mutex);
    }
    pthread_exit(NULL);
}

void *writer_thread(void *arg) {
    while (!terminate) {
        sem_wait(&wsem);
        
        // Writing
        printf("Writer is writing...\n");

        sem_post(&wsem);
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wsem, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader_thread, NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer_thread, NULL);
    }

    // Sleep for a while to let threads run
    sleep(5);

    // Set the terminate flag to true
    terminate = true;

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wsem);

    return 0;
}

