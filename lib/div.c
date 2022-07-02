#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

double divs(int a, int b)
{
    if(0 == b)
<<<<<<< HEAD
    {
        perror("Error: division by 0");
        exit(EXIT_FAILURE);
    }
    return a / (double)b;
}
=======
        return 0;
    return (a / (double)b);
}
>>>>>>> 4f86532b513795b5ccd341f92748d6849bb6c597
