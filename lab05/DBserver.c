/*
 3 users use the DB (for each, a thread is spawned).
 Thread i does queryNo[i] queries for its user.
 A global "total_queries" is maintained. Each thread
 updates it after each of its queries.

 This has a race condition on variable total_queries. 

 Note that if you have maxed out your allotted clones, 
   one (or more) child may never execute its function, 
   although it exists. So parent can't terminate 
   because it waits forever for child (do ps -l or 
   ps -lu USERID and kill the offending child)
*/

#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int queryNo[3] = {1011, 1012, 1013};

int total_queries = 0;

int userThread (void *p) 
{
   int i;
   int q = (int)(long)p;

   //set thread q on CPU q
   cpu_set_t set;
   CPU_ZERO( &set );
   CPU_SET( q, &set );
   if (sched_setaffinity( getpid(), sizeof( cpu_set_t ), &set ))
   {
     perror( "sched_setaffinity" );
     _exit(0);
   }

   for (i = 0; i < queryNo[q]; i++) { //handle queries
       total_queries = total_queries + 1;
   }
   _exit(0);
}

int main(int argc, char *argv[]) 
{
   const int STACK_SIZE = 65536;  
   char *stack;
   char *stackTop[3];
   pid_t cret[3], wret;
   int i;

   for (i = 0; i < 3; i++) { //do 3 child threads
      stack = malloc(STACK_SIZE);
      if (stack == NULL) {
          perror("malloc"); 
		  exit(1);
      }
      stackTop[i] = stack + STACK_SIZE;  /* Assume stack grows downward */
         
      cret[i] = clone(userThread, stackTop[i], CLONE_VM|SIGCHLD, 
                (void *)(long)i);  //make child signal when done
      
	  if (cret[i] == -1) {
		  perror("clone"); 
		  exit(0); 
	  }
      //parent keeps going here
   }
   //for (i=0;i<3;i++) waitpid(cret[i],0,0);

   for (i = 0; i < 3; i++) 
   {
      wret = waitpid(-1, 0, 0);
      if (wret == -1) {
         perror("waitpid");
         exit(3);
      } //a useless double-check that we got our own children...
      if (wret != cret[0] && wret != cret[1] && wret != cret[2] ) {
         perror("waitpid wret");
         exit(2);
      } 
   }
   sleep(1);
   printf("%d total_queries should be 3036 and it is %d\n", getpid(), total_queries);
   return 0;
}
      
