#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define LINES_PER_PAGE 20

void display_file(const char *filename);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        char error[] = "Enter at least 1 argument.\n";
        write(STDERR_FILENO, error, strlen(error));
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        display_file(argv[i]);
    }

    return 0;
}

void display_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        char error[] = "Can't open file\n";
        write(STDERR_FILENO, error, strlen(error));
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;
    int line_count = 0;
    int char_count = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            write(STDOUT_FILENO, &buffer[i], 1);
            char_count++;

            if (buffer[i] == '\n') {
                line_count++;
                if (line_count % LINES_PER_PAGE == 0) {
                    char prompt[] = "More\n";
                    write(STDOUT_FILENO, prompt, strlen(prompt));
                    
                    char input;
                    read(STDIN_FILENO, &input, 1);
                    
                    write(STDOUT_FILENO, "\r       \r", 9);

                    if (input == 'x' || input == 'X') {
                        close(fd);
                        return;
                    }
                }
            }
        }
    }

    close(fd);

    if (char_count > 0 && buffer[char_count - 1] != '\n') {
        write(STDOUT_FILENO, "\n", 1);
    }
}