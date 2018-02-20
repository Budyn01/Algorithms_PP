#pragma once

typedef struct {
	int value;
	double prior;
} PQItem;
typedef struct
{
	PQItem* queueArray;
	int size;
	int currentSize;
}PriorQueue;

PriorQueue* PQInit(int);
int PQisEmpty(PriorQueue*);
void PQEnQueue(PriorQueue*, int, double);
int PQDeQueue(PriorQueue*);
void PQRelease(PriorQueue**);
void DecreaseKey(PriorQueue*, int, double);
void IncreaseKey(PriorQueue*, int, double);

