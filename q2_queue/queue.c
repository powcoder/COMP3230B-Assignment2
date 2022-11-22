https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include "queue.h"

queue* queueCreate(unsigned capacity){
	queue* q = malloc(sizeof(queue));
	q->capacity = capacity;
	q->front = 0;
	q->rear = capacity - 1;
	q->array = (int*) malloc(q->capacity * sizeof(int));
	return q;
}

void queueDestroy(queue* q){
		free(q->array);	//free array in q
		free(q);				//free q
	}

int queueIsFull(queue* q){
	if (q->size == q->capacity)
		return 1;
	else
		return 0;
}

int queueIsEmpty(queue* q){
	if (q->size == 0)
		return 1;
	else
		return 0;
}

//add item to queue
int queueEnqueue(queue* q, int* value){
	if (!queueIsFull(q))
	{
		q->rear = (q->rear + 1)%q->capacity;
		q->array[q->rear] = *value;
		q->size = q->size + 1;
		return 1;
	}
	else return 0;

}

int queueDequeueFront(queue* queue, int* container){
	if (!queueIsEmpty(queue))
		{
			*container = queue->array[queue->front];
			queue->front = (queue->front + 1)%queue->capacity;
			queue->size = (queue->size) - 1;
			return 1;
		}
	else return 0;
}

int queueDequeueRear(queue* queue, int* container){
	if (!queueIsEmpty(queue))
			{
				*container = queue->array[queue->rear];	//dereference container, assign the value to it
				//queue->rear = queue->rear - 1
				queue->rear = (queue->rear - 1)%queue->capacity;	//this avoids moving data out of queue
				queue->size = queue->size - 1;
				//if (queue->rear < 0)
					//queue->rear = 4;
				return 1;
			}
		else return 0;
}

int* queueFront(queue* queue){
	if (!queueIsEmpty(queue))
		return &queue->array[queue->front];
		//return pointer to first element (&)
	else return NULL; //return INT_MIN;
}

int* queueRear(queue* queue){
 if (!queueIsEmpty(queue))
 	return &queue->array[queue->rear];
 	//return pointer to last element
 else return NULL; //return INT_MIN;
}

void queuePrint(queue* q){
	printf("queue(^: front, *: rear): [");
	int i;
	for(i = 0; i < q->capacity; i++){
		printf("%d", q->array[i]);
		if(i == q->front) printf("^");
		if(i == q->rear) printf("*");
		i == q->capacity - 1 ? printf("] ") : printf(", ");
	}
	printf("size=%d, capacity=%d\n", q->size, q->capacity);
}
