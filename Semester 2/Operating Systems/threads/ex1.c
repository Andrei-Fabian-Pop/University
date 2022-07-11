// Scrieti un program C care primeste ca si argumente in linia de comanda oricate fisiere. Fiecare fisier va cantine doua numere intregi a inter 1 si 100 si b intre 1000 si 100000. Prgramul va avea n variabile globale, n find numarul de fisiere date ca argument in linia de comanda. Programu va crea cate doua thread-uri x si y pentru fiecare fisier primit ca argument, Fiecare pereche de thread-uri x si y va primi ca argument un fisier dat ca argument, thread-ul x va citi numarul a si b din fisier si va adauga valoarea lui a la variabila globala asociata acestuia pana cand variabila globala va depasi valoarea lui b, moment in care x va trimite un semnal lui y si y va afisa pe ecran valoarea variabilei globale.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int n = 0, *sum;

typedef struct {
	int id;
	char* filename;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
} data;

void* f1(void* var) {
	data d = *((data*)(var));
	FILE* file = fopen(d.filename, "r");
	int a, b;
	fscanf(file, "%d %d", &a, &b);
	fclose(file);

	pthread_mutex_lock(d.mutex);
	
	while (sum[d.id] <= b) {
		sum[d.id] += a;
	}

	if (sum[d.id] > b) {
		pthread_cond_signal(d.cond);
	}

	pthread_mutex_unlock(d.mutex);

	return NULL;
}

void* f2(void* var) {	
	data d = *((data*)(var));
	pthread_mutex_lock(d.mutex);
	pthread_cond_wait(d.cond, d.mutex);

	printf("thread with id %d printed %d\n", d.id, sum[d.id]);

	pthread_mutex_unlock(d.mutex);
	
	return NULL;
}
int main(int argc, char** argv) {
	--argc;
	sum = (int*)malloc(argc * sizeof(int));
	pthread_mutex_t *mutexes = (pthread_mutex_t*)malloc(argc * sizeof(pthread_mutex_t));
	pthread_cond_t *conds = (pthread_cond_t*)malloc(argc * sizeof(pthread_cond_t));
	data* d = (data*)malloc(argc * sizeof(data));

	for (int i = 0; i < argc; ++i) {
		pthread_mutex_init(&mutexes[i], NULL);
		pthread_cond_init(&conds[i], NULL);
	}

	for (int i = 0; i < argc; ++i) {
		sum[i] = 0;
		d[i].id = i;
		d[i].filename = argv[i+1];
		d[i].mutex = &mutexes[i];
		d[i].cond = &conds[i];
	}

	pthread_t *threads = malloc(2 * argc * sizeof(pthread_t));
	for (int i = 0; i < argc; ++i) {
		pthread_create(&threads[i+argc], NULL, f2, (void*)(&d[i]));
		sleep(2);
		pthread_create(&threads[i], NULL, f1, (void*)(&d[i]));		
	}

	for (int i = 0; i < argc; ++i) {
		pthread_join(threads[i], NULL);
		pthread_join(threads[i+argc], NULL);
		pthread_mutex_destroy(&mutexes[i]);
		pthread_cond_destroy(&conds[i]);
	}

	free(mutexes);
	free(conds);
	free(d);
	free(threads);
	free(sum);

	return 0;
}
