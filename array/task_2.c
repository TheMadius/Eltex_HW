#include "stdio.h"

#define N 10

int main(int argc, char** argv)
{
    int arr[N];
    
    //init array
    for(int i = 0; i < N; i++){
        arr[i] = i +1;
    }

    //swap element 
    for(int i = 0; i < (N / 2); i++){
        int temp = arr[i];
        arr[i] = arr[N - i - 1];
        arr[N - i - 1] = temp;
    }

    //print array
    for(int i = 0; i < N; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    return 0;
}