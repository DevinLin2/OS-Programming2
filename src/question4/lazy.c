#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main() {
  // test for lazy allocaion
  struct timespec ts;
  double before, after;
  int *ptr = (int*)malloc(10 * sizeof(int));
  timespec_get(&ts, TIME_UTC);
  before = ts.tv_nsec;
  ptr[0] = 2;
  timespec_get(&ts, TIME_UTC);
  after = ts.tv_nsec;
  printf("Time used for first write in nanoseconds: %f\n", after - before);
  timespec_get(&ts, TIME_UTC);
  before = ts.tv_nsec;
  ptr[1] = 5;
  timespec_get(&ts, TIME_UTC);
  after = ts.tv_nsec;
  printf("Time used for second write in nanoseconds: %f\n", after - before);
  timespec_get(&ts, TIME_UTC);
  before = ts.tv_nsec;
  ptr[2] = 2;
  timespec_get(&ts, TIME_UTC);
  after = ts.tv_nsec;
  printf("Time used for third write in nanoseconds: %f\n", after - before);
  // test for if malloc has a fixed heap expansion size
  int *array1 = (int*)malloc(10*sizeof(int));
  for (int i = 0; i < 10; i++) {
    array1[i] = i;
  }
  int *array2 = (int*)malloc(30*sizeof(int));
  for (int i = 0; i < 30; i++) {
    array2[i] = i;
  }
  int array3[10];
  for (int i = 0; i < 10; i++) {
    array3[i] = i;
  }
  int array4[30];
  for (int i = 0; i < 30; i++) {
    array3[i] = i;
  }
  printf("Size of dynamically allocated arrays:\n");
  printf("Size of first array of size 10 ints: %li\n", sizeof(array1));
  printf("Size of first array of size 30 ints: %li\n", sizeof(array2));
  printf("Size of statically allocated arrays:\n");
  printf("Size of first array of size 10 ints: %li\n", sizeof(array3));
  printf("Size of first array of size 30 ints: %li\n", sizeof(array4));
}
