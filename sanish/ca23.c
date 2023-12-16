#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd = open("UPREGNO.txt", O_RDONLY);
	
	char buffer[1];
	ssize_t readb;
	int lc = 0;
	
	while((readb = read(fd, buffer, sizeof(buffer))) > 0){
		if (buffer[0] == '\n'){
			lc++;
		}
	}
	close(fd);
	
	if (readb == 0 && lc > 0){
		lc++;
	}
	printf("%d\n", lc);
	
	return 0;
}
