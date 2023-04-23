#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  even_condition_var   = PTHREAD_COND_INITIALIZER;
pthread_cond_t odd_condition_var = PTHREAD_COND_INITIALIZER;

void *functionCount1();
void *functionCount2();
int  count = 0;
int total = 0;
#define COUNT_DONE  10
#define COUNT_HALT1  3
#define COUNT_HALT2  6

int main()
{
   printf("Starting total: %d\n", total);   
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &functionCount1, NULL);
   pthread_create( &thread2, NULL, &functionCount2, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   printf("Final total: %d\n",total);

   exit(0);
}

// Write numbers 1-3 and 8-10 as permitted by functionCount2()

// Even
void *functionCount1()
{
   for(;;)
   {
        pthread_mutex_lock(&count_mutex);

        if (count % 2 == 0){
                total += 2;
                count ++;
                printf("Total value functionEven: %d\n", total);
                pthread_cond_signal(&odd_condition_var);
        } else {
                pthread_cond_wait(&even_condition_var, &count_mutex);
        }

        if (count >= COUNT_DONE || total >= COUNT_DONE * 2) {
                pthread_mutex_unlock(&count_mutex);
                return (NULL);
        }
        pthread_mutex_unlock(&count_mutex);
   }
}

// Odd
void *functionCount2()
{
   for(;;)
   {
        pthread_mutex_lock(&count_mutex);

        if (count % 2 == 1){
                total += 1;
                count ++;
                printf("Total value functionOdd: %d\n", total);
                pthread_cond_signal(&even_condition_var);
        } else {
                pthread_cond_wait(&odd_condition_var, &count_mutex);
        }

        if (count >= COUNT_DONE || total >= COUNT_DONE * 2) {
                pthread_mutex_unlock(&count_mutex);
                return (NULL);
        }
        pthread_mutex_unlock(&count_mutex);
   }
}
