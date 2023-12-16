#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	const char *filename = "file1";
	int fd = open(filename, O_RDONLY);
	char ch;
	while(1){
		ssize_t bytes_read = read(fd,&ch,1);
		if (bytes_read == 0){
			break;
		}
		write(STDOUT_FILENO, &ch, 1);
	}
	close(fd);
return 0;
}
