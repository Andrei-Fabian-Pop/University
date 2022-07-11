#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	struct timeval tv1, tv2;
	if (argc < 2) {
		printf("Enter more than 1 arg\n");
		exit(1);
	}
	gettimeofday(&tv1, NULL);
	int f = fork();
	if (f < 0) {
		perror("Fork error");
		exit(1);
	} else if (f == 0) {
		// child
		printf("Child executing %s", argv[1]);
		if (execvp(argv[1], argv + 1) == -1) {
			perror("Error executing command\n");
			exit(1);
		}
	} else {
		wait(0);
		gettimeofday(&tv2, NULL);
		printf("This whole madness took %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));
	}
	
	return 0;
}
