#include <stdio.h>
#include "include/my_math.h"

union Result
{
    int _int_c;
    double _double_c;
};

int main(int argc, char** argv)
{
    char menu[] = "Меню:\n1 - Найти сумму\n2 - Найти разность\n3 - Найти произведение\n4 - Найти частное\n";
    union Result c;
	int numMenu;
    int a, b;

	printf("%s\nВвод-->\t",menu);    
	scanf("%d",&numMenu);
	printf("\n");

	printf("\nВвод первого значения-->\t");    
	scanf("%d",&a);
	printf("\nВвод второго значения-->\t");    
	scanf("%d",&b);

    switch(numMenu)
    {
        case 1:
            c._int_c = addition( a, b );
            break;
        case 2:
            c._int_c = subtraction( a, b );
            break;
        case 3:
            c._int_c = multiplication( a, b );
            break;
        case 4:
            c._double_c = division( a,b );
            break;
        default:
            break;
    }

    if( 4 == numMenu )
        printf("Результат равен: %lf", c._double_c);
    else 
        printf("Результат равен: %d", c._int_c);

    return 0;
}