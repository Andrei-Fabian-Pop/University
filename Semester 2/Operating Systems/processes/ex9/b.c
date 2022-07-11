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
	int rd = open("./fifo1", O_RDONLY);
	int wr = open("./fifo2", O_WRONLY);

	int i, argvLen, count;

	read(rd, &argvLen, sizeof(int));
	read(rd, &count, sizeof(int));

	for (i = 1; i < count; ++i) {
		int size = 0;
		// printf("Sending %d chars\n", size);
		if (read(rd, &size, sizeof(int)) < 0) {
			printf("Error on reading\n");
		}
		char *buf = calloc(sizeof(char) * (size + 1));
		printf("Got size %d\n", size);
		read(rd, buf, sizeof(char) * size);
		printf("Read %s\n", buf);
		for (i = 0; i < size; ++i) {
			if(buf[i] >= 'a' && buf[i] <= 'z') {
                buf[i] += 'A' - 'a';
            }
		}
		buf[size] = 0;
		printf("Sending %s\n", buf);
		write(wr, buf, sizeof(char) * size);

		printf("%s\n", buf);

		free(buf);
	}


	close(wr);
	close(rd);
	
	return 0;
}
