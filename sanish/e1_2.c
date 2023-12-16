#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_fd[1]);  // Close write end of the pipe in the child process

        char buffer[100];
        // Read data from the pipe
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Child process received: %s\n", buffer);

        close(pipe_fd[0]);  // Close read end of the pipe in the child process
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipe_fd[0]);  // Close read end of the pipe in the parent process

        char data[] = "Hello from the parent!";
        // Write data to the pipe
        write(pipe_fd[1], data, sizeof(data));

        close(pipe_fd[1]);  // Close write end of the pipe in the parent process
        wait(NULL);         // Wait for the child process to complete

        exit(EXIT_SUCCESS);
    }

    return 0;
}

