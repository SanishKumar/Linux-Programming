#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void copyFile(const char *src, const char *dest) {
    int src_fd, dest_fd;
    char buffer[4096];
    ssize_t bytes_read;

    src_fd = open(src, O_RDONLY);
    if (src_fd == -1) {
        perror("open source file");
        exit(1);
    }

    dest_fd = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("create destination file");
        exit(1);
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("write to destination file");
            exit(1);
        }
    }

    close(src_fd);
    close(dest_fd);
}

void copyDirectory(const char *src_dir, const char *dest_dir) {
    DIR *dir;
    struct dirent *entry;
    struct stat stat_buf;
    char src_path[PATH_MAX];
    char dest_path[PATH_MAX];

    if ((dir = opendir(src_dir)) == NULL) {
        perror("opendir");
        exit(1);
    }

    if (mkdir(dest_dir, 0777) == -1) {
        perror("mkdir");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, entry->d_name);

        if (lstat(src_path, &stat_buf) == -1) {
            perror("lstat");
            exit(1);
        }

        if (S_ISDIR(stat_buf.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                copyDirectory(src_path, dest_path);
            }
        } else {
            copyFile(src_path, dest_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_directory destination_directory\n", argv[0]);
        exit(1);
    }

    copyDirectory(argv[1], argv[2]);

    printf("Files and directories copied successfully.\n");

    return 0;
}

