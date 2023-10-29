#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*Every X seconds, prints one of:
  no PCs to report
  a list of machines that have gone down since last check
  e.g.,
  X should be 300 if you wanted the report every 5 minutes (60sec x 5 min)
*/


#define X 1

int get_machine_list(void);
void busy(void);

int main (int argc, char *argv[]) {

  int i,machine_num;
  fflush(stdout);

  for (;;) {
    fflush(stdout);
    printf("Down machines on ");
    fflush(stdout);
    system("date");
    fflush(stdout);

    machine_num=get_machine_list();
    if (machine_num==0) {
       fflush(stdout);
       printf("   --no PCs to report\n");
       busy();
       fflush(stdout);
    }
    else {
       for (i=25;i<=machine_num;i++) {
         fflush(stdout);
         busy();
         printf("   --machine %d\n",i);
         fflush(stdout);
       }
    }       
  fflush(stdout);
  //sleep(X);
  } 


return 0;
}

int get_machine_list(void) {
  /*This function should do some system-level processing to figure out
    the list of down machines, if any. However, we SIMULATE it here,
    by returning some random number of down machines from 25 to 29
  */

  int r;
  unsigned int iseed = (unsigned int)time(NULL);
  srand (iseed);
  r = rand();
  if ( (r%2) == 0 ) return 0;
  else return 25+r%5;
}

void busy(void) {
  int i, y=0;
  for (i=0;i<INT_MAX/10;i++) y+=0;
}
