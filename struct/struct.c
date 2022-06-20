#include <stdio.h>
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

int init(struct NodeUser *);
int del(struct NodeUser (*)[], int  ,int );
int add(struct NodeUser (*)[], int );
int show(struct NodeUser (*)[], int );
int find(struct NodeUser (*)[], int , char *);

int main(int argc, char** argv)
{
    struct NodeUser listUser[SIZE_LIST_USER];
    char filter[SIZE_FIRST_NAME];
    char menu[] = "Меню:\n1 - Добавить запись\n2 - Посмотреть запись\n3 - Найти пользователя по имени\n4 - Удалить пользователя\n5 - Выйти";
    int index;
	
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
				if(add(&listUser,SIZE_LIST_USER) < 0)
					printf("Список полный\n");
				system("clear");
				break;
			case 2:
				//show user
				system("clear");
				show(&listUser,SIZE_LIST_USER);
				getchar();
				system("clear");
				break;
			case 3:
				//find user
				system("clear");
				printf("Введите номер удаляемого элемента:\t");    
				scanf("%s",filter);
				find(&listUser,SIZE_LIST_USER,filter);
				getchar();getchar();
				system("clear");
				break;
			case 4:
				//del user
				system("clear");
				printf("Введите номер удаляемого элемента:\t");    
				scanf("%d",&index);
				del(&listUser,SIZE_LIST_USER,index - 1);
				system("clear");
				break;
			case 5:
				system("clear");
				return 0;
				break;
			default:
				system("clear");
				break;
		}
	}
    return 0;
}

int init(struct NodeUser *user)
{
	user->empty = 1;
	return 0;
}

int del(struct NodeUser (*user)[], int size ,int index)
{
	if(size <= index || index < 0)
		return -1;
		
	(*user)[index].empty = 1;
	return 0;
}

int add(struct NodeUser (*user)[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if((*user)[i].empty)
		{
			(*user)[i].empty = 0;
			printf("Введите имя: ");
			scanf("%s",(*user)[i].user.firstname);
			printf("Введите фамилию: ");
			scanf("%s",(*user)[i].user.lastname);
			printf("Введите номер телефона: ");
			scanf("%s",((*user)[i].user.number));
			return 0;
		}
	}
	return -1;
}

int show(struct NodeUser (*user)[], int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("%d пользователь:  \n",i + 1);
		if((*user)[i].empty)
		{
			printf("Пустой\n");
		}
		else
		{
			printf("Имя: %s\n",(*user)[i].user.firstname);
			printf("Фамилию: %s\n",(*user)[i].user.lastname);
			printf("Номер телефона: %s\n",(*user)[i].user.number);
		}
		printf("\n");
	}
	return 0;
}

int find(struct NodeUser (*user)[], int size, char *filter)
{
	int count = 0;
	for(int i = 0; i < size; i++)
	{
		if(!((*user)[i].empty) && !strcmp((*user)[i].user.firstname,filter))
		{
			printf("%d пользователь:  \n",i + 1);
			printf("Имя: %s\n",(*user)[i].user.firstname);
			printf("Фамилию: %s\n",(*user)[i].user.lastname);
			printf("Номер телефона: %s\n",(*user)[i].user.number);
			printf("\n");
			count++;
		}
	}
	if(!count)
		printf("Пользователь не найден \n");
	return -1;
}
