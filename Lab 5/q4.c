//Create a zombie (defunct) child process (a child with exit() call, but no corresponding wait() in the sleeping parent) and allow the init 
//process to adopt it (after parent terminates). Run the process as a background process and run the “ps” command.
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
        printf("Child Process:\n");
        printf("  PID: %d\n", getpid());       
        printf("  Parent PID: %d\n", getppid()); 

        
        sleep(5);  
        
        /* Child process exits */
        printf("Child exiting...\n");
        exit(0);
    }
    else {
        printf("Parent Process:\n");
        printf("  PID: %d\n", getpid());     
        printf("  Child PID: %d\n", pid);   

     
        printf("Parent sleeping for 60 seconds...\n");
        sleep(60);
        
        
        printf("Parent exiting...\n");
        exit(0);
    }
}
