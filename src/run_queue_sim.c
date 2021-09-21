#include <stdio.h>
#include <time.h>

struct task {
  int prio;
  int burst;
  int arrivalDelay;
}

main() {
  struct task ready[100];
  FILE *fp = fopen("tasks.txt", "r");
  char buff[20];
  char *line;
  int index = 0;
  // adding tasks to ready queue
  while (fgets(buff, 20, fp)) {
    int prio, burst, delay;
    sscanf(buff, "%d %d %d", &prio, &burst, &delay);
    struct task t = {prio, burst, delay};
    ready[index] = t;
    index++;
  }
  // ready now contains all tasks specified in file
  // ready is now a functioning ready queue
}
