/* 8. Write 2 C programs, A and B. A receives however many command line arguments and sends them to process B. 
 * Process B converts all lowercase letters from the received arguments to uppercase arguments and sends the results back to A. 
 * A reads the results, concatenates them and prints. 
 *
 * Scrieti 2 programe C, A si B. A primeste un numar oarecare de argumente la linia de commanda si le trimite procesului B. 
 * B converteste toate literele mici in litere mari din argumentele primite si trimite rezultatul inapoi procesului A. 
 * A citeste rezultatele procesului B, le concateneaza si le afiseaza.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc < 2)  {
		printf("Not enough arguments.\n");
		exit(1);
	}

	if (mkfifo("./fifo1", 0600) < 0)
		exit(1);
	if (mkfifo("./fifo2", 0600) < 0)
		exit(1);
	
	int wr = open("./fifo1", O_WRONLY);
	int rd = open("./fifo2", O_RDONLY);


	int argvLen = 0, i;
	for (i = 1; i < argc; ++i) {
		argvLen += strlen(argv[i]);
	}
	++argvLen;

	char *full = malloc(sizeof(char) * argvLen);

	write(wr, &argvLen, sizeof(int));
	write(wr, &argc, sizeof(int));
	for (i = 1; i < argc; ++i) {
		printf("Processing %s\n", argv[i]);
		int size = strlen(argv[i]);
		printf("Sending %d chars\n", size);
		write(wr, &size, sizeof(int));
		write(wr, argv[i], sizeof(char) * size);
		
		char *rec = malloc(sizeof(char) * (size + 1));
		read(rd, rec, sizeof(char) * size);
		rec[size] = 0;
		printf("%s\n", rec);

		strcat(full, rec);
		strcat(full, " ");
		free(rec);
	}

	printf("Full: %s\n", full);

	free(full);
	close(wr);
	close(rd);
	if (unlink("./fifo1") < 0)
		exit(1);
	if (unlink("./fifo2") < 0)
		exit(1);

	return 0;
}
