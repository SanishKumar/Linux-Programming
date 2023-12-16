#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	const char *filename = "UPREGNO.txt";
	int fd = open(filename, O_RDONLY);
	off_t offset = lseek(fd, -7, SEEK_END);
	char ch[7];
	while(1){
		ssize_t bytes_read = read(fd, ch, 7);
		if(bytes_read == 0){
			break;
		}
		write(STDOUT_FILENO, ch, bytes_read);
	}
	close(fd);
return 0;
}
