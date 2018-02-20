#ifndef _FIFO_H
#define _FIFO_H


typedef struct Queue {
	int head;			// index of first element index
	int tail;			// index of first empty index 
	int currentSize;	// number of elements in array
	int *tab;			// array with elements
	int length;			// size of declared tab
} Queue;

Queue *createQueue(int size);
int queueIsEmpty(Queue *queue);
void enQueue(Queue *queue, int x);
int deQueue(Queue *queue);
void QClear(Queue *queue);
void QDel(Queue **queue);

#endif
