#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t pid;

  pid = fork();

  if (pid == 0) {
    printf("Сhild : pid - %d ppid - %d\n", getpid(), getppid());
  } else {
    printf("Parent : pid - %d ppid - %d\n", getpid(), getppid());
  }
}
