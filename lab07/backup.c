#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

void *functionEven();
void *functionOdd();
int  count = 0;
int total = 0;
#define COUNT_DONE  10

int main()
{
	printf("Starting total: %d\n", total);
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &functionEven, NULL);
   pthread_create( &thread2, NULL, &functionOdd, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   printf("Final total: %d\n",total);

   exit(0);
}

// Write numbers 1-3 and 8-10 as permitted by functionCount2()

void *functionEven()
{
   for(;;)
   {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &count_mutex );
	
	while (count % 2 != 0){
      		pthread_cond_wait( &condition_var, &count_mutex );
	}
	count++;
	total+=2;
	printf("Total value functionEven: %d\n", total);

	pthread_cond_signal( &condition_var );
	pthread_mutex_unlock( &count_mutex );
      if(count >= COUNT_DONE) return(NULL);
    }
}

void *functionOdd()
{
   for(;;)
   {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &count_mutex );
	
	while (count % 2 == 0){
      		pthread_cond_wait( &condition_var, &count_mutex );
	}
	count++;
	total+=1;
	printf("Total value functionOdd: %d\n", total);

	pthread_cond_signal( &condition_var );
	pthread_mutex_unlock( &count_mutex );
      if(count >= COUNT_DONE) return(NULL);
    }
}

