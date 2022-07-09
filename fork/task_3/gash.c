#include <malloc.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define TRUE 1 

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

int splitString(char ***split_text, char *string, char separator) {
  if (string == NULL) {
    return -1;
  }
  
  int size = strlen(string);
  int count = 1;
  int len = 1;
  
  (*split_text) = malloc(sizeof(char *) * count);
  (*split_text)[count - 1] = malloc(sizeof(char) * len);
  (*split_text)[count - 1][len - 1] = '\0';

  for (int i = 0; i < size; i++) {
    if (string[i] == separator) {
      (*split_text)[count - 1][len - 1] = '\0';

      count++;
      (*split_text) = realloc(*split_text, sizeof(char *) * count);

      len = 1;
      (*split_text)[count - 1] = malloc(sizeof(char) * len);
      (*split_text)[count - 1][len - 1] = '\0';

    } else {
      len++;
      (*split_text)[count - 1] = realloc((*split_text)[count - 1], sizeof(char) * len);
      (*split_text)[count - 1][len - 2] = string[i];
    } 
  }
  
  (*split_text) = realloc(*split_text, sizeof(char *) * (count + 1));
  (*split_text)[count] = (char *)NULL;

  return count;
}

int main(int argc, char **argv) {
  
  system("clear");

  while (TRUE) {
    char *command = NULL;
    char **argv = NULL;
    pid_t pid_child;
    int argc = 0;
    
    printf("gash > ");

    command = enterString();
    argc = splitString(&argv , command, ' ');

    pid_child = fork();

    if (0 == pid_child) {
      int error = execvp(argv[0], argv);
      perror("Error");
      exit(EXIT_FAILURE);
    } else {
      int exit_code;
      wait(&exit_code);
      if (exit_code != 0) {
        printf("Error: Closing process with code %d\n", exit_code);
      }
    }
  }
}