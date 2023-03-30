// Jonathan Collazo || CSCE 3600 || EUID: 11535014

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main()
{
    pid_t pid = fork();
    // In child process
    if (pid == 0)
    {
        exit(0);
    }
    // In parent process 
    else if (pid > 0)
    {
        sleep(5);
        system("ps -e -o pid,ppid,stat,user,cmd | grep $USER");
    }

    // Process was not created 
    else
    {
        perror("fork error");
        exit(1);
    }
    return 0;
}
