#include <stdio.h>
#include <stdlib.h>

void main() {
  srand(10132002);
  FILE *fp = fopen("tasks.txt", "w+");
  for (int i = 1; i <= 100; i++) {
    fprintf(fp, "%d %d %d\n", rand()%256, 1+rand()%100, 1+rand()%25);
  }
  fclose(fp);
}
