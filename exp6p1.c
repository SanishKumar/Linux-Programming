#include <stdio.h>
#include <pthread.h>

char *a;

void *func(){
	printf("In thread function \n");
	pthread_exit("Exit thread function \n");
}

int main(){
	pthread_t thread1;
	void *result;
	
	printf("In main thread \n");
	
	pthread_create(&thread1, NULL, func, NULL);
	
	pthread_join(thread1, &result);
	
	printf("%s \n", (char*)result);
	
	return 0;
}
