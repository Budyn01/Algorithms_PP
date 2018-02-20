#pragma once
#ifndef _ONP
#define _ONP

#include <math.h>
#include "DoubleStack.h"
#include "OperatorStack.h"

double ONP();

int isOper(char c);

int IsDigit(char c);

int priority(char c);

double getNum();

char getOper();

void skipSpaces();

double Calcul(char cOper, double arg1, double arg2);

#endif



