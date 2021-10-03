#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#define MAX_LINE 80
#define MAX_OPTS 20
int main()
{
  char *myopts[MAX_OPTS];
  char tempstring[MAX_LINE];
  char *wordstring;
  char newlinestring[MAX_LINE];
  int should_run = 1;
  int ac;

  char *myopts1[MAX_OPTS];
  char tempstring1[MAX_LINE];
  char *wordstring1;
  char newlinestring1[MAX_LINE];
  int ac1;

  // printf("%ld\n",sizeof(char)); return 0;
  while (should_run) {
    printf("osh> ");
    scanf("%[^\n]",tempstring); // might overflow
    fgets(newlinestring,MAX_LINE,stdin); // clear the stdin newline

    printf("\treceived (%s)\n", tempstring);
    printf("\tnow scanning tokens\n");

    ac = 0;
    wordstring = strtok(tempstring," "); // might overflow
    while (wordstring != NULL) {
      printf("\tstoring token (%s)",wordstring);
      myopts[ac] = malloc(MAX_LINE*sizeof(char));
      strcpy(myopts[ac],wordstring);
      printf(" = (%s)\n", myopts[ac]);
      ac++;
      wordstring = strtok(NULL," ");
    }
    myopts[ac] = NULL; // last wordstring was NULL, so store it for execvp
    printf(" --> done \n");
    fflush(stdout);

    printf("osh> ");
    scanf("%[^\n]",tempstring1); // might overflow
    fgets(newlinestring1,MAX_LINE,stdin); // clear the stdin newline

    printf("\treceived (%s)\n", tempstring1);
    printf("\tnow scanning tokens\n");

    ac1 = 0;
    wordstring1 = strtok(tempstring1," "); // might overflow
    while (wordstring1 != NULL) {
      printf("\tstoring token (%s)",wordstring1);
      myopts1[ac1] = malloc(MAX_LINE*sizeof(char));
      strcpy(myopts1[ac1],wordstring1);
      printf(" = (%s)\n", myopts1[ac1]);
      ac1++;
      wordstring1 = strtok(NULL," ");
    }
    myopts1[ac1] = NULL; // last wordstring was NULL, so store it for execvp
    printf(" --> done \n");
    fflush(stdout);

    pid_t pid;
    pid = fork();

    if (pid == 0) {
      // should_run = 0;
      printf("CHILD working on %s\n", myopts[0]);
      fflush(stdout);
      execvp(myopts[0], myopts);
      // return 1;

    } else {
      should_run = 1;
      wait(NULL); // waiting for CHILD
      printf("PARENT working on %s\n", myopts1[0]);
      execvp(myopts1[0], myopts1);
    }
  }
}
