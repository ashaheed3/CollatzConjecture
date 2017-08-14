#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define NUMOFTHREADS 8

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
double areaSum = 0.00;

//Thread instructions
void *reimannSum(void *threadid){
	
	double x,area;
	long tid;
	
	tid = (long)threadid;
	x = 1.0/NUMOFTHREADS;

	area = (x * (sqrt(1.0-pow((x*tid),2))));
	
	
	pthread_mutex_lock(&mutex1);	
	areaSum += area;
	pthread_mutex_unlock(&mutex1);

	printf("#%ld: %f\n", tid, area);
	pthread_exit(NULL);
}


int main(int argc, char *argv[]){

	pthread_t threads[NUMOFTHREADS];

	for(int i = 0;i < NUMOFTHREADS;i++){
		pthread_create(&threads[i], NULL, reimannSum, (void *)i);
	}

	for(int i= 0; i < NUMOFTHREADS; i++){
		pthread_join(threads[i], NULL);
	}

	printf("Work Complete \n");
	printf("Sum: %f\n",(4*areaSum));
	system("PAUSE");
	return EXIT_SUCCESS;
}
