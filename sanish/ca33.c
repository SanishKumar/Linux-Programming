#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid;
	pid= getpid();
	printf("current process ID is %d\n", pid);
	printf("forking a child process \n");
	pid=fork();
	if (pid==0){
		sleep(10);
		for(int i=0; i<5; i++){
			printf("%s\n","sanish");
		}
	}else{
		int num, reversedNum = 0, remainder, originalNum;

		    num = 121;
		    originalNum = 121;

		    // Reverse the number
		    while (num != 0) {
			remainder = num % 10;
			reversedNum = reversedNum * 10 + remainder;
			num /= 10;
		    }

		    if (originalNum == reversedNum) {
			printf("%d is a palindrome number.\n", originalNum);
		    } else {
			printf("%d is not a palindrome number.\n", originalNum);
		    }
	}
	return 0;
}
