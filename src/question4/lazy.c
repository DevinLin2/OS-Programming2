#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main() {
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
}
