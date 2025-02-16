#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void write_str(int fd, const char *str) {
    write(fd, str, strlen(str));
}

void write_int(int fd, int value) {
    char buffer[20];
    int i = 0;
    int is_negative = 0;

    if (value == 0) {
        write(fd, "0", 1);
        return;
    }

    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    while (i > 0) {
        write(fd, &buffer[--i], 1);
    }
}

void write_float(int fd, float value, int precision) {
    int integer_part = (int)value;
    write_int(fd, integer_part);
    write(fd, ".", 1);

    float fractional_part = value - integer_part;
    for (int i = 0; i < precision; i++) {
        fractional_part *= 10;
        int digit = (int)fractional_part;
        write(fd, &"0123456789"[digit], 1);
        fractional_part -= digit;
    }
}

int main() {
    const char *filename = "lab4q3.txt";
    int fd = creat(filename, 0644);
    if (fd == -1) {
        write(STDERR_FILENO, "Error\n", 20);
        exit(1);
    }

    write_str(fd, "Integer (%d): ");
    write_int(fd, 12345);
    write_str(fd, "\n");

    write_str(fd, "Negative Integer (%d): ");
    write_int(fd, -9876);
    write_str(fd, "\n");

    write_str(fd, "Float (%f): ");
    write_float(fd, 3.14159, 5);
    write_str(fd, "\n");

    write_str(fd, "Character (%c): ");
    write(fd, "A", 1);
    write_str(fd, "\n");

    write_str(fd, "String (%s): ");
    write_str(fd, "Hello, World!");
    write_str(fd, "\n");

    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Error\n", 31);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);
    return 0;
}