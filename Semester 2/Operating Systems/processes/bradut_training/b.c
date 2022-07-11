#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	int p[2];
	pipe(p);
	int rd = open("./fifo", O_RDONLY);

	if (fork() == 0) {
		close(p[0]);
		int nr, sum=0;
		while (read(rd, &nr, sizeof(int)) > 0) {
			printf("%d\n", nr);
			sum += nr;
		}

		write(p[1], &sum, sizeof(int));

		exit(0);
	}
	if (fork() == 0) {
		close(p[1]);

		int sum1=0;
		read(p[0], &sum1, sizeof(int));
		printf("Sum = %d\n", sum1);

		exit(0);
	}

	wait(0);
	wait(0);

	close(p[0]);
	close(p[1]);

	close(rd);

	unlink("./fifo");

	return 0;
}
