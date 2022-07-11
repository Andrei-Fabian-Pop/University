#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	if (fork() != fork()) {
		fork();
	}	
	sleep(20);

	return 0;
}
