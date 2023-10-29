#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>

#define SHMKEY 750
int shmid;

int main(int argc, char *argv[]) {
	shmid = shmget(SHMKEY, 2, 0666|IPC_CREAT);
	int *x = (int*) shmat(shmid, 0, 0);

	int i = 0;
	int count = 0;
	*x = 10;
	while (1) {
		if (*(x+1) == 2){
		if (count == 10){
			break;
		}
		i = i + 1;
		*x = *x - 1;
		*x = *x + 1;
		if (*x != 10) {
			count = count + 1;
			printf("P2 %u: x is %d i=%d\n",getpid(),*x,i);
		}
		*(x+1) = 1;
		}
	}
}
