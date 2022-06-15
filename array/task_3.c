#include "stdio.h"

#define N 3

int main(int argc, char** argv)
{
    int arr[N][N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j <= N - 1 - i; j++){
            arr[i][j] = 0;
            arr[N - j - 1][N - i - 1] = 1;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }

}