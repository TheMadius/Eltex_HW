#include <stdio.h>
#include <malloc.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

int printToDoPlugin(void *plugin) {
  char *(*plugin_function)(void);
  
  plugin_function = dlsym(plugin, "plagin_GetTodo");
  if (NULL == plugin_function) {
    perror("Error: Function not found");
    return -1;
  }
  printf("%s\n", plugin_function());
  return 0;
}

int pluginRun(void *plugin, int first_arg, int second_arg) {
  int (*fun_lib)(int, int);
  
  fun_lib = dlsym(plugin, "plugin_Run");
  if (NULL == fun_lib) {
    perror("Error: Function not found");
    exit(EXIT_FAILURE);
  }
   return fun_lib(first_arg, second_arg);
}

int printMenu(void **array_plugins, int count_plugins) {
  for(int i = 0; i < count_plugins; ++i) {
    printf("%d - ", i + 1);
    int error = printToDoPlugin(array_plugins[i]);
    if (error < 0) {
      return error;
    }
  }
  printf("0 - Exit\n");
  return 0;  
}

void **getPluginsPointer(char **name, int count_name) {
  void **plugins = malloc(sizeof(*plugins) * count_name);

  for (int i = 0; i < count_name; ++i) {
    plugins[i] = dlopen(name[i], RTLD_LAZY);
    if (plugins[i] == NULL) {
      printf("Error: Library %s can't open\n", name[i]);
      free(plugins);
      return NULL;
    }
  }

  return plugins;
}

int closePlagin(void **array_plugins, int count_plugins) {
  for(int i = 0; i < count_plugins; ++i) {
    dlclose(array_plugins[i]);
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
  char **name_plugins;
  void **plugins;
  int count;
  
  printf("Enter number of plugins: ");
  count = enterNum();

  name_plugins = malloc(sizeof(*name_plugins) * count);
  for (int i = 0; i < count; ++i) {
    printf("Enter name plugin (%d): ", i + 1);
    name_plugins[i] = enterString();
  }

  plugins = getPluginsPointer(name_plugins, count);
  if(NULL == plugins) goto finally;

  while (TRUE) {
    int menu_item, first_arg, second_arg, result;
    printMenu(plugins, count);

    printf("Selection--> ");    
	  menu_item = enterNum();

    if(menu_item > count || menu_item <= 0) break;

    printf("\nEnter first argument--> ");    
	  first_arg = enterNum();
	  printf("Enter second argument--> ");    
	  second_arg = enterNum();

    result = pluginRun(plugins[menu_item - 1], first_arg, second_arg);

    printf("Result: %d\n", result);
  }
  
  closePlagin(plugins, count);
  free(plugins);

finally:
  for (int i = 0; i < count; ++i) {
    free(name_plugins[i]);
  }
  free(name_plugins);

  return 0;
}