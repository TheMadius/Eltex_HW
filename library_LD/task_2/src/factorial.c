#include "../include/plugin.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct setting_plugin plugin_GetSetting(void) {
  struct setting_plugin setting;

  setting.count_arg = 1;
  setting.type_return = TYPE_INT;

  return setting;
}

char *plugin_GetTodo(void) {
  return "Finding factorial values";
}

int factorial(int num) {
  int accumulator = 1;

  if(0 == num) 
    return 1;
  for(int i = 1; i <= num; ++i)
    accumulator *= i;
  
  return accumulator;
}

int plugin_Run(int argc, char **argv) {
    if (argc != 1) {
      perror("Error:incorrect count arguments");
      exit(EXIT_FAILURE);
    }

    int a = atoi(argv[0]);

    if(0 > a)
    {
        perror("Error: negative number");
        exit(EXIT_FAILURE);
    }
   
    return factorial(a);
}