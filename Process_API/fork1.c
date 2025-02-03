#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int child = fork();

    if (child < 0){
        printf("ERROR\n");
        return 1;
    }
    else if (child == 0){
        /*
        printf("child pid: %i\n", getpid());
        char*myargs[2];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = NULL;
        execvp(myargs[0], myargs); */
    }
    else {
        //int rvalue = wait(NULL); //wait returns the pid of the child process we're waiting on
        //printf("%i", rvalue);
        int * status = NULL; 
        int rvalue = waitpid(-1, status, WNOHANG);
        printf("child wait value: %i", rvalue);
    }


    return 0;
}