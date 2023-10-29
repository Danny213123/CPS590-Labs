#include <semaphore.h>
#include <stdio.h>

int main(){
	sem_unlink("/d1guan_sema");
	return 0;
}
