#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <string.h> 
#include <unistd.h> 
#define MAX 2
pthread_t tid[MAX]; 
int counter; 
pthread_mutex_t lock; 

void* trythis(void* arg) 
{ 
	int pr=0;
    while(pthread_mutex_trylock(&lock)==EBUSY)
    {
        if (pr==0){
		printf("soy el hilo %lX y estoy esperando que se libere el lock\n",pthread_self());
		pr=1;
		}
    };
	unsigned long i = 0; 
	counter += 1; 
	printf("Job %d (%lX) has started\n", counter,pthread_self()); 

	for (i = 0; i < (0xFFFFFFF); i++) 
		; 

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 

	return NULL; 
} 

int main(void) 
{ 
	int i = 0; 
	int error; 

	if (pthread_mutex_init(&lock, NULL) != 0) { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	while (i < MAX) { 
		error = pthread_create(&(tid[i]), 
							NULL, 
							&trythis, NULL); 
		if (error != 0) 
			printf("\nThread can't be created :[%s]", 
				strerror(error)); 
		i++; 
	} 
for (i=0;i<MAX;i++){
	pthread_join(tid[i], NULL); 
	}
	pthread_mutex_destroy(&lock); 

	return 0; 
} 
