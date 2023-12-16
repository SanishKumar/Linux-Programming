#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	char buffer[1024];
	int fd;
	ssize_t bytes_read;
	fd=open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("Enter text \n");
while(1) {
	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	write(fd,buffer,bytes_read);
	if (buffer[0] == '$'){
	break;
}
}
printf("Input Saved!");
close(fd);
return 0;
}
