#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void){
    printf("hello (pid:%d)\n", (int)getpid());
    int x = 100;
    int child = fork(); //stores child pid value, creates copy of parents memory space
    if (child < 0){
        printf("error");
        return 1;
    }
    else if (child == 0){
        //child (new process)
        x=75;
        printf("child x: %i\n", x);
    }
    else { //parent
        x = 50;
        printf("parent x: %i\n", x);
    }

    return 0;
}