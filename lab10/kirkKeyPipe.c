// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include "halfduplex.h"

int main(void)
{
    int fd;
    char buf[MAX_BUF_SIZE];

    int ret_val = mkfifo(HALF_DUPLEX, 0666);

    fd = open(HALF_DUPLEX, O_WRONLY);

    while(fgets(buf, MAX_BUF_SIZE, stdin) != NULL) {
        int len = strlen(buf);
	
	if (buf[len-1] == '\n')
		buf[len-1] = '\0';

	if (write(fd, buf, len + 1) == -1){
		perror("write");
		exit(EXIT_FAILURE);
	}
    }

    close(fd);
    unlink(HALF_DUPLEX);

    return 0;
}

