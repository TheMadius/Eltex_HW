#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define COUNT_PID 5 

int main(int argc, char **argv) {
  pid_t pid[COUNT_PID];
  pid[0] = fork();

  if (pid[0] == 0) {
    pid[1] = fork();
    if (pid[1] == 0) {
        printf("Process #%d: pid - %d ppid - %d\n", 4, getpid(), getppid());
        exit(EXIT_SUCCESS);
    } else {
      printf("Process #%d: pid - %d ppid - %d\n", 2, getpid(), getppid());
      waitpid(pid[1], NULL, 0);
      exit(EXIT_SUCCESS);
    }

  } else {
    pid[2] = fork();
    if (pid[2] == 0) {
      pid[3] = fork();
      if (pid[3] == 0) {
        printf("Process #%d: pid - %d ppid - %d\n", 5, getpid(), getppid());
        exit(EXIT_SUCCESS);
      } else {
        pid[4] = fork();
        if (pid[4] == 0) {
          printf("Process #%d: pid - %d ppid - %d\n", 6, getpid(), getppid());
          exit(EXIT_SUCCESS);
        } else {
          printf("Process #%d: pid - %d ppid - %d\n", 3, getpid(), getppid());
          waitpid(pid[3], NULL, 0);
          waitpid(pid[4], NULL, 0);
          exit(EXIT_SUCCESS);
        }
      }
    } else {
      printf("Process #%d: pid - %d ppid - %d\n", 1, getpid(), getppid());
      waitpid(pid[0], NULL, 0);
      waitpid(pid[2], NULL, 0);
      exit(EXIT_SUCCESS);
    }
  }
}
