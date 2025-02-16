//Write a C program to block a parent process until the child completes using a wait system call.#include <sys/types.h>
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
        execlp("/bin/ls", "ls", NULL);
        perror("execlp");
        exit(-1);
    }
    else {
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
}
