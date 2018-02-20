#include "stdafx.h"
#include <iostream>

using namespace std;

void print(Queue *queue) {
	int isEmpty = !queue->head->nKey;
	QueueElement *current = queue->head;
	cout << "{";
	while (current->nKey) {
		cout << current->nKey << ",";
		current = current->pNext;
	}
	cout << (isEmpty ? "empty}\n" : "\b}\n");
}


//Wartownik
Queue* createQueue() {
	Queue *queue = (Queue*)calloc(1, sizeof(Queue));
	if (!queue) {
		printf("ERROR: createQueue");
		return NULL;
	}
	QueueElement *wartownik = (QueueElement*)calloc(1, sizeof(QueueElement));
	if (!wartownik) {
		printf("ERRROR: createWartownik");
		return NULL;
	}
	wartownik->nKey = 0;
	queue->head = queue->tail = wartownik;
	return queue;
};
//Wartownik
int queueIsEmpty(Queue* queue) {
	return !(queue->head->pNext);
}

//Wartownik
void enQueue(Queue* queue, int value) {
	QueueElement *element = (QueueElement*)calloc(1, sizeof(QueueElement));
	if (!element) {
		printf("ERROR: createElement");
		return;
	}
	if (!value) {
		printf("ERROR: 0 jest zarezerwowane dla wartownika!\n");
		return;
	}
	element->nKey = value;
	//element->pNext = queue->tail;
	//if (queueIsEmpty(queue)) {
		//queue->head = element;
	//}
	queue->tail->pNext = element;
	queue->tail = element;
}

//Wartownik
int deQueue(Queue *queue) {
	if (!queue->head->nKey) {
		printf("ERROR: Queue is empty!");
		return 0;
	}
	QueueElement *tempElement = queue->head;
	int temp = tempElement->nKey;
	queue->head = tempElement->pNext;
	free(tempElement);
	/// jesli pusta tail = head
	if (queueIsEmpty(queue)) {
		queue->tail = queue->head;
	}
	return temp;
}

void freeQueue(QueueElement *element) {
	if (element->nKey) {
		freeQueue(element->pNext);
	}
	free(element);
}

void clearQueue(Queue *queue) {

	QueueElement *wartownik = queue->head->pNext;
	freeQueue(queue->head);
	//queue->head = wartownik;
	//queue->tail = wartownik;

}

void deleteQueue(Queue **queue) {
	freeQueue((*queue)->head);
	free(*queue);
}