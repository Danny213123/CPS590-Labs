#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "NO PID");
		exit(1);
	} else {
		kill (atol(argv[1]), SIGKILL);	
	}
}
