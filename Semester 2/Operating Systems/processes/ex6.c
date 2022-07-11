#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <time.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>

/* Create a C program that generates N random integers (N given at the command line). 
 * It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.
 */

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Enter an integer as parameter\n");
		exit(1);
	}
	int p_to_c[2], c_to_p[2];  //[0] - read, [1] - write
	pipe(p_to_c);
	pipe(c_to_p);
	int f = fork();
	if (f == -1) {
		printf("Error making fork\n");
	} else if (f == 0) {
		// child
		close(p_to_c[1]);
		close(c_to_p[0]);
		int n=0, i, nr;
		float rez = 0;
		if (read(p_to_c[0], &n, sizeof(int)) < 0) {
			perror("Error reading pipe from parent.\n");
			close(p_to_c[0]);
			close(c_to_p[1]);
			exit(1);
		}
		for (i=0; i < n; ++i) {
			if (read(p_to_c[0], &nr, sizeof(int)) < 0) {
				perror("Error reading num from parent pipe.\n");
				close(p_to_c[0]);
				close(c_to_p[1]);
				exit(1);
			}
			rez += nr;
		}
		rez /= n;
		if (write(c_to_p[1], &rez, sizeof(float)) < 0) {
			perror("Error writing to parent pipe.\n");
			close(p_to_c[0]);
			close(c_to_p[1]);
			exit(1);
		}
		close(p_to_c[0]);
		close(c_to_p[1]);
		exit(1);
	} else {
		// parent
		close(p_to_c[0]);
		close(c_to_p[1]);

		int n = atoi(argv[1]);
		int i, nr;
		float rez = -1;

		srandom(time(0));

		if (write(p_to_c[1], &n, sizeof(int)) < 0) {
			perror("Error writing n to child.\n");
			close(p_to_c[1]);
			close(c_to_p[0]);
			exit(1);
		}
		for (i=0; i < n; ++i) {
			nr = random() % 100;
			printf("Parent generated %d.\n", nr);
			if (write(p_to_c[1], &nr, sizeof(int)) < 0) {
                perror("Error writing nr to child.\n");
                close(p_to_c[1]);
                close(c_to_p[0]);
                exit(1);
          	}
		}

		wait(0);
		
		if(0 > read(c_to_p[0], &rez, sizeof(float))) {
            perror("Error on read result from child ");
        }
        printf("Average is %f\n", rez);
        close(p_to_c[1]);
        close(c_to_p[0]);
	}
	
	return 0;
}
