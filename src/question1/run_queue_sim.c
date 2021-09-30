#include <stdio.h>
#include <string.h>
#include <time.h>

struct task {
  int pid;
  int prio;
  int burst;
  int arrivalDelay;
};

void main() {
  struct task ready[100];
  struct task run1[100];
  struct task run2[100];
  FILE *fp = fopen("tasks.txt", "r");
  char buff[20];
  char *line;
  int index = 0;
  int finished_tasks = 0;
  int tasks_in_ready_queue = 100;
  int time = 0;
  int time_slice = 10;
  int size_of_run1 = 0;
  int size_of_run2 = 0;
  int greatest_prio = -1;
  int task_running = 0;
  int i_of_to_run = -1;
  int queue_in_use = 1;
  int size = 100;
  // adding tasks to ready queue
  while (fgets(buff, 20, fp)) {
    int prio, burst, delay;
    // printf("%d\n", index);
    sscanf(buff, "%d %d %d", &prio, &burst, &delay);
    struct task t = {index, prio, burst, delay};
    // printf("size of struct %ld\n", sizeof(t));
    ready[index] = t;
    index++;
  }
  // ready now contains all tasks specified in file
  // ready is now a functioning ready queue
  while (finished_tasks < 100) {
    for (int i = 0; i < 100 && tasks_in_ready_queue > 0 ; i++) {
      //loop through ready queue and add task to run queue if arrivalDelay == time_delay
      if (ready[i].arrivalDelay == time) {
        run1[size_of_run1] = ready[i];
        size_of_run1++;
      }
    }
    if (queue_in_use == 1 && task_running == 0) {
      for (int i = 0; i < size_of_run1; i++) {
        if (run1[i].prio > greatest_prio) {
          greatest_prio = run1[i].prio;
          i_of_to_run = i;
          // printf("%d\n", task_running);
        }
      }
      if (i_of_to_run >= 0) {
        printf("%d\n", time);
        task_running = 1;
        // printf("%d\n", task_running);
        printf("task running: %d\n", run1[i_of_to_run].pid);
      }
    }
    if (queue_in_use == 2 && task_running == 0) {
      for (int i = 0; i < size_of_run2; i++) {
        if (run2[i].prio > greatest_prio) {
          greatest_prio = run2[i].prio;
          i_of_to_run = i;
          // task_running = 1;
        }
      }
      if (i_of_to_run >= 0) {
        printf("%d\n", time);
        task_running = 1;
        printf("task running: %d\n", run2[i_of_to_run].pid);
      }
    }
    if (task_running == 1 && time_slice != 0) {
      // printf("%d\n", size_of_run1);
      if (queue_in_use == 1) {
        // printf("%d\n", run1[i_of_to_run].burst);
        run1[i_of_to_run].burst = run1[i_of_to_run].burst - 1;
        time_slice--;
        // printf("burst left %d\n", run1[i_of_to_run].burst);
        if (run1[i_of_to_run].burst < 0) {
          task_running = 0;
          time_slice = 10;
          // printf("%d\n", queue_in_use);
          printf("%d\n", time);
          printf("task %d finished running\n", run1[i_of_to_run].pid);
          struct task tmp = run1[i_of_to_run];
          run1[i_of_to_run] = run1[0];
          run1[0] = tmp;
          memset(run1, '\0', sizeof(run1[i_of_to_run]));
          for (int i = 0; i < size_of_run1 - 1; i++) {
            struct task t = run1[i];
            run1[i] = run1[i+1];
            run1[i+1] = t;
          }
          size_of_run1--;
          // for (int i = 0; i < 15; i++) {
          //   printf("tasks %d\n", run1[i].pid);
          // }
          finished_tasks++;
          greatest_prio = -1;
        }
        if (size_of_run1 == 0) {
          // printf("%s\n", "hi");
          queue_in_use = 2;
        }
      } else {
        // printf("%s\n", "switch");
        // printf("run 2 burst %d", run2[i_of_to_run].burst);
        run2[i_of_to_run].burst = run2[i_of_to_run].burst - 1;
        time_slice--;
        if (run2[i_of_to_run].burst < 0) {
          task_running = 0;
          time_slice = 10;
          printf("%d\n", time);
          printf("task %d finished running\n", run2[i_of_to_run].pid);
          struct task tmp = run2[i_of_to_run];
          run2[i_of_to_run] = run2[0];
          run2[0] = tmp;
          memset(run2, '\0', sizeof(run2[i_of_to_run]));
          for (int i = 0; i < size_of_run2 - 1; i++) {
            struct task t = run2[i];
            run2[i] = run2[i+1];
            run2[i+1] = t;
          }
          size_of_run2--;
          finished_tasks++;
          greatest_prio = -1;
        }
        if (size_of_run2 == 0) {
          // printf("%s\n", "hi");
          queue_in_use = 1;
        }
      }
    } else if (size_of_run1 != 0 || size_of_run2 != 0){
      // time slice is zero
      // printf("%s\n", "shi");
      if (time_slice == 0 && queue_in_use == 1) {
        task_running = 0;
        time_slice = 10;
        run2[size_of_run2] = run1[i_of_to_run];
        // printf("%d\n", run2[size_of_run2].pid);
        size_of_run2++;
        printf("%d\n", time);
        printf("task %d time slice expired\n", run1[i_of_to_run].pid);
        struct task tmp = run1[i_of_to_run];
        run1[i_of_to_run] = run1[0];
        run1[0] = tmp;
        memset(run1, '\0', sizeof(run1[i_of_to_run]));
        for (int i = 0; i < size_of_run1 - 1; i++) {
          struct task t = run1[i];
          run1[i] = run1[i+1];
          run1[i+1] = t;
        }
        // for (int i = 0; i < 15; i++) {
        //   printf("tasks %d\n", run1[i].pid);
        // }
        size_of_run1--;
        if (size_of_run1 == 0) {
          // printf("%s\n", "hi");
          queue_in_use = 2;
        }
        greatest_prio = -1;
      } else if (time_slice == 0 && queue_in_use == 2){
        printf("%s\n", "switch");
        task_running = 0;
        time_slice = 10;
        run1[size_of_run1] = run2[i_of_to_run];
        size_of_run1++;
        printf("%d\n", time);
        printf("task %d time slice expired\n", run2[i_of_to_run].pid);
        struct task tmp = run2[i_of_to_run];
        run2[i_of_to_run] = run2[0];
        run2[0] = tmp;
        memset(run2, '\0', sizeof(run2[i_of_to_run]));
        for (int i = 0; i < size_of_run2 - 1; i++) {
          struct task t = run2[i];
          run2[i] = run2[i+1];
          run2[i+1] = t;
        }
        size_of_run2--;
        if (size_of_run2 == 0) {
          // printf("%s\n", "hi");
          queue_in_use = 1;
        }
        greatest_prio = -1;
      }
    }
    time++;
    // if (time < 30){
    //   printf("%d\n", time);
    //   // printf("%d\n", queue_in_use);
    // }
    // printf("finished %d\n", finished_tasks);
  }
}
