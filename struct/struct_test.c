#include <stdio.h>

struct unpacket
{
    char a;
    int b;
};

struct packed
{
    char a;
    int b;
}__attribute__((packed));

int main()
{
    char str[] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};

    struct packed * test1 = (struct packed *)str;
    struct unpacket * test2 = (struct unpacket *)str;;
    
    printf("Packed:\n");
    printf("char[0]: %c(%d)\n",test1->a,test1->a);
    printf("int[0]: %d\n",test1->b);
    printf("char[1]: %c(%d)\n",(test1+1)->a,(test1+1)->a);
    printf("int[1]: %d\n",(test1+1)->b);

    printf("Unpacked:\n");
    printf("char[0]: %c(%d)\n",test2->a,test2->a);
    printf("int[0]: %d\n",test2->b);
    printf("char[1]: %c(%d)\n",(test2+1)->a,(test2+1)->a);
    printf("int[1]: %d\n",(test2+1)->b);
    return 0;
}