#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	int rd = open("./fifo1", O_RDONLY);
	int wr = open("./fifo2", O_WRONLY);

	srandom(getpid());
	int nr = 0;

	while (nr != 10) {
		read(rd, &nr, sizeof(int));
		printf("B <- %d\n", nr);
		if (nr == 10) {
			printf("B lost\n");
			break;
		}
		nr = random() % 10 + 1;
		printf("B -> %d\n", nr);
		write(wr, &nr, sizeof(int));
	}

	close(rd);
	close(wr);

	return 0;
}
