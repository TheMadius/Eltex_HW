#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char menu[] = "Меню:\n1 - Найти сумму\n2 - Найти разность\n3 - Найти произведение\n4 - Найти частное\n";
    int (*fun_lib)(int,int);
	int numMenu, result, first_value, second_value;

    void *lib = dlopen("bin/libmy_math.so",RTLD_LAZY);
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
            fun_lib = dlsym( lib, "addition");
            break;
        case 2:
            fun_lib = dlsym( lib, "subtraction");
            break;
        case 3:
            fun_lib = dlsym( lib, "multiplication");
            break;
        case 4:
            fun_lib = dlsym( lib, "division");
            break;
        default:
            fun_lib = NULL;
            break;
    }

    result = fun_lib( first_value, second_value );
    printf("Результат равен: %d\n", result);

    dlclose(lib);
    return 0;
}