#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_LIST_USER 10 
#define SIZE_FIRST_NAME 30 
#define SIZE_LAST_NAME 30 
#define SIZE_NUMBER 15

typedef struct User
{
    char number[SIZE_NUMBER];
    char firstname[SIZE_FIRST_NAME];
    char lastname[SIZE_LAST_NAME];
} User;

typedef struct NodeUser
{
	struct User user;
	char empty;
} NodeUser;

enum ERROR_LIST
{
	ERROR_PTR = -1,
	ERROR_OUT = -2,	
	ERROR_EMPTY = -3,	
};

int init(struct NodeUser * const);
int del(struct NodeUser * const, int  ,int );
int add(struct NodeUser * const, int );
int show(struct NodeUser * const, int );
int find(struct NodeUser * const, int , char *);

int main(int argc, char** argv)
{
    struct NodeUser* listUser;
    char filter[SIZE_FIRST_NAME];
    char menu[] = "Меню:\n1 - Добавить запись\n2 - Посмотреть запись\n3 - Найти пользователя по имени\n4 - Удалить пользователя\n5 - Выйти";
    int index;
	
	listUser = malloc(sizeof(struct NodeUser) * SIZE_LIST_USER);

	for(int i = 0; i < SIZE_LIST_USER; i++)
		init(&listUser[i]);
		
	system("clear");
		
	while(1)
	{
		int numMenu;
		printf("%s\nВвод-->\t",menu);    
		scanf("%d",&numMenu);
		printf("\n");
		getchar();
				
		switch(numMenu)
		{
			case 1:
				//add user
				system("clear");
				if(add(listUser,SIZE_LIST_USER) < 0)
				{
					printf("Список полный\n");
				}
				system("clear");
				break;
			case 2:
				//show user
				system("clear");
				show(listUser,SIZE_LIST_USER);
				getchar();
				system("clear");
				break;
			case 3:
				//find user
				system("clear");
				printf("Введите номер удаляемого элемента:\t");    
				scanf("%s",filter);
				find(listUser,SIZE_LIST_USER,filter);
				getchar();getchar();
				system("clear");
				break;
			case 4:
				//del user
				system("clear");
				printf("Введите номер удаляемого элемента:\t");    
				scanf("%d",&index);
				del(listUser,SIZE_LIST_USER,index - 1);
				system("clear");
				break;
			case 5:
				//exit
				system("clear");
				goto finally;
				break;
			default:
				system("clear");
				break;
		}
	}

finally:
	free(listUser);
    return 0;
}

int init(struct NodeUser * const user)
{
	if(NULL == user)
		return ERROR_PTR;
	user->empty = 1;
	return 0;
}

int del(struct NodeUser * const users , int size ,int index)
{
	if(NULL == users)
		return ERROR_PTR;

	if(size <= index || index < 0)
		return ERROR_OUT;
		
	users[index].empty = 1;
	return 0;
}

int add(struct NodeUser * const users , int size)
{
	if(NULL == users)
		return ERROR_PTR;

	for(int i = 0; i < size; i++)
	{
		if(users[i].empty)
		{
			users[i].empty = 0;
			printf("Введите имя: ");
			scanf("%s",users[i].user.firstname);
			printf("Введите фамилию: ");
			scanf("%s",users[i].user.lastname);
			printf("Введите номер телефона: ");
			scanf("%s",(users[i].user.number));
			return 0;
		}
	}
	return ERROR_EMPTY;
}

int show(struct NodeUser * const users, int size)
{
	if(NULL == users)
		return ERROR_PTR;

	for(int i = 0; i < size; i++)
	{
		printf("%d пользователь:  \n",i + 1);
		if(users[i].empty)
		{
			printf("Пустой\n");
		}
		else
		{
			printf("Имя: %s\n",users[i].user.firstname);
			printf("Фамилию: %s\n",users[i].user.lastname);
			printf("Номер телефона: %s\n",users[i].user.number);
		}
		printf("\n");
	}
	return 0;
}

int find(struct NodeUser * const users, int size, char *filter)
{
	if(NULL == users)
		return ERROR_PTR;

	int count = 0;

	for(int i = 0; i < size; i++)
	{
		if(!(users[i].empty) && !strcmp(users[i].user.firstname,filter))
		{
			printf("%d пользователь:  \n",i + 1);
			printf("Имя: %s\n",users[i].user.firstname);
			printf("Фамилию: %s\n",users[i].user.lastname);
			printf("Номер телефона: %s\n",users[i].user.number);
			printf("\n");
			count++;
		}
	}
	if(!count)
		printf("Пользователь не найден \n");
	return ERROR_EMPTY;
}
