// Jonathan Collazo || CSCE 3600 || EUID: 11535014

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    const char* name;
    pid_t pid = fork();

    // In child process
    if(pid == 0)
    {
        printf("child: %d started\n", getpid());
        printf("child:  parent  =  %d\n", getppid());
        printf("child is about to sleep: ....\n");
        sleep(20);
        printf("child has woken up.\n");
    }

    // In parent process
    else if(pid > 0)
    {
        printf("parent: %d started\n",getpid());
        printf("parent:  parent  = %d\n",getppid());

    }

    // Process was not created
    else
    {
        perror("fork error");
    }

    (pid==0) ? (name = "child") : (name = "parent");

    printf("%s is about to exit\n", name);

    return 0;
}
