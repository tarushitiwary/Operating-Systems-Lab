#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        char error[] = "Enter exactly 3 arguments\n";
        write(STDERR_FILENO, error, strlen(error));
        exit(1);
    }

    char *search_word = argv[1];
    char *filename = argv[2];

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        char error[] = "Can't open file\n";
        write(STDERR_FILENO, error, strlen(error));
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    int line_pos = 0;
    int bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                line[line_pos] = '\0';
                if (strstr(line, search_word) != NULL) {
                    write(STDOUT_FILENO, line, line_pos);
                    write(STDOUT_FILENO, "\n", 1);
                }
                line_pos = 0;
            } else {
                line[line_pos++] = buffer[i];
                if (line_pos >= BUFFER_SIZE - 1) {
                    line[BUFFER_SIZE - 1] = '\0';
                    if (strstr(line, search_word) != NULL) {
                        write(STDOUT_FILENO, line, BUFFER_SIZE - 1);
                        write(STDOUT_FILENO, "\n", 1);
                    }
                    line_pos = 0;
                }
            }
        }
    }

    if (line_pos > 0) {
        line[line_pos] = '\0';
        if (strstr(line, search_word) != NULL) {
            write(STDOUT_FILENO, line, line_pos);
            write(STDOUT_FILENO, "\n", 1);
        }
    }

    close(fd);
    return 0;
}