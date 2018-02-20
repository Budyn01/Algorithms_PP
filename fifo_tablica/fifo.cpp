#include "stdafx.h"
#include "fifo.h"

Queue *createQueue(int size) {
	Queue *queue = (Queue*)calloc(1, sizeof(Queue));
	if (!queue) {
		printf("Error");
		return NULL;
	}
	queue->tab = (int*)calloc(size, sizeof(int));
	if (!queue->tab) {
		printf("Error");
		return NULL;
	}
	//queue->head = 0;
	//queue->tail = 0;
	//queue->currentSize = 0;
//	queue->head = queue->tail =queue->currentSize = 0;

	queue->length = size;
	return queue;
}

int queueIsEmpty(Queue *queue) {
	return !queue->currentSize;
}

void enQueue(Queue *queue, int x) { // Add element to queue
	if (queue->currentSize >= queue->length) {
		printf("ERROR: Queue is full, delete element to insert new");
		return;
	} 
	queue->tab[queue->tail] = x;
	queue->currentSize++;
	queue->tail = (queue->tail + 1) % queue->length;
}
int deQueue(Queue *queue) {
	if (queueIsEmpty(queue)) {
		printf("ERROR: Queue is empty!");
		return 0;
	}
	int temp = queue->tab[queue->head];
	queue->head = (queue->head+1) % queue->length;
	queue->currentSize--;
	return temp;
}

void QClear(Queue *queue) {
	queue->head = queue->tail =queue->currentSize = 0;
}

void QDel(Queue **queue) {
	free((*queue)->tab);
	free(*queue);
}

