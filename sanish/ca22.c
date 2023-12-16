#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(){
	int fd = open("ca22.txt", O_CREAT | O_RDWR, 0644);
	
	const char *intext = "Learningisfreesoletslearn";
	ssize_t byteswritten = write(fd, intext, strlen(intext));
	
	off_t offset = lseek(fd, strlen("Learningisfree"), SEEK_SET);
	
	char buffer[100];
	ssize_t bytesread = read(fd, buffer, sizeof(buffer));
	
	printf("%s\n",buffer);
	close(fd);
	
	return 0;
}
