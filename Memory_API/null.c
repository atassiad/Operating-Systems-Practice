#include <stdio.h>
#include <stdlib.h>

int main(void){
    int * ptr = (int*)malloc(sizeof(int)*100);
    int *ptr2 = &ptr[50];
    free(ptr2);

    return 0;
}