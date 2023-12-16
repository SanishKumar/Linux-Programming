#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid, a, b, c;
	pid = getpid();
	printf("current process ID is %d\n", pid);
	a=5;
	b=5;
	c=a+b;
	printf("Sum of two numbers is: %d\n", c);	
	
	printf("Forking a child process \n");
	pid = fork();
	if (pid == 0){
		printf ("child processnid: %d and its parent id: %d\n", getpid(),getppid());
		int arr[]={1,2,3,4,5};
		int max = arr[0];
		for(int i = 0; i < 5; i++){
			if (arr[i] > max){
				max = arr[i];
			}
		}
		printf("Max integer of the numbers is %d\n", max);
	}
	return 0;
}
