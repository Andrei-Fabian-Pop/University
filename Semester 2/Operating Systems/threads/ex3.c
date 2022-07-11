// Write a c program that recives as command line arguments as many pairs formed by a file (f) containing only numbers (as may as you like) 
// and a number (n). For each such pair the program will create a thread. Each thread will receive a pair and will add the first n even numbers 
// from f to a global variable. The threads must be dynamically allocated in memory. The access to the global variable must be 
// efficiently synchronized using mutex variables (putting a mutex_lock at the begnnig of the thread and mutex_unlock at the end of the 
// thread IS NOT EFFICIENT SYNCHRONIZATION) NOTE: When you compile use the -pthread obtion. The source file must be compiled using gcc 
// with -Wall -g options WITHOUT WARNINGS OR SYNTAX ERRORS!!!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int sum = 0;

typedef struct {
	int id, n;
	char* filename;
	pthread_mutex_t *mutex;
} data;

void* f(void* arg) {
	data d = *((data*)arg);
	int s = 0, num = d.n, aux;
	FILE* file = fopen(d.filename, "r");

	if (file == NULL) {
		printf("Cannot open file %s\n", d.filename);
		return NULL;
	}

	while ((fscanf(file, "%d", &aux)) != EOF && num > 0) {
		// fscanf(file, "%d", &aux);
		if (aux%2 == 0) {
			s += aux;
			--num;
		}
	}

	fclose(file);

	if (s != 0) {
		pthread_mutex_lock(d.mutex);
		sum += s;
		pthread_mutex_unlock(d.mutex);
	}

	return NULL;
}

int main(int argc, char** argv) {
	pthread_t *threads = malloc(((argc-1) / 2) * sizeof(pthread_t));
	pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
	data *d = malloc(((argc-1) / 2) * sizeof(data));

	pthread_mutex_init(mutex, NULL);
	
	for (int i = 0; i < (argc-1)/2; ++i) {
		d[i].id = i;
		d[i].n = atoi(argv[1+i*2]);
		d[i].filename = argv[1+i*2+1];
		d[i].mutex = mutex;
		pthread_create(&threads[i], NULL, f, (void*)(&d[i]));
	}

	for (int i = 0; i < (argc-1)/2; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf("Final sum is: %d\n", sum);

	pthread_mutex_destroy(mutex);
	free(threads);
	free(mutex);
	free(d);

	return 0;
}
