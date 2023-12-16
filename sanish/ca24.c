#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {

    mkdir("BELIEVER", 0777);
    
    chdir("BELIEVER"); 

    FILE *file1 = fopen("file1.txt", "w");
    
    fclose(file1);

    FILE *file2 = fopen("file2.txt", "w");
    
    fclose(file2);

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    printf("Current directory: %s\n", cwd);

    chdir("..");

    getcwd(cwd, sizeof(cwd));
    
    printf("Parent directory: %s\n", cwd);

    return 0;
}

