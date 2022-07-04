#include <stdio.h>
#include <malloc.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "include/plugin.h"

#define TRUE 1

int printToDoPlugin(void *plugin) {
  char *(*plugin_function)(void);
  
  plugin_function = dlsym(plugin, "plugin_GetTodo");
  if (NULL == plugin_function) {
    perror("Error: Function not found");
    return -1;
  }
  printf("%s\n", plugin_function());
  return 0;
}

int pluginRun(void *plugin, int argc, char **argv) {
  int (*fun_lib)(int, char**);
  
  fun_lib = dlsym(plugin, "plugin_Run");
  if (NULL == fun_lib) {
    perror("Error: Function not found");
    exit(EXIT_FAILURE);
  }
   return fun_lib(argc, argv);
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

struct setting_plugin getPluginSetting(void *plugin) {
  struct setting_plugin (*getSetting)(void);

  getSetting = dlsym(plugin, "plugin_GetSetting");
  if (NULL == getSetting) {
    perror("Error: Function not found");
    exit(EXIT_FAILURE);
  }
  return getSetting();
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

int isDigit(char *const string)
{
  int size_string = strlen(string);
  for (int i = 0; i < size_string; i++) {
    if (string[i] < '0' || string[i] > '9') return 0;
  }
  return 1;
}

int enterNum(void) {
  char *num;

  while (TRUE) {
    num = enterString();
    if (isDigit(num)) {
      break;
   } else {
      printf("Error: the entered string is not a number.\nEnter again-->");
      free(num);
    }
  }

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
    
    printf("\n");
    printMenu(plugins, count);

    printf("Selection--> ");    
<<<<<<< HEAD
	  menu_item = enterNum();
    printf("\n");

    if(menu_item > count || menu_item <= 0) break;

    struct setting_plugin setting = getPluginSetting(plugins[menu_item - 1]);

    char **argv = malloc(sizeof(*argv) * setting.count_arg);
    for (int i = 0; i < setting.count_arg; ++i) {
      while(TRUE)
      {
        printf("Enter %d argument--> ", i + 1);    
        argv[i] = enterString();
        if (isDigit(argv[i])) {
          break;
        } else {
          printf("Error: the entered string is not a number.Enter again.\n");
          free(argv[i]);
        }
      }
    }

    result = pluginRun(plugins[menu_item - 1], setting.count_arg, argv);

    printf("\nResult: %d\n", result);

    for (int i = 0; i < setting.count_arg; ++i) {
      free(argv[i]);
    }
    free(argv);

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
