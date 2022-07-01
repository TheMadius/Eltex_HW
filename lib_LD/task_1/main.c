#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char menu[] = "Меню:\n1 - Найти сумму\n2 - Найти разность\n3 - Найти произведение\n4 - Найти частное\n";
    int (*fun_lib)(int,int);
	int numMenu, result, first_value, second_value;

    void *lib = dlopen("libmy_math.so",RTLD_LAZY);
    if( NULL == lib )
    {
        perror("Ошибка загрузки библиотеки");
        exit(-1);
    }

	printf("%s\nВвод-->\t",menu);    
	scanf("%d",&numMenu);

	printf("\nВвод первого значения-->\t");    
	scanf("%d",&first_value);
	printf("Ввод второго значения-->\t");    
	scanf("%d",&second_value);

    switch(numMenu)
    {
        case 1:
            fun_lib = dlsym( lib, "add");
            break;
        case 2:
            fun_lib = dlsym( lib, "sub");
            break;
        case 3:
            fun_lib = dlsym( lib, "mult");
            break;
        case 4:
            fun_lib = dlsym( lib, "divs");
            break;
        default:
            fun_lib = NULL;
            break;
    }

    result = fun_lib( first_value, second_value );
    printf("Результат равен: %d\n", result);

    return 0;
}