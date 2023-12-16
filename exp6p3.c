#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arg_struct {
    int arg1;
    int arg2;
    int arg3;
};

void *print_the_arguments(void *arg) {
    struct arg_struct *ar = (struct arg_struct *)arg;
    scanf("%d", &ar->arg3);
    scanf("%d", &ar->arg2);
    int *c = (int *)malloc(sizeof(int)); // Allocate memory for the result
    *c = ar->arg2 + ar->arg3;
    pthread_exit(c); // Pass the pointer to the result
}

int main() {
    pthread_t some_thread;
    struct arg_struct args;
    args.arg1 = 5;
    args.arg2 = 7;

    int *result; // Declare a pointer to store the result
    pthread_create(&some_thread, NULL, &print_the_arguments, &args);
    pthread_join(some_thread, (void **)&result); // Cast the result pointer

    // Now you can use the result
    printf("Result: %d\n", *result);

    // Free the memory allocated for the result
    free(result);

    return 0;
}

