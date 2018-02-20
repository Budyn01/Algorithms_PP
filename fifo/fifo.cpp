#include "stdafx.h"


void print(Queue *queue) {
	printf("First->  ");
	QueueElement *current = queue->head;
	while (current) {
		printf("%i, ", current->nKey);
		current = current->pNext;
	}
	printf("  <-Last \n");
}

Queue* createQueue() {
	Queue *queue = (Queue*)calloc(1, sizeof(Queue)); //TODO: Check NULL
	if (!queue) {
		printf("Error: createQueue");
		return 0;
	}
	//queue->head = NULL;
	//queue->tail = NULL;
	return queue;
};

int queueIsEmpty(Queue* queue) {
	return !queue->head;
	//	if (queue->head == 0 && queue->tail == 0) {
	////!!!!!!!!!!!!!!		return 1;
	//	}
	//	return 0;
}

void enQueue(Queue* queue, int value) {
	QueueElement *element = (QueueElement*)calloc(1, sizeof(QueueElement));
	element->nKey = value;
	element->pNext = NULL;
	if (queueIsEmpty(queue)) {
		queue->head = element;
	} else {
		queue->tail->pNext = element;
	}
	queue->tail = element;
}

int deQueue(Queue *queue) {
	int temp = queue->head->nKey;
	QueueElement *tempElement = queue->head;
	queue->head = tempElement->pNext;
	free(tempElement);
	// jezeli pusta to tail na null
	if (queueIsEmpty(queue)) {
		queue->tail = NULL;
	}
	return temp;
}

void freeQueue(QueueElement *element) {
	if (element->pNext) {
		freeQueue(element->pNext);
	}
	free(element);
}

void clearQueue(Queue *queue) {
	freeQueue(queue->head);
	queue->head = NULL;
	queue->tail = NULL;
}

void deleteQueue(Queue **queue) {
	freeQueue((*queue)->head);
	free(*queue);
}