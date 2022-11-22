https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include "queue.h"
#include <pthread.h>

static int num_pthreads = 10000;

void* enqueueThread(void* arg){ 
	queue *q = (queue*) arg;
	int i = 1;
	if(!queueEnqueue(q, &i)) printf("[!!!]enqueueThread failed!\n");
	pthread_exit(NULL);
}

void* dequeueRearThread(void* arg){ 
	queue *q = (queue*) arg;
	int i;
	if(!queueDequeueRear(q, &i)) printf("[!!!]dequeueRearThread failed!\n");
	pthread_exit(NULL);
}

void* dequeueFrontThread(void* arg){ 
	queue *q = (queue*) arg;
	int i;
	if(!queueDequeueFront(q, &i)) printf("[!!!]dequeueFrontThread failed!\n");
	pthread_exit(NULL);
}

int main(int argc, char** argv){
	int i, rc, tmp;
	queue *q = queueCreate(num_pthreads);
	pthread_t *threads = malloc(num_pthreads * sizeof(pthread_t)); 
	int j;
	num_pthreads = num_pthreads;
	for(j = 0; j < 10; j++){ // run the test 10 times
		printf("\n-------Run %d-------\n", j);
		printf("====Enqueuing...");
		for(i = 0; i < num_pthreads; i++) {
			if ((rc = pthread_create(&threads[i], NULL, enqueueThread, (void*) q))) {
				fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
				return EXIT_FAILURE;
			} 
		} 
		for (i = 0; i < num_pthreads; i++) pthread_join(threads[i], NULL); 
		int sum = 0;
#pragma omp parallel for reduction(+: sum) 
		for(i = 0; i < num_pthreads; i++) sum += q->array[i];
		if(queueIsFull(q) && q->size == num_pthreads && sum) printf(" Pass.\n");
		else {
			printf(" Fail! \nQueue is Full: %d, size = %d\n", queueIsFull(q), q->size);
			printf("Queue sum = %d, num_pthreads = %d\n", sum, num_pthreads); 
		}


		int queueSize = q->size;
		printf("====Dequeuing Rear...");
		for (i = 0; i < queueSize; i++){
			if ((rc = pthread_create(&threads[i], NULL, dequeueRearThread, (void*) q))) {
				fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
				return EXIT_FAILURE;
			} 
		} 
		for (i = 0; i < queueSize; i++) pthread_join(threads[i], NULL); 
		if(queueIsEmpty(q)) printf(" Pass.\n");
		else printf(" Fail!\nQueue is Empty: %d, size = %d\n", queueIsEmpty(q), q->size);
		while(queueDequeueRear(q, &tmp)){}

		printf("====Dequeuing Front...");
		for (i = 0; i < num_pthreads; i++) queueEnqueue(q, &num_pthreads);
		for (i = 0; i < num_pthreads; i++){
			if ((rc = pthread_create(&threads[i], NULL, dequeueFrontThread, (void*) q))) {
				fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
				return EXIT_FAILURE;
			} 
		} 
		for (i = 0; i < num_pthreads; i++) pthread_join(threads[i], NULL); 
		if(queueIsEmpty(q)) printf(" Pass.\n");
		else printf(" Fail!\nQueue is Empty: %d, size = %d\n", queueIsEmpty(q), q->size); 
		while(queueDequeueRear(q, &tmp)){}
	}
	
	queueDestroy(q);
	return 0;
}
