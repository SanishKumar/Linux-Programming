#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "mkdir ./sanish_system";

    int status = system(command);

    if (status == 0) {
        printf("Directory created successfully\n");
    } else {
        perror("Error creating directory");
    }

    return 0;
}

