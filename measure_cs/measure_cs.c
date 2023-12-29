#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t rc = fork();

  if (rc == -1) {
    exit(EXIT_FAILURE);
  } else if (rc == 0) {
    // Child process
  } else {
    // Parent process
  }
  exit(EXIT_SUCESS);
}
