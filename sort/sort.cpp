#include "stdafx.h"
#include <iostream>
using namespace std;

void Merge(int *data, int *tmp, int left, int mid, int right);
void Update(int *data, int left, int size);
int Copy(int *data, int *tmp, int size, int *i, int *x);
void CopySerie(int *data, int *tmp, int size, int *i, int *x);

inline void swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void SelectionSort(int *data, int size) {
	for (int i = 0; i < size - 1; i++) {
		int minimal = data[i];
		int x = i;
		for (int j = i + 1; j < size; j++) {
			if (data[j] < minimal) {
				minimal = data[j];
				x = j;
			}
		}
		data[x] = data[i];
		data[i] = minimal;
	}
}

void InsertionSort(int *data, int size) {
	for (int i = 1; i < size; i++) {
		int value = data[i];
		int j;
		for (j = i - 1; j >= 0 && data[j] > value; j--) {
			data[j + 1] = data[j];
		}
		data[j + 1] = value;
	}
}

void MixedSort(int *data, int size) {
	int k = size - 1;
	int l = 0;
	int p = size - 1;
	while (l < p) {
		for (int i = p; i >= 0; i--) {
			if (data[i - 1] > data[i]) {
				swap(&data[i - 1], &data[i]);
			}
			k = i;
		}
		l = k + 1;
		for (int i = l; i <= p; i++) {
			if (data[i - 1] > data[i]) {
				swap((data + i - 1), (data + i));
			}
			k = i;
		}
		p = k - 1;
	}
}

void HalfSort(int *data, int size) {
	for (int i = 1; i < size; i++) {
		int key = data[i];
		int l = 0;
		int p = i - 1;
		while (l <= p) {
			int m = (l + p) / 2;
			if (key < data[m]) {
				p = m - 1;
			}
			else {
				l = m + 1;
			}
		}
		for (int j = i - 1; j >= l; j--) {
			data[j + 1] = data[j];
		}
		data[l] = key;
	}
}

void QuickSortRec(int *data, int left, int right) {
	int i = left;
	int j = right;
	int x = data[(left + right) / 2];
	while (i <= j) {
		while (data[i] < x) i++;
		while (data[j] > x) j--;
		if (i <= j) {
			if (i < j) {
				swap((data + i), (data + j));
			}
			i++;
			j--;
		}
	}
	if (left < j) QuickSortRec(data, left, j);
	if (right > i) QuickSortRec(data, i, right);
}

void QuickSort(int *data, int size) {
	QuickSortRec(data, 0, size - 1);
}

void Merge(int *data, int *tmp, int left, int mid, int right) {
	//	tmp = (int*)calloc((right + 1) - left, sizeof(int));
	//tmp < data  //memcpy
	
	//memcpy(tmp + left, data + left, right );
	for (int i = left; i <= right; i++) tmp[i] = data[i];

	int i = left;
	int q = left;
	int j = mid + 1;

	while (i <= mid && j <= right) {
		if (tmp[i] < tmp[j]) {
			data[q++] = tmp[i++];
		}
		else data[q++] = tmp[j++];
	}
	//while (i <= mid && j <= right) {
	//	if (*(tmp + j) < *(tmp + i)) *(data + q) = *(tmp + j++);
	//	else *(data + q) = *(tmp + i++);
	//	q++;
	//}

	while (i <= mid) data[q++] = tmp[i++];
	//	free(tmp);
	//tmp = NULL;
}

void MergeSortRec(int *data, int *tmp, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSortRec(data, tmp, left, mid);
		MergeSortRec(data, tmp, mid + 1, right);
		Merge(data, tmp, left, mid, right);
	}
}

void MergeSort(int *data, int size) {
	int *tmp = NULL;
	tmp = (int*)calloc(size, sizeof(int));
	if (!tmp) {
		printf("Error with allocation!\n");
		return;
	}
	MergeSortRec(data, tmp, 0, size - 1); // -1
	free(tmp);
	tmp = NULL;
}

void Update(int *data, int left, int size) {
	int i = left;
	int j = 2 * i + 1;
	int x = data[i];
	while (j <= size) {
		if (j < size)
			if (data[j] < data[j + 1]) j++;
		if (x > data[j]) break;
		data[i] = data[j];
		i = j;
		j = 2 * i + 1;
	}
	data[i] = x;
}

void HeapSort(int *data, int size) { //OK
	for (int mid = size / 2; mid >= 0; mid--) {
		Update(data, mid, size);
	}
	for (int right = size - 1; right > 0; right--) {
		swap((data), (data + right));
		Update(data, 0, right + 1);
	}
}

void NaturalSort(int *data, int size) { //OK
	int *tmp1 = (int*)calloc(size, sizeof(int));
	if (!tmp1) {
		printf("ERROR: allocation in NaturalSort\n");
		return;
	}
	int *tmp2 = (int*)calloc(size, sizeof(int));
	if (!tmp1) {
		printf("ERROR: allocation in NaturalSort\n");
		return;
	}
	int series;

	do {
		int i = 0;
		int j = 0;
		int k = 0;

		while (i < size) {
			while ((i < size - 1) && (*(data + i) <= *(data + i + 1))) *(tmp1 + j++) = *(data + i++);
			if (i < size) *(tmp1 + j++) = *(data + i++);
			while ((i < size - 1) && (*(data + i) < *(data + i + 1))) *(tmp2 + k++) = *(data + i++);
			if (i < size) *(tmp2 + k++) = *(data + i++);
		}

		int endtmp1 = j;
		int endtmp2 = k;
		series = 0;
		i = j = k = 0;
		while ((j < endtmp1) && (k < endtmp2)) {
			int end = 0;
			while (!end) {
				if (*(tmp1 + j) <= *(tmp2 + k)) {
					end = Copy(data, tmp1, endtmp1, &i, &j);
					if (end) CopySerie(data, tmp2, endtmp2, &i, &k);
				}
				else {
					end = Copy(data, tmp2, endtmp2, &i, &k);
					if (end) CopySerie(data, tmp1, endtmp1, &i, &j);
				}
			}
			series++;
		}
		while (j < endtmp1) {
			CopySerie(data, tmp1, endtmp1, &i, &j);
			series++;
		}
		while (k < endtmp2) {
			CopySerie(data, tmp2, endtmp2, &i, &j);
			series++;
		}
	} while (series > 1);
	free(tmp1);
	free(tmp2);
}

void CopySerie(int *data, int *tmp, int size, int *i, int *x) {
	int end = 0;
	do {
		end = Copy(data, tmp, size, i, x);
	} while (!end);
}

int Copy(int *data, int *tmp, int size, int* i, int *x) {
	data[(*i)++] = tmp[(*x)++];
	if (*x == size) return 1;
	return tmp[(*x) - 1] > tmp[(*x)];
}