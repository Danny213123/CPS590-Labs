#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>

#define SHMKEY 750
int shmid;

void cleanup(int);

int main(int argc, char *argv[]) {
	shmid = shmget(SHMKEY, 2, 0666|IPC_CREAT);
	int *x = (int*) shmat(shmid, 0, 0);
	*x = 10;
	
	for (int y = 0; y <= 20; y++){
		signal(y,cleanup);
	}

	signal(SIGTERM, cleanup);

	int i = 0;
	int count = 0;
	while (1) {
		if (count == 10){
			break;
		}
		i = i + 1;
		*x = *x - 1;
		*x = *x + 1;
		if (*x != 10) {
			count = count + 1;
			printf("P1 %u: x is %d i=%d\n",getpid(),*x,i);
		}
	}
}

void cleanup(int x) {
	shmctl(shmid, IPC_RMID, 0);
	exit(0);
}
