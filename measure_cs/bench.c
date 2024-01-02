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
int main() {
  int first_pipe[2], second_pipe[2];

  if (pipe(first_pipe) == -1) {
    fprintf(stderr, "%s\n", "Cannot open pipe");
  }
  if (pipe(second_pipe) == -1) {
    fprintf(stderr, "%s\n", "Cannot open pipe");
  }

  for (int i = 0; i < LOOPS; i++) {

  }
  
  //printf("%d,%d\n", fcntl(pipe_ends[0], F_GETPIPE_SZ), fcntl(pipe_ends[1], F_GETPIPE_SZ));
  pid_t rc = fork();


  if (rc == -1) {
    exit(EXIT_FAILURE);
  } else if (rc == 0) {
    close(pipe_ends[1]);

    /*
    while (read(pipe_ends[0], &buf, 1) > 0) {
      write(STDOUT_FILENO, &buf, 1);
    }
    */
    char *buf;
    buf = malloc(PIPE_SIZE * sizeof(char));

    FILE *outfile = fopen("child.out", "w");
    if (outfile == NULL) {
      fprintf(stderr, "%s\n", "Could not open write file");
    } else {
      fprintf(outfile, "%s\n", "File opened");
    }
    // Read from pipe.
    size_t read_count;
    while (1) {
      read_count = read(pipe_ends[0], buf, PIPE_SIZE);
      if (read_count > 0) {
        fprintf(outfile, "Read from pipe - %ld\n", read_count);
      } else {
        fprintf(outfile, "%s\n", "Could not read from pipe");
      }
      fflush(outfile);
      sleep(30);
    }
    close(pipe_ends[0]);
    exit(EXIT_SUCCESS);

  } else {

    close(pipe_ends[0]);
    char data[PIPE_SIZE];
    // Read from infile
    FILE *data_in = fopen("data.in", "r");
    size_t read_count = fread(data, 1, PIPE_SIZE, data_in);

    printf("Read %ld from data.in file\n", read_count);

    // Write to pipe.
    while (1) {
      size_t write_count = write(pipe_ends[1], data, PIPE_SIZE);
      printf("Wrote %ld to pipe\n", write_count);
    }
    wait(NULL);
  }
  exit(EXIT_SUCCESS);
}
