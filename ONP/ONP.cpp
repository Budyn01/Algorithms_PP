#include "ONP.h"
#include "stdafx.h"

double ONP() {
	char oper;
	operationStack *listaOper = NULL;
	doubleStack *listaLiczb = NULL;

	while ((oper = getOper()) == '(') {
		Push(&listaOper, oper);
	}
	ungetc(oper, stdin);
	doublePush(&listaLiczb, getNum());
	while (isOper(oper = getOper())) {
		if (oper == ')') {
			while ((oper = Pop(&listaOper)) != '(') {
				double x = doublePop(&listaLiczb);
				doublePush(&listaLiczb, Calcul(oper, doublePop(&listaLiczb), x));
			}
		}
		else {
			while (priority(oper) <= priority(Top(listaOper))) {
				double x = doublePop(&listaLiczb);
				doublePush(&listaLiczb, Calcul(Pop(&listaOper), doublePop(&listaLiczb), x));
			}
			Push(&listaOper, oper);
			while ((oper = getOper()) == '(') {
				Push(&listaOper, oper);
			}
			ungetc(oper, stdin);
			doublePush(&listaLiczb, getNum());
		}
	}

	while (!IsEmpty(listaOper)) {
		double x = doublePop(&listaLiczb);
		doublePush(&listaLiczb, Calcul(Pop(&listaOper), doublePop(&listaLiczb), x));
	}

	return doublePop(&listaLiczb);
}

int isOper(char znak) {
	switch (znak) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		return 1;
	}
	return 0;
}

int IsDigit(char c) {
	return (c >= '0') && (c <= '9');
}

int priority(char znak) {
	switch (znak) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	}
	return 0;
}

double getNum() {
	char c;
	double res = 0;

	skipSpaces();
	while (IsDigit(c = getOper()))
		res = res * 10 + (c - '0');

	if (c == '.')
	{
		double dzielnik = 10;
		while (IsDigit(c = getOper())) {
			res += (c - '0') / dzielnik;
			dzielnik *= 10;
		}
	}

	ungetc(c, stdin);
	return res;
}

char getOper() {
	skipSpaces();
	return getchar();
}

void skipSpaces() {
	char c;
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}

double Calcul(char oper, double arg1, double arg2) {
	switch (oper) {
	case '+':
		return arg1 + arg2;
	case '-':
		return arg1 - arg2;
	case '*':
		return arg1 * arg2;
	case '/':
		if (arg2 <= 1e-10)
		{
			printf("dzielenie przez 0\n");
			return 0;
		}
		return arg1 / arg2;
	case '^':
		return pow(arg1, arg2);
	default:
		printf("ERROR: blad operatora w funkcjii calcul\n");
		return 0;
	}
}