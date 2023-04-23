// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>
#include "halfduplex.h"

int main(void)
{
    int fd;
    char buf[MAX_BUF_SIZE];

    int num_read;

    fd = open(HALF_DUPLEX, O_RDONLY);

    printf("spock: ready to receive messages, captain.\n");

    for(;;) { /* Spock never quits! */
        num_read = read(fd, buf, MAX_BUF_SIZE);
        if (num_read == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("spock: \"%s\"\n", buf);
    }

    close(fd);
    return 0;
}
