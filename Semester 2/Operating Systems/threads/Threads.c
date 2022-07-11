#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int id;
	pthread_barrier_t *barrier;
} data;

void* f(void* var) {
	data d = *((data*) (var));
	pthread_barrier_wait(d.barrier);
	printf("id: %d\n", d.id);
	
	return NULL;
}

int main(int argc, char** argv){
	int n = 10;
	pthread_barrier_t barrier;
	pthread_t *threads = malloc(n * sizeof(pthread_t));
	data* d = malloc(n * sizeof(data));
	pthread_barrier_init(&barrier, NULL, 7);
	for (int i = 0; i < n; ++i) {
		d[i].id = i+1;
		d[i].barrier = &barrier;
		pthread_create(&threads[i], NULL, f, (void*)(&d[i]));
	}
	for (int i = 0; i < n; ++i) {
		pthread_join(threads[i], NULL);
	}
	
	pthread_barrier_destroy(&barrier);
	free(threads);
	free(d);

	return 0;
}
