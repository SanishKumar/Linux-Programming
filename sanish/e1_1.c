#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 5
#define MAX_ACCESS_TIME 2

int shared_resource = 0;
pthread_mutex_t mutex;

void *access_resource(void *thread_id) {
    int id = *(int *)thread_id;

    int access_time = rand() % (MAX_ACCESS_TIME + 1);
    printf("Thread %d is accessing the resource for %d seconds.\n", id + 1, access_time);
    sleep(access_time);

    // Lock the mutex before accessing the shared resource
    pthread_mutex_lock(&mutex);

    // Critical section: Access the shared resource
    shared_resource++;
    printf("Thread %d updated the shared resource to %d.\n", id + 1, shared_resource);

    // Unlock the mutex after accessing the shared resource
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create and launch threads
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, access_resource, &thread_ids[i]) != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < MAX_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads have completed.\n");

    // Destroy the mutex
    if (pthread_mutex_destroy(&mutex) != 0) {
        perror("Mutex destruction failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

