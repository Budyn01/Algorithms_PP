// queue_prior.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void PQPrint(PriorQueue* queue, int i)
{
	if (PQisEmpty(queue))
	{
		printf("Queue is empty\n");
		return;
	}
	if (i >= queue->currentSize)
		return;
	PQPrint(queue, 2 * i + 1);
	cout << "Value: " << queue->queueArray[i].value << " Prior: " << queue->queueArray[i].prior << endl;
	PQPrint(queue, 2 * i + 2);
}

int main()
{

	PriorQueue *queue = PQInit(10);
	PQEnQueue(queue, 3, 3);
	PQEnQueue(queue, 1, 1);
	PQEnQueue(queue, 2, 2);
	PQEnQueue(queue, 5, 5);
	PQEnQueue(queue, 4, 4.6);
	PQEnQueue(queue, 7, 7);
	PQEnQueue(queue, 6, 6);
	
	cout << "DeQueue 1: " << PQDeQueue(queue) << endl;
	cout << "DeQueue 2: " << PQDeQueue(queue) << endl;
	cout << "DeQueue 3: " << PQDeQueue(queue) << endl;
	cout << "DeQueue 4: " << PQDeQueue(queue) << endl;
	cout << "DeQueue 5: " << PQDeQueue(queue) << endl;
	cout << "DeQueue 6: " << PQDeQueue(queue) << endl;
	cout << "DeQueue 7: " << PQDeQueue(queue) << endl;




	system("PAUSE");
    return 0;
}

