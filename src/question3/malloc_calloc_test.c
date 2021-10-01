#include <stdio.h>
#include <stdlib.h>

// test of malloc and calloc are different on my system
void main() {
  int *mptr = (int*)malloc(10 * sizeof(int));
  if (mptr == NULL) {
    printf("Memory not allocated\n");
    exit(0);
  }
  int *cptr = (int*)calloc(10, sizeof(int));
  if (cptr == NULL) {
    printf("Memory not allocated\n");
    exit(0);
  }
  printf("The elements in malloc array are: \n");
  for (int i = 0; i < 10; i++) {
    printf("%d, ", mptr[i]);
  }
  printf("\n");
  printf("The elements in calloc array are: \n");
  for (int i = 0; i < 10; i++) {
    printf("%d, ", cptr[i]);
  }
  printf("\n");
}
