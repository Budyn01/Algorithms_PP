#pragma once

#include "stdafx.h"

struct operationStack {
	char key;
	operationStack *next;
};

void Push(operationStack **stack, char znak);

char Pop(operationStack **stack);

int IsEmpty(operationStack *stack);

void Del(operationStack **stack);

char Top(operationStack *stack);
