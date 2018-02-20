#include "DoubleStack.h"
#include <malloc.h>
#include "stdafx.h"

void doublePush(doubleStack **stos, double liczba) {
	doubleStack *temp = (doubleStack *)malloc(sizeof(doubleStack));
	if (!temp) {
		printf("ERROR: in doublePush!");
		system("exit");
	}
	memset(temp, 0, sizeof(temp));
	temp->key = liczba;
	temp->next = *stos;
	*stos = temp;
}

double doublePop(doubleStack **stos) {
	double x = 0;
	if (!doubleIsEmpty(*stos)) {
		x = doubleTop(*stos);
		doubleDel(stos);
	}
	else
		printf("ERROR(doublePop<number>) Stack underflow\n");
	return x;
}

int doubleIsEmpty(doubleStack *stos) {
	return !stos;
}

void doubleDel(doubleStack **stos) {
	if (doubleIsEmpty(*stos)) {
		printf("ERROR(isEmpty<number>) Stack Underflow\n");
		return;
	}
	doubleStack *temp = *stos;
	*stos = temp->next;
	free(temp);
}

double doubleTop(doubleStack *stos) {
	if (doubleIsEmpty(stos)) {
		printf("ERROR(top<number>) stack underflow\n");
		return 0;
	}
	return stos->key;
}

