#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_data {
    char *str1;
    char *str2;
    char *result;
};

void *concat_strings(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    
    data->result = (char *)malloc(100);
    
    if (data->result != NULL) {
        snprintf(data->result, 100, "%s%s", data->str1, data->str2);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    struct thread_data data;
    
    data.str1 = "Hello, ";
    data.str2 = "world!";
    
    if (pthread_create(&thread, NULL, concat_strings, (void *)&data) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(thread, NULL);
    
    if (data.result != NULL) {
        printf("Concatenated string: %s\n", data.result);
        free(data.result);
    } else {
        fprintf(stderr, "Concatenation failed.\n");
    }
    
    return 0;
}

