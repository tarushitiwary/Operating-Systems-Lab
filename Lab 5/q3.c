//Write a program to create a child process. Display the process IDs of the process,parent and child (if any) in both the parent and child processes.
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        printf("Child Process:\n");
        printf("  PID: %d\n", getpid());      
        printf("  Parent PID: %d\n", getppid()); 
    }
    else {
        printf("Parent Process:\n");
        printf("  PID: %d\n", getpid());      
        printf("  Child PID: %d\n", pid);    
        wait(NULL);
    }
    
    return 0;
}
