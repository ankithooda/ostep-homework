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
#define SAMPLES 500000
int main() {
  int pipe_ends[2];
  char buf;
  pipe(pipe_ends);
  ssize_t c;
  unsigned long before, after, diff = 0;
  for (int i = 0; i < SAMPLES; i++) {
    before = __rdtsc();
    c = write(pipe_ends[1], "X", 1);
    c = read(pipe_ends[0], &buf, 1);
    after = __rdtsc();
    diff = diff + (after - before);
    //printf("%ld\n", c);
  }

  printf("Cycles - %ld\n", diff/SAMPLES);
  exit(EXIT_SUCCESS);
}
