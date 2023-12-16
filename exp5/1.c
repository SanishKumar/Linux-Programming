#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Include this header for wait

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("Child %d (PID: %d) created by Parent (PID: %d)\n", i + 1, getpid(), getppid());
            break;
        }
        // Parent process should wait for child to complete before creating another child
        wait(NULL);
    }

    return 0;
}

