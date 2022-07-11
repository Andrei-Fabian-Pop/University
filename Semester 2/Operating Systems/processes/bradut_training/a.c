#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv) {
	char filename[200];
	printf("File:\n");
	scanf("%s", filename);
	FILE * file = fopen(filename, "r");

	if (mkfifo("./fifo", 0600) < 0) {
		printf("Fifo already exists\n");
		exit(1);
	}
	int wr = open("./fifo", O_WRONLY);
	int nr = 0;

	while(fscanf(file, "%d", &nr) != EOF) {
		printf("%d\n", nr);
		write(wr, &nr, sizeof(int));
	}

	fclose(file);
	close(wr);

	return 0;
}
