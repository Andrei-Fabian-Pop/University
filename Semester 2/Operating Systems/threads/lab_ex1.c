#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread(void *arg) {
	int d = *(int *) (arg);
	printf("%d message\n", d);
	

	return 0;
}

int main(int argc, char** argv) {
	int n = atoi(argv[1]);

	pthread_t *t = malloc(n * sizeof(pthread_t));

	for (int i = 0; i < n; ++i) {
		pthread_create(&t[i], 0, thread, (void *)&i);
	}

	for (int i = 0; i < n; ++i) {
		pthread_join(t[i], 0);
	}

	return 0;
}
