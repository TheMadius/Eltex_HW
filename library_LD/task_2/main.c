#include <stdio.h>
#include <malloc.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

int printToDoPlagin(void *plagin) {
  char *(*plagin_function)(void);
  
  plagin_function = dlsym(plagin, "plagin_GetTodo");
  if (NULL == plagin_function) {
    perror("Error: Function not found");
    return -1;
  }
  printf("%s\n", plagin_function());
  return 0;
}

int plaginRun(void *plagin, int first_arg, int second_arg) {
  int (*fun_lib)(int, int);
  
  fun_lib = dlsym(plagin, "plagin_Run");
  if (NULL == fun_lib) {
    perror("Error: Function not found");
    exit(EXIT_FAILURE);
  }
   return fun_lib(first_arg, second_arg);
}

int printMenu(void **array_plagins, int count_plagins) {
  for(int i = 0; i < count_plagins; ++i) {
    printf("%d - ", i + 1);
    int error = printToDoPlagin(array_plagins[i]);
    if (error < 0) {
      return error;
    }
  }
  printf("0 - Exit\n");
  return 0;  
}

void **getPlaginsPointer(char **name, int count_name) {
  void **plagins = malloc(sizeof(*plagins) * count_name);

  for (int i = 0; i < count_name; ++i) {
    plagins[i] = dlopen(name[i], RTLD_LAZY);
    if (plagins[i] == NULL) {
      printf("Error: Library %s can't open\n", name[i]);
      free(plagins);
      return NULL;
    }
  }

  return plagins;
}

int closePlagin(void **array_plagins, int count_plagins) {
  for(int i = 0; i < count_plagins; ++i) {
    dlclose(array_plagins[i]);
  }
  return 0;  
}

char *enterString(void) {
  char *text = malloc(sizeof(*text));
  int size = 0;
 
  while (TRUE) {
    text[size] = getchar();
    size++;

    if (text[size - 1] == '\n') {
      text[size - 1] = '\0';
      break;
    }

    text = realloc(text, sizeof(*text) * (size + 1));
  }
  return text;
}

int enterNum(void) {
  char *num = enterString();
  int number = atoi(num);
  free(num);
  
  return number;
}

int main(int argc, char **argv) {
  char **name_plagins;
  void **plagins;
  int count;
  
  printf("Enter number of plugins: ");
  count = enterNum();

  name_plagins = malloc(sizeof(*name_plagins) * count);
  for (int i = 0; i < count; ++i) {
    printf("Enter name plugin (%d): ", i + 1);
    name_plagins[i] = enterString();
  }

  plagins = getPlaginsPointer(name_plagins, count);
  if(NULL == plagins) goto finally;

  while (TRUE) {
    int menu_item, first_arg, second_arg, result;
    printMenu(plagins, count);

    printf("Selection--> ");    
	  menu_item = enterNum();

    if(menu_item > count || menu_item <= 0) break;

    printf("\nEnter first argument--> ");    
	  first_arg = enterNum();
	  printf("Enter second argument--> ");    
	  second_arg = enterNum();

    result = plaginRun(plagins[menu_item - 1], first_arg, second_arg);

    printf("Result: %d\n", result);
  }
  
  closePlagin(plagins, count);
  free(plagins);

finally:
  for (int i = 0; i < count; ++i) {
    free(name_plagins[i]);
  }
  free(name_plagins);

  return 0;
}