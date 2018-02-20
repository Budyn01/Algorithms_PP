#include "stdafx.h"

#include <iostream>
using namespace std;

void UpdateDown(PriorQueue*, int l, int p);
void UpdateUp(PriorQueue*, int l, int p);

PriorQueue* PQInit(int size) {
	PriorQueue* queue = (PriorQueue*)calloc(1, sizeof(PriorQueue));
	if (!queue) {
		printf("Can't allocate memory\n");
		return NULL;
	} //!!!!!!!!komunk
	queue->queueArray = (PQItem*)calloc(size, sizeof(PQItem));
	if (!queue->queueArray) {
		printf("Can't allocate memory\n");
		return NULL;
	} //!!!!
	queue->size = size;
	return queue;
}
int PQisEmpty(PriorQueue* queue)
{
	return !queue->currentSize;
}
void PQEnQueue(PriorQueue* queue, int value, double prior)
{
	if (queue->currentSize == queue->size)
	{
		printf("Queue is full. \n");
		return;
	}

	queue->queueArray[queue->currentSize].value = value;
	queue->queueArray[queue->currentSize].prior = prior;

	UpdateUp(queue, 0, queue->currentSize);

	queue->currentSize++;

}
int PQDeQueue(PriorQueue* queue)
{
	if (PQisEmpty(queue))
	{
		printf("Queue is empty. \n");
		return 0;
	}

	int temp = queue->queueArray[0].value;
	
	queue->currentSize--;
	queue->queueArray[0] = queue->queueArray[queue->currentSize];
	
	UpdateDown(queue, 0, queue->currentSize);

	return temp;
}
void PQRelease(PriorQueue** queue)
{
	free((*queue)->queueArray);
	free(*queue);
	*queue = NULL;
}

void DecreaseKey(PriorQueue* queue, int index, double prior)
{
	if (index > queue->currentSize) {
		printf("Out of bound!\n");
		return;
	}
	if (queue->queueArray[index].prior > prior) {
		queue->queueArray[index].prior = prior;
	}
	UpdateDown(queue, index, queue->currentSize);
}
void IncreaseKey(PriorQueue* queue, int index, double prior)
{
	if (index > queue->currentSize) {
		printf("Out of bound!\n");
		return;
	}
	if (queue->queueArray[index].prior < prior) {
		queue->queueArray[index].prior = prior;
	}

	UpdateUp(queue, 0, index);//!!!!!od do
}
void UpdateDown(PriorQueue* queue, int left, int right) { 
	int i = left;
	int j = 2 * i + 1;
	PQItem temp = queue->queueArray[i];
	while (j <= right) {
		if (j < right)
			if (queue->queueArray[j].prior > queue->queueArray[j + 1].prior)
				j++;
		if (temp.prior < queue->queueArray[j].prior)
			break;
		queue->queueArray[i] = queue->queueArray[j];
		i = j;
		j = 2 * i + 1;
	}
	queue->queueArray[i] = temp;
}
void UpdateUp(PriorQueue* queue, int left, int right) {
	int i = right;
	int j = (i - 1) / 2;
	PQItem temp = queue->queueArray[i];
	while (i > 0 && queue->queueArray[j].prior > temp.prior) {
		queue->queueArray[i] = queue->queueArray[j];
		i = j;
		j = (i - 1) / 2;
	}
	queue->queueArray[i] = temp;
}

