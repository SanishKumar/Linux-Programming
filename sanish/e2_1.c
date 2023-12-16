#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t child_pid;
	child_pid = fork();
	
	if (child_pid == 0) {
		printf("Child process is executing.\n");
        	sleep(2); // Simulating some work in the child process
        	printf("Child process completed.\n");
        	exit(EXIT_SUCCESS);
	} else {
		// Parent process
		printf("Parent process is waiting for the child process.\n");
		wait(NULL); // Wait for the child process to complete
		printf("Parent process resumed after the child process completed.\n");
		exit(EXIT_SUCCESS);
    	}
    	return 0;
}
