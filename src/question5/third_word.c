#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char input[100];
  int words = 0;
  printf("Enter 3 or more words or quit to quit program:\n");
  fgets(input, 100, stdin);
  while (strcmp(input, "quit\n") != 0) {
    for (int i = 0; i < 100; i++) {
      if (input[i] == ' ') {
        words++;
      }
    }
    if (words >= 2) {
      char *ptr = strtok(input, " ");
      ptr = strtok(NULL, " ");
      ptr = strtok(NULL, " ");
      printf("The third word in the phrase is: %s\n", ptr);
    } else {
      printf("Please enter 3 or more words\n");
    }
    words = 0;
    fgets(input, 100, stdin);
  }
  return 0;
}
