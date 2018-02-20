#include "stdafx.h"

using namespace std;
//
//void swap(int *a, int *b) {
//	*a ^= *b;
//	*b ^= *a;
//	*a ^= *b;
//}
//
////  QuickSort
//int partition(int *tab, int l, int r) {
//	int pivot, i, j, t;
//	pivot = tab[l];
//	i = l;
//	j = r + 1;
//
//	while (true) {
//		do ++i; while (tab[i] <= pivot && i <= r);
//		do --j; while (tab[j] > pivot);
//		if (i >= j) break;
//		t = tab[i];
//		tab[i] = tab[j];
//		tab[j] = t;
//	}
//	t = tab[l];
//	tab[l] = tab[j];
//	tab[j] = t;
//	return j;
//}
//
//void quickSSort(int *tab, int l, int r) {
//	int j;
//
//	if (l < r) {
//		j = partition(tab, l, r);
//		quickSSort(tab, l, j - 1);
//		quickSSort(tab, j + 1, r);
//	}
//
//}
//
//void quickSort(int *tab, int size) {
//	quickSSort(tab, 0, size - 1);
//}
////  End of QuickSort
//
//
////  HeapSort
//void heapify(int *tab, int i, int n) {
//	int l = 2 * i, r = 2 * i + 1;
//	int great;
//	if (l < n && tab[l] > tab[i])
//		great = l;
//	else
//		great = i;
//
//	if (r < n && tab[r] > tab[great])
//		great = r;
//
//	if (great != i) {
//		int temp = tab[i];
//		tab[i] = tab[great];
//		tab[great] = temp;
//		heapify(tab, great, n);
//	}
//}
//
//void buildHeap(int *tab, int n) {
//	int i;
//	for (i = (n - 1) / 2; i >= 1; i--)
//		heapify(tab, i, n);
//}
//
//void heapSort(int *tab, int size) {
//	buildHeap(tab, size);
//	int i;
//	for (i = size - 1; i >= 1; i--) {
//		int temp = tab[1];
//		tab[1] = tab[i];
//		tab[i] = temp;
//		heapify(tab, 1, i);
//	}
//}
////  End of HeapSort
//
////    SelectionSort
//void selectionSort(int *tab, int size) {
//	int temp;
//	int i, j;
//
//	for (i = 0; i < size - 1; i++) {
//		for (j = i + 1; j < size; j++) {
//			if (tab[i] > tab[j]) {
//				temp = tab[i];
//				tab[i] = tab[j];
//				tab[j] = temp;
//			}
//		}
//	}
//}
////  End of SelectionSort
//
////  InsertionSort
//void insertionSort(int *tab, int size) {
//	int key;
//	int i, j;
//	for (i = 2; i < size; ++i) {
//		key = tab[i];
//
//		for (j = i - 1; j >= 0 && tab[j] > key; --j) {
//			tab[j + 1] = tab[j];
//		}
//
//		tab[j + 1] = key;
//	}
//}
////    End of InsertionSort
//
////    HalfSort
//void halfSort(int *tab, int size) {
//
//	int key;
//	int i, j;
//	int k, p, m;
//	for (i = 1; i < size; ++i) {
//		key = tab[i];
//		k = 0;
//		p = i - 1;
//		while (k <= p) {
//			m = (k + p) / 2;
//			if (key < tab[m]) {
//				p = m - 1;
//			}
//			else {
//				k = m + 1;
//			}
//		}
//
//		for (j = i - 1; j >= k; j--) {
//			tab[j + 1] = tab[j];
//			tab[k] = key;
//		}
//	}
//}
////    End of HalfSort
//
////  ShakeSort
//void shakeSort(int *tab, int size) {
//	int bottom = 0, top = size - 1;
//	bool replace = true;
//
//	while (replace) {
//		replace = false;
//
//		for (int i = bottom; i < top; i++) {
//			if (tab[i] > tab[i + 1]) {
//				swap(tab[i], tab[i + 1]);
//
//				replace = true;
//			}
//		}
//
//
//		top--;
//		for (int i = top; i > bottom; i--) {
//			if (tab[i] < tab[i - 1]) {
//				swap(tab[i], tab[i - 1]);
//
//				replace = true;
//			}
//		}
//
//		bottom++;
//	}
//}
////    Enf of ShakeSort
//
//
////   MergeSort
//void merge(int tab[], int start, int srodek, int koniec) {
//	int *tab_pom = new int[(koniec - start + 1)]; // utworzenie tablicy pomocniczej
//	int i = start, j = srodek + 1, k = 0; // zmienne pomocnicze
//
//	while (i <= srodek && j <= koniec) {
//		if (tab[j] < tab[i]) {
//			tab_pom[k] = tab[j];
//			j++;
//		}
//		else {
//			tab_pom[k] = tab[i];
//			i++;
//		}
//		k++;
//	}
//
//	if (i <= srodek) {
//		while (i <= srodek) {
//			tab_pom[k] = tab[i];
//			i++;
//			k++;
//		}
//	}
//	else {
//		while (j <= koniec) {
//			tab_pom[k] = tab[j];
//			j++;
//			k++;
//		}
//	}
//
//	for (i = 0; i <= koniec - start; i++)
//		tab[start + i] = tab_pom[i];
//
//}
//
//void merge_sort(int *tab, int start, int koniec) {
//	int srodek;
//
//	if (start != koniec) {
//		srodek = (start + koniec) / 2;
//		merge_sort(tab, start, srodek);
//		merge_sort(tab, srodek + 1, koniec);
//		merge(tab, start, srodek, koniec);
//	}
//}
//
//void mergeSort(int *tab, int size) {
//	merge_sort(tab, 0, size - 1);
//};
////  End of MergeSort
//
//
//int *sorter(int finalTab[], int size) {
//
//	int *tapeA = (int *)calloc(size, sizeof(int));
//	int *tapeB = (int *)calloc(size, sizeof(int));
//	int *tapeC = (int *)calloc(size, sizeof(int));
//	int sizeA = 0;
//	int sizeB = 0;
//	int sizeC = 0;
//
//
//	int saveTo = 1;
//	int series = 0;
//
//	for (int i = 0; i < size; ++i) {
//
//		if (saveTo) {
//			tapeA[sizeA++] = finalTab[i];
//		}
//		else {
//			tapeB[sizeB++] = finalTab[i];
//		}
//
//		if (finalTab[i] > finalTab[i + 1]) {
//			saveTo = !saveTo;
//			series++;
//		};
//
//		if (series == 2 || (i + 1) == size) {
//			int a = 0;
//			int b = 0;
//			for (int k = 0; k < sizeA + sizeB; ++k) {
//				if (tapeA[a] < tapeB[b] || sizeB == b) {
//					tapeC[sizeC++] = tapeA[a++];
//				}
//				else {
//					tapeC[sizeC++] = tapeB[b++];
//				}
//			}
//			series = 0;
//			sizeA = 0;
//			sizeB = 0;
//		}
//	}
//	free(tapeA);
//	free(tapeB);
//	return tapeC;
//}
//
//int isSorted(int *tab, int size) {
//	for (int i = 0; i < size - 1; ++i) {
//		if (tab[i] > tab[i + 1]) return 0;
//	}
//	return 1;
//}
//
//void naturalSort(int *tab, int size) {
//
//	while (!isSorted(tab, size)) {
//		tab = sorter(tab, size);
//	}
//}
//
//
//
//
//
//
