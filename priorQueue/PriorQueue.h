#pragma once
#import ""
typedef struct PQItem {
	int value;
	int prior;
};

typedef struct PriorQueue {
	PQItem* queueArray;
	int size;
	int currSize;
};

PriorQueue* PQInit(int size);
int PQEmpty(PriorQueue* queue);
void PQEnQueue(PriorQueue*, int nKey, int nPrior);
int PQDeQueue(PriorQueue*);
void PQRelease(PriorQueue**);
void PQPrint(PriorQueue*, int);
void IncreaseKey(PriorQueue*, int nKey, int nPrior);
void DecreaseKey(PriorQueue*, int nKey, int nPrior);

void UpdateDown(PriorQueue*, int l, int p);
void UpdateUp(PriorQueue*, int l, int p);