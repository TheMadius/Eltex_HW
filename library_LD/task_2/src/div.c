#include "../include/plugin.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct setting_plugin plugin_GetSetting(void) {
  struct setting_plugin setting;

  setting.count_arg = 2;
  setting.type_return = TYPE_INT;

  return setting;
}

char *plugin_GetTodo(void) {
  return "Finding the quotient of 2 values";
}

int plugin_Run(int argc, char **argv) {
    if (argc != 2) {
      perror("Error:incorrect count arguments");
      exit(EXIT_FAILURE);
    }

    int a = atoi(argv[0]);
    int b = atoi(argv[1]);

    if(0 == b)
    {
        perror("Error: division by 0");
        exit(EXIT_FAILURE);
    }

    return (a / b);
}