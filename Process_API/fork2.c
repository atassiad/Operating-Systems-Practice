#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    printf("parent in pid: (%d)\n", (int)getpid());
    fflush(stdout);
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    char buff1[100];
    char buff2[100];
    int rc = fork();
    if (rc == 0)
    {
        int fd = open("test1.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        printf("%d\n", fd);
        printf("entering child1 process at pid : (%d)\n", (int)getpid());
        fflush(stdout);
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);
        puts("this is a message from child 1");
        fflush(stdout);
        int n = read(STDIN_FILENO, buff1, sizeof buff1);
        write(fd, buff1, n);
    }
    else
    {
        int rc2 = fork();
        if (rc2 == 0)
        {
            int fd2 = open("test2.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
            printf("%d\n", fd2);
            printf("entering child2 process at pid : (%d)\n", (int)getpid());
            fflush(stdout);
            dup2(p2[0], STDIN_FILENO);
            dup2(p1[1], STDOUT_FILENO);
            puts("this is a message from child 2");
            fflush(stdout);
            int n = read(STDIN_FILENO, buff2, sizeof buff2);
            write(fd2, buff2, n);
        }
        else
        {
            printf("final parent in pid: (%d)\n", (int)getpid());
            waitpid(rc, &rc, 0);
            waitpid(rc2, &rc2, 0);
        }
    }
    return 0;
}