#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	char* s[3] = {"A", "B", "C"};
	for (int i = 0; i < 3; ++i) {
		// sleep(random() % 2);
		if (fork() != 0) {
			execl("/bin/echo", "/bin/echo", s[i], NULL);
		}
	}
	wait(0);
	// wait(0);
	// wait(0);

	return 0;
}
