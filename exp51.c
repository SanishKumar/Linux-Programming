#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Recursive function to create child processes
void createChildProcesses(int n) {
    if (n <= 0) {
        return;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This is the child process
        printf("Child process (PID: %d)\n", getpid());
        createChildProcesses(n - 1);
        exit(EXIT_SUCCESS);
    } else {
        // This is the parent process
        wait(NULL);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Please provide a positive integer 'n'.\n");
        return EXIT_FAILURE;
    }

    printf("Creating %d child processes...\n", (1 << n) - 1);

    createChildProcesses(n);

    return EXIT_SUCCESS;
}

