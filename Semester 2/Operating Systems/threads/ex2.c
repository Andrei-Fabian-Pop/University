// Write a c program that recives as command line arguments as many files containig random text. For each such file the program will create a thread. Each thread will recive as argument a file. All threads will have access to 2 global variables. Each thread will count the letter and the digits from the file it recived as argument and will add each of these 2 values to the global variables mentioned earlier. The threads must be dynamically allocated in memory. The access to the global variables must be efficiently synchronized using mutex variables (putting a mutex_lock at the begnnig of the thread and mutex_unlock at the end of the thread IS NOT EFFICIENT SYNCHRONIZATION) NOTE: When you compile use the -pthread obtion. The source file must be compiled using gcc with -Wall -g options WITHOUT WARNINGS OR SYNTAX ERRORS!!! Memory leaks and zombie processes are not allowed.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int l=0, d=0;

typedef struct {
	int id;
	char* filename;
	pthread_mutex_t *mutexes;
} data;

void* f(void* arg) {
	data dt = *((data*)(arg));

	FILE* file = fopen(dt.filename, "r");

	int letter=0, decimal=0, c;

	if (file == NULL) {
		printf("Could not open file %s\n", dt.filename);
		return NULL;
	}

	while ((c = fgetc(file)) != EOF) {
		if ( (c >= (int)('a') && c <= (int)('z')) || (c >= (int)('A') && c <= (int)('Z')) ) {
			++letter;
		} else if (c >= (int)('0') && c <= (int)('9')) {
			++decimal;
		}
	}

	fclose(file);

	if (letter > 0) {
		pthread_mutex_lock(&dt.mutexes[0]);
		l += letter;
		pthread_mutex_unlock(&dt.mutexes[0]);
	}

	if (decimal > 0) {
		pthread_mutex_lock(&dt.mutexes[1]);
		d += decimal;
		pthread_mutex_unlock(&dt.mutexes[1]);
	}

	return NULL;
}

int main(int argc, char** argv) {
	pthread_t *threads = malloc((argc-1) * sizeof(pthread_t));
	pthread_mutex_t *mutexes = malloc(2 * sizeof(pthread_mutex_t));
	data *dt = malloc((argc-1) * sizeof(data));

	pthread_mutex_init(&mutexes[0], NULL);
	pthread_mutex_init(&mutexes[1], NULL);

	for (int i = 0; i < argc-1; ++i) {
		dt[i].id = i;
		dt[i].filename = argv[i+1];
		dt[i].mutexes = mutexes;

		pthread_create(&threads[i], NULL, f, (void*)(&dt[i]));
	}

	for (int i = 0; i < argc-1; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf("letters: %d\ndecimals: %d\n", l, d);
	
	return 0;
}
