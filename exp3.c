#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <first|second>\n", argv[0]);
        return 1;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    const char *halfChoice = argv[3];

    int inputFd = open(inputFile, O_RDONLY);
    if (inputFd == -1) {
        perror("Error opening input file");
        return 1;
    }

    off_t fileSize = lseek(inputFd, 0, SEEK_END);
    off_t halfSize = fileSize / 2;

    lseek(inputFd, 0, SEEK_SET);

    int outputFd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFd == -1) {
        perror("Error opening output file");
        close(inputFd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    if (strcmp(halfChoice, "first") == 0) {
        while ((bytesRead = read(inputFd, buffer, sizeof(buffer))) > 0 && halfSize > 0) {
            ssize_t bytesToWrite = (halfSize < bytesRead) ? halfSize : bytesRead;
            write(outputFd, buffer, bytesToWrite);
            halfSize -= bytesToWrite;
        }
    } else if (strcmp(halfChoice, "second") == 0) {
        lseek(inputFd, halfSize, SEEK_SET); // Move the file pointer to the second half
        while ((bytesRead = read(inputFd, buffer, sizeof(buffer))) > 0) {
            write(outputFd, buffer, bytesRead);
        }
    } else {
        fprintf(stderr, "Invalid half choice. Use 'first' or 'second'.\n");
    }

    close(inputFd);
    close(outputFd);

    return 0;
}

