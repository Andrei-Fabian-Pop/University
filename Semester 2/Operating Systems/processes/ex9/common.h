#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char *a2b = "./a2b";
char *b2a = "./b2a";

// reuse the same functions in both process A and process B
void write_to_fd(int fd, char *buf) {
    int len = strlen(buf);
    if (0 > write(fd, &len, sizeof(int))) {
        perror("Error on write length");
    }
    if (0 > write(fd, buf, len * sizeof(char))) {
        perror("Error on write buffer");
    }
}

void read_from_fd(int fd, int max, char *buf) {
    int read_bytes = 0;
    while(read_bytes < max) {
        int k;
        if((k = read(fd, buf + read_bytes, (max - read_bytes) * sizeof(char))) > 0) {
            read_bytes += k;
        }
    }
}

#endif
