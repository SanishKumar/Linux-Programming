#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include<string.h>

int main() {
    int crtdir;
    crtdir = mkdir("exp4", 0777);
    if (crtdir == -1) {
        perror("mkdir");
        return 1; // Exit with an error code
    }

    // Change to the "exp4" directory
    if (chdir("exp4") == -1) {
        perror("chdir");
        return 1; // Exit with an error code
    }

    // Create a file inside the directory
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1; // Exit with an error code
    }

    const char *content = "This is the content of the file.";
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        return 1; // Exit with an error code
    }

    close(fd);

    // List the contents of the directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1; // Exit with an error code
    }

    struct dirent *entry;
    printf("Contents of the directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}

