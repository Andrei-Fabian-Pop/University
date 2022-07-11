#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {
	//FILE * file;
	//file = fopen("exam1.txt", "r");

	int atob[2];
	pipe(atob);

	if (fork() == 0) {
		// B
		close(atob[1]);
		int sz1, sz2;
		char r=0, s1[200], s2[200];
		memset(s1, 0, 200);
		memset(s2, 0, 200);

		while (1) {
			read(atob[0], &r, sizeof(char));
			if (r == '-') {
				exit(0);
			}
			read(atob[0], &sz1, sizeof(int));
			read(atob[0], s1, sizeof(char) * sz1);
			read(atob[0], &sz2, sizeof(int));
			read(atob[0], s2, sizeof(char) * sz2);
			
			if (r == '|') {
				int i;
				for (i = 0; i < sz1; ++i) {
					printf("%c%c", s1[i], s2[i]);
				} 
				printf("\n");
			} else if (r == '&') {
				printf("%s%s\n", s1, s2);
			} else {
				printf("Invalid char: %c\n", r);
				exit(1);
			} 

			memset(s1,0,200);
			memset(s2,0,200);
			r=0;
			sz1=0;
			sz2=0;
		}
	} else {
		// A
		close(atob[0]); // write = btoa[1]
						// close(btoa[0]); // read = atob[0]
		FILE * file = fopen("exam1.txt", "r");

		char c, str1[200], str2[200];
		memset(str1, 0, 200);
		memset(str2, 0, 200);
		while (fscanf(file, "%c %s %s\n", &c, str1, str2) != EOF) {
			write(atob[1], &c, sizeof(char));
			int size1 = sizeof(str1);
			write(atob[1], &size1, sizeof(int));
			write(atob[1], str1, sizeof(char) * size1);
			int size2 = sizeof(str2);
			write(atob[1], &size2, sizeof(int));
			write(atob[1], str2, sizeof(char) * size2);

			memset(str1, 0, 200);
			memset(str2, 0, 200);
			c=0;
		}
		c = '-';
		write(atob[1], &c, sizeof(char));
		// printf("%s %s %c", str2, str1, c);

		fclose(file);
		wait(0);
	}

	// fclose(file);
	return 0;
}
