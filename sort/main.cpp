#include "stdafx.h"

typedef void(*sort)(int *, int);

void showArray(int *tab, int size);
int *createEmptyArray(int size);
double simpleTimer(int *, int, sort);
void timer(sort functionTable[], int numberOfFunction, int *table, int size, const char *functionName[]);
int randomInt();
int *createRandomArray(int size);

int main(int argc, char *argv[]) {

	srand(5);
	if (argc != 2) {
		printf("Usage: %s <size>\n", argv[0]);
		return 1;
	}
	int size = atoi(argv[1]);

	int *table = createRandomArray(size);
	sort sortFunctionTab[] = { SelectionSort, InsertionSort, MixedSort, HalfSort, QuickSort, MergeSort, HeapSort, NaturalSort};
	const char *sortFunctionNames[] = { "SelectionSort", "InsertionSort", "MixedSort", "HalfSort", "QuickSort", "MergeSort", "HeapSort", "NaturalSort"};

	timer(sortFunctionTab, 8, table, size, sortFunctionNames);
	system("PAUSE");
	return 0;
}

//    Timers
double simpleTimer(int *table, int size, sort sortowanie) {
	clock_t start, end;
	start = clock();
	sortowanie(table, size);
	end = clock();
	return ((double)(end - start) / CLOCKS_PER_SEC);
}

void timer(sort functionTable[], int numberOfFunction, int *table, int size, const char *functionName[]) {
	int *copyOfTable = createEmptyArray(size);
	printf("Sorting time for tab with %i elements: \n", size);
	for (int i = 0; i < numberOfFunction; ++i) {
		memcpy(copyOfTable, table, size * sizeof(int));
		printf("%s: \t %lf sekundy. \n", functionName[i],
			simpleTimer(copyOfTable, size, functionTable[i]));
		showArray(copyOfTable, size);
	}
	free(copyOfTable);
};
//  End of Timers


int *createEmptyArray(int size) {
	int *table = (int *)calloc(size, sizeof(int));
	if (!table) {
		printf("ERROR: createEmptyArray\n");
		return 0;
	}
	return table;
};

void showArray(int *tab, int size) {
	printf("Table: [");
	for (int i = 0; i < size - 1; ++i) {
		printf("%i, ", tab[i]);
	}
	printf("%i] \n", tab[size - 1]);
};

int randomInt() {
	return rand() % 100;
}
int *createRandomArray(int size) {
	int *table = createEmptyArray(size);
	for (int i = 0; i < size; ++i) {
		table[i] = randomInt();
	}
	return table;
}