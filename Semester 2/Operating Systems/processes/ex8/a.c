#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	if (mkfifo("./fifo1", 0600) < 0)
		exit(1);
	if (mkfifo("./fifo2", 0600) < 0) 
		exit(1);
	
	int wr = open("./fifo1", O_WRONLY);
	int rd = open("./fifo2", O_RDONLY);

	srandom(getpid());

	int nr = 0;
	write(wr, &nr, sizeof(int));
	while (nr != 10) {
		read(rd, &nr, sizeof(int));
		printf("A <- %d\n", nr);
		if (nr == 10) {
			printf("A lost\n");
			break;
		}
		nr = random() % 10 + 1;
		printf("A -> %d\n", nr);
		write(wr, &nr, sizeof(int));
	}
	close(wr);
	close(rd);

	unlink("./fifo1");
	unlink("./fifo2");

	return 0;
}
