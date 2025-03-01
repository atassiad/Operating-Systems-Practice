#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]){
    if (argc != 2){
        printf("What r u doing? I need two args");
        return 1;
    }

    int megabytestobytes = atoi(argv[1])*pow(2, 20);
    char *arr = malloc(sizeof(char)*megabytestobytes);

    while(1){
        for (int i = 0; i < megabytestobytes; i++){
            arr[i] = 'a';
        }
    }

    free(arr);
    return 0;
}