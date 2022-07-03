#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int divs(int a, int b)
{
    if(0 == b)
    {
        perror("Error: division by 0");
        exit(EXIT_FAILURE);
    }
    return a / (double)b;
}