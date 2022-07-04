#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>

void printFile(int fd) {
  int size_file;
  int error;
  char *buff;
  
  size_file = lseek(fd, 0, SEEK_END);
  if (size_file < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  error = lseek(fd, 0, SEEK_SET);
  if (error < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  buff = malloc(sizeof(*buff) * size_file);
  error = read(fd, buff, size_file);
  if (error < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  printf("%s\n", buff);

  free(buff);
}

void negotiableOutput(int fd) {
  char symbol;
  int error;
  int pos = lseek(fd, 0, SEEK_END);

  for(int i = pos - 1; i >= 0  ; --i) {
    error = lseek(fd, i, SEEK_SET);
    if (error < 0) {
     perror("Error");
      exit(EXIT_FAILURE);
    }

    error = read(fd, &symbol, 1);
    if (error < 0) {
     perror("Error");
      exit(EXIT_FAILURE);
    }

    printf("%c", symbol);
  }
  printf("\n");
}


int main(int argc, char **argv) {
  char *namefile = "test";
  char *message = "Hello, world!!!";
  int error;
  int fd;

  fd = open(namefile, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
  if (fd < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }
  
  error = write(fd, message, strlen(message)+1);
  if (error < 0) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  printFile(fd);
  negotiableOutput(fd);

  close(fd);
}