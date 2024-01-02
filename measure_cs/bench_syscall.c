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
#define SAMPLES 100000
int main() {
  int pipe_ends[2];
  pipe(pipe_ends);
  unsigned long before, after;
  for (int i = 0; i < SAMPLES; i++) {
    before += __rdtsc();
    write(pipe_ends[0], NULL, 0);
    after += __rdtsc();
  }

  printf("Cycles - %ld\n", (after - before)/SAMPLES);
  exit(EXIT_SUCCESS);
}
