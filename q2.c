//Write a C program to load the binary executable of the previous program in a child process using the exec system call.
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        execl("./q1", "q1", NULL);
        
        perror("execl");
        exit(-1);
    }
    else {
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
}
