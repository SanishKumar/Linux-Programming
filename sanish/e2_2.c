#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_INCREMENTS 1000000

int shared_variable = 0;

void *increment_shared_variable(void *thread_id) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        shared_variable++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        int result = pthread_create(&threads[i], NULL, increment_shared_variable, (void *)i);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %ld\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of the shared variable: %d\n", shared_variable);

    return 0;
}

