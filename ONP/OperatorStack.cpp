#include <malloc.h>
#include "stdafx.h"
#include "OperatorStack.h"

void Push(operationStack **stack, char znak) {
	operationStack *nowy = (operationStack *)malloc(sizeof(operationStack));
	memset(nowy, 0, sizeof(nowy));
	nowy->key = znak;
	nowy->next = *stack;
	*stack = nowy;
}

char Pop(operationStack **stack) {
	char c = 0;
	if (!IsEmpty(*stack)) {
		c = Top(*stack);
		Del(stack);
	}
	else
		printf("Error(doublePop()<oper>) Stack underflow");
	return c;
}

int IsEmpty(operationStack *stack) {
	return !stack;
}

void Del(operationStack **stack) {
	if (IsEmpty(*stack)) {
		printf("ERROR(doubleDel<oper>) Stack Underflow\n");
	}
	else {
		operationStack *temp = *stack;
		*stack = temp->next;
		free(temp);
	}
}

char Top(operationStack *stos) {
	if (IsEmpty(stos)) {
		//printf("ERROR(doubleTop<oper> Stack underflow)");			//
		return 0;
	}
	return stos->key;
}
