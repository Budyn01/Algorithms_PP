#pragma once

#include "stdafx.h"


struct doubleStack {
	double key;
	doubleStack *next;
};

void doublePush(doubleStack **stos, double liczba);

double doublePop(doubleStack **stos);

int doubleIsEmpty(doubleStack *stos);

void doubleDel(doubleStack **stos);

double doubleTop(doubleStack *stos);