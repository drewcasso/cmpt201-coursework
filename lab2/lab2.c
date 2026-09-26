#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  // declarations for file path input
  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char;

  while (1) {
    printf("Enter programs to run: ");
    num_char = getline(&buff, &size, stdin);

    // getline error catch
    if (num_char == -1) {
      perror("getline error");
      exit(EXIT_FAILURE);
    }

    if (num_char > 0 && buff[num_char - 1] == '\n') {
      buff[num_char - 1] = '\0';
    }

    pid_t pid = fork();

    if (pid == -1) {
      // fork error catch
      perror("fork error");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // child
      execlp(buff, buff, NULL);
      perror("exec failure");
      exit(EXIT_FAILURE);
    } else {
      // parent
      int status;
      waitpid(pid, &status, 0);
    }
  }
  free(buff);
  return 0;
}
