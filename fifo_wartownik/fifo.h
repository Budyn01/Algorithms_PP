#ifndef _FIFO_H
#define _FIFO_H


typedef struct QueueElement
{
	int nKey;
	QueueElement* pNext;
} QueueElement;

typedef struct
{
	QueueElement* head;
	QueueElement* tail;
} Queue;


void print(Queue *queue);
Queue* createQueue();  
int queueIsEmpty(Queue* q);
void enQueue(Queue* queue, int value);
int deQueue(Queue* queue);
void clearQueue(Queue* q);
void deleteQueue(Queue** q);

#endif