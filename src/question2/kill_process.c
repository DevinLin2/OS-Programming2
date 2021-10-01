#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main() {
  char buffer[20];
  system("ps -o pid= > output.txt");
  FILE *fp = fopen("output.txt", "r");
  int index = 0;
  system("ps");
  while(fgets(buffer, 20, fp)) {
    if (index != 0) {
      char kill_command[20];
      int pid;
      sscanf(buffer, "%d", &pid);
      sprintf(kill_command, "kill -9 %d", pid);
      system(kill_command);
      system("ps");
    }
    index++;
  }
}
