#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	fork();
	printf("f1\n");
	wait(0);
	printf("w1\n");
	fork();
	printf("f2\n");
	wait(0);
	printf("w2\n");
	fork();
	printf("f3\n");
	
	sleep(20);

	return 0;
}
