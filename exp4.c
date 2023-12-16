#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
int main(){
	DIR *dp;
	struct dirent *dptr;
	int b = mkdir("sanish_exp41",0777);
	dp=opendir("sanish_exp41");
	while(NULL !=(dptr = readdir(dp))){
		printf("\%s \n", dptr->d_name);
		printf("\%d \n", dptr->d_type);
	}
return 0;
}
