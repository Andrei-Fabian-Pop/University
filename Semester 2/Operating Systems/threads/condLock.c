#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int done = 1;
typedef struct{
	int id;
	pthread_cond_t *cond;
	pthread_mutex_t *mutex;
}data;

void* f(void* arg){
	data info = *((data*) arg);
	pthread_mutex_lock(info.mutex);
	if(done == 1){
		done++;
		printf("Waiting for condition...\n");
		usleep(5000);
		pthread_cond_wait(info.cond, info.mutex);
	}
	else{
		printf("Unlocking condition...\n");
		usleep(5000);
		pthread_cond_signal(info.cond);
	}
	printf("Thread %d unlocking mutex...\n", info.id);
	pthread_mutex_unlock(info.mutex);
	return NULL;
}

int main(int argc, char** argv){
	pthread_t * th = malloc(sizeof(pthread_t) * 2);
	pthread_cond_t cond;
	pthread_mutex_t *mut = malloc(sizeof(pthread_mutex_t));
	data *info = malloc(sizeof(data) * 2);
	pthread_mutex_init(mut, NULL);
	pthread_cond_init(&cond, NULL);
	for(int i = 0; i < 2; ++i){
		info[i].id = i + 1;
		info[i].cond = &cond;
		info[i].mutex = mut;
		pthread_create(&th[i], NULL, f, (void*)&info[i]);
		sleep(1);
	}
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	return 0;
}
