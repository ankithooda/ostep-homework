#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE
#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PIPE_SIZE 65536
#define LOOPS 100000

/*
  PROCESS 1 (Parent)
  WRITE PIPE 1        NO BLOCK
  READ PIPE 2         BLOCK

  PROCESS 2 (Child)
  READ PIPE 1         NO BLOCK
  WRITE PIPE 2        NO BLOCK
  ---
  2nd Iter
  READ PIPE 1         BLOCK
*/
int main() {
  int first_pipe[2], second_pipe[2];

  if (pipe(first_pipe) == -1) {
    fprintf(stderr, "%s\n", "Cannot open pipe");
  }
  if (pipe(second_pipe) == -1) {
    fprintf(stderr, "%s\n", "Cannot open pipe");
  }

  pid_t rc = fork();


  if (rc == -1) {
    exit(EXIT_FAILURE);
  } else if (rc == 0) {

    close(first_pipe[1]);
    close(second_pipe[0]);

    char buf;
    while (1) {
      read(first_pipe[0], &buf, 1);
      write(second_pipe[1], "X", 1);
    }
    close(first_pipe[0]);
    close(second_pipe[1]);
    exit(EXIT_SUCCESS);

  } else {

    close(first_pipe[0]);
    close(second_pipe[1]);

    char buf;
    // Write to pipe.
    while (1) {
      write(first_pipe[1], "X", 1);
      read(second_pipe[0], &buf, 1);
    }
    wait(NULL);
  }
  exit(EXIT_SUCCESS);
}
