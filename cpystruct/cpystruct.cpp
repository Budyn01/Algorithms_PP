// cpystruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define MAX 20
#define MAX_STR 5

using namespace std;

typedef struct {
	int key;
	char* str;
} T;

void printTab(T* tab, int size);

int main()
{
	T* t = (T*)calloc(MAX, sizeof(T));


	srand(time(NULL));
	for (int i = 0, char c = 'A'; i < MAX; i++, a++) {
		t[i].key = rand() % 20;
		t[i].str = (char*)calloc(MAX_STR, sizeof(char));
		for (int j = 0; j < MAX_STR-1; j++)		{
			t[i].str[j] = c;	
		}
	}
	
	printTab(t, MAX);

	T *t1 = (T*)calloc(MAX, sizeof(T));
	copyTab(t, t1, MAX);


	free(t);
	return 0;
}

void printTab(T* tab, int size) {
	for (int i = 0; i < size; i++)	{
		cout << " (" << tab[i].key << ", " << tab[i].str << ") " << endl;
	}
}

void copyTab(T* tab1, T* tab2, int size) {
	for(int i = 0; i < size)
}