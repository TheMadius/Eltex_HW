#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char *plagin_GetTodo(void) {
  return "Finding the quotient of 2 values";
}

int plagin_Run(int a, int b) {
    if(0 == b)
    {
        perror("Error: division by 0");
        exit(EXIT_FAILURE);
    }
    return (a / b);
}