#include "stdio.h"
#define N 4

int main(int argc, char** argv)
{
    int arr[N][N];
    int dim = N;
    int acc = 0;
    int i, j;

    //Algorithm
    for(int k = 0; k < (N / 2); k++ )
    {
        for(int num = 0; num < (dim-1)*4; num++)
        {
            switch (num / (dim - 1))
            {
                case 0:
                    i = 0;
                    j = num % (dim-1);
                    break;
                case 1:
                    i = num % (dim-1);
                    j = dim - 1;
                    break;
                case 2:
                    i = dim - 1;
                    j = dim - 1 - (num % (dim-1));
                    break;
                case 3:
                    i = dim - 1 - (num % (dim-1));
                    j = 0;
                    break;
            }
            arr[k + i][k + j] = acc + num + 1;
        }
        acc += (dim - 1)*4;
        dim -= 2;
    }

    if(N % 2 != 0)
        arr[N/2][N/2] = N*N;
    
    //print mtrix
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }

}