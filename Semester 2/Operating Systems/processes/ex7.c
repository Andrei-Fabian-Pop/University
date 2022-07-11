/*
 * Write a C program that creates two child processes. The two child processes will 
 * alternate sending random integers between 1 and 10(inclusively) to one another 
 * until one of them sends the number 10. Print messages as the numbers are sent.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
	int atob[2], btoa[2];
	
	if (pipe(atob) < 0)
		exit(1);
	if (pipe(btoa) < 0)
		exit(1);

	// srandom(getpid());

	if (fork() == 0) {
		// child A
		// printf("A started\n");
		int numa = 0;
		srandom(getpid());
		close(btoa[0]);
		close(atob[1]);
		while(numa != 10) {
			read(atob[0], &numa, sizeof(int));
			printf("A <- %d\n", numa);
			if (numa == 10) {
				printf("A lost\n");
				exit(0);
			}
			numa = random() % 10 + 1;
			printf("A -> %d\n", numa);
			write(btoa[1], &numa, sizeof(int));
		}
	} else if (fork() == 0) {
		// printf("B started\n");
		// child B
		close(atob[0]);
		close(btoa[1]);
		srandom(getpid());
		int numb = 0;
		while (numb != 10) {
			read(btoa[0], &numb, sizeof(int));
			printf("B <- %d\n", numb);
			if (numb == 10) {
				printf("B lost\n");
				exit(0);
			}
			numb = random() % 10 + 1;
			printf("B -> %d\n", numb);
			write(atob[1], &numb, sizeof(int));
		}
	} else {
		// parent
		close(atob[0]);
		close(btoa[0]);
		close(btoa[1]);
		int startint = 0;
		write(atob[1], &startint, sizeof(int));
		close(atob[1]);
		wait(0);
	}

	return 0;
}
