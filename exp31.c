#include<fcntl.h>
#include<unistd.h>
int main(){
	int source_fd, new_fd;
	off_t size, midpoint;
	char buffer[4096];
	source_fd = open("file1", O_RDONLY);
	size=lseek(source_fd,0,SEEK_END);
	midpoint=size/2;
	new_fd=open("new.txt", O_WRONLY | O_CREAT, 0644);
	lseek(source_fd,midpoint,SEEK_SET);
	read(source_fd,buffer,size-midpoint);
	write(new_fd,buffer,size-midpoint);
	close(source_fd);
	close(new_fd);
return 0;
}
