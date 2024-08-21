#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

int main(int argc, char *argv[]) {
    FILE *source_file, *dest_file;
    int ch;
    
    source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    dest_file = fopen(argv[2], "w");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        exit(1);
    }

    while ((ch = fgetc(source_file)) != EOF) {
        if (fputc(ch, dest_file) == EOF) {
            perror("Error writing");
            fclose(source_file);
            fclose(dest_file);
            exit(1);
        }
    }

    if (ferror(source_file)) {
        perror("Error reading");
        fclose(source_file);
        fclose(dest_file);
        exit(1);
    }

    fclose(source_file);
    fclose(dest_file);

    printf("File copied successfully.\n");
    return 0;
}