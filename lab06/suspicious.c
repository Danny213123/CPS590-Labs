#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*Every X seconds, prints one of:
  nothing suspicious to report
  a list of suspicious users
  e.g.,
  X should be 300 if you wanted the report every 5 minutes (60sec x 5 min)
*/


#define X 1

int get_user_list(void);
void busy(void);

int main (int argc, char *argv[]) {

  int i,user_num;
  fflush(stdout);

  for (;;) {
    fflush(stdout);
    printf("Suspicious users on ");
    fflush(stdout);
    system("date");
    fflush(stdout);

    user_num=get_user_list();
    if (user_num==0) {
       fflush(stdout);
       printf("   --nothing suspicious to report\n");
       busy();
       fflush(stdout);
    }
    else {
       for (i=1;i<=user_num;i++) {
         fflush(stdout);
         printf("   --user %d\n",i);
         busy();
         fflush(stdout);
       }
    }       
  fflush(stdout);
  //sleep(X);
  } 


return 0;
}

int get_user_list(void) {
  /*This function should do some system-level processing to figure out
    the list of suspicious users, if any. However, we SIMULATE it here,
    by returning some random number of suspicious users from 0 to 4
  */

  int r;
  unsigned int iseed = (unsigned int)time(NULL);
  srand (iseed);
  r = rand();
  if ( (r%2) == 0 ) return 0;
  else return r%5;
}

void busy(void) {
  int i, y=0;
  for (i=0;i<INT_MAX/10;i++) y+=0;
}
