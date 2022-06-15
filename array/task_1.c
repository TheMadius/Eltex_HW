// 1. Вывести квадратную матрицу по заданному N.

#include "stdio.h"
#define N 5

int main(int argc, char** argv)
{
    int arr[N][N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arr[i][j] = i*N + (j + 1);
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }

}