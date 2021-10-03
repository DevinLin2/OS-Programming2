#include <stdlib.h>
#include <stdio.h>

void main() {
  int i;
  int *p2i = &i;
  int **p2p2i = &p2i;
  **p2p2i = 32;
  printf("%d\n", i);
}
