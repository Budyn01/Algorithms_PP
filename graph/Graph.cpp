#include "stdafx.h"

double Dijkstra(Vertex *vertex, int size, int first) {

	PriorQueue *queue = PQInit(size);

	double *pathLength = (double*)calloc(size, sizeof(double));
	double *time = (double*)calloc(size, sizeof(double));

	if (!pathLength || !time) {
		printf("Can't alloc memory\n");
		return 0;
	}

	for (int i = 0; i < size; i++) {
		pathLength[i] = INT_MAX;
		vertex[first].allway[i] = -1;
	}

	PQEnQueue(queue, first, 0);
	pathLength[first] = 0;

	double length = 0;

	while (!PQisEmpty(queue)) {
		int element = PQDeQueue(queue);
		if (vertex[element].type) {
			vertex[first].timeAll = time[element];
			vertex[first].nearestShop = element;
			PQRelease(&queue);
			length = pathLength[element];
			break;
		}

		List *tmp = vertex[element].list;
		while (tmp) {
			int node = tmp->target;
			double w = tmp->length;
			if ((pathLength[element] + w) < pathLength[node]) {
				vertex[first].allway[node] = element;
				time[node] = time[element] + tmp->time;
				pathLength[node] = pathLength[element] + w;
				PQEnQueue(queue, node, pathLength[node]);
			}
			tmp = tmp->next;
		}
	}
	free(time);
	free(pathLength);
	return length;
}

void DFS(Vertex* vertex, int speed, int *tab, int n) {
	tab[n] = 1;
	List *tmp = vertex[n].list;
	while (tmp) {
		tmp->time = tmp->length / speed * 60;
		if (!tab[tmp->target]) DFS(vertex, speed, tab, tmp->target);
		tmp = tmp->next;
	}
}

Vertex* CreateVertex(int size) {
	Vertex* vertex = (Vertex*)calloc(size, sizeof(Vertex));
	if (!vertex) {
		printf("Can't allocate memory\n");
		return NULL;
	}
	for (int i = 0; i < size; i++) {
		vertex[i].allway = (int*)calloc(size, sizeof(int));
		if (!vertex[i].allway) {
			printf("Can't allocate memory\n");
			return NULL;
		}
	}
	for (int i = 0; i < size; i++) vertex[i].list = NULL;
	return vertex;
}

void DeleteVertex(Vertex** vertex, int size) {
	for (int i = 0; i < size; i++) {
		while ((*vertex)[i].list) {
			List* p = (*vertex)[i].list;
			(*vertex)[i].list = (*vertex)[i].list->next;
			free(p);
		}
	}
	free(*vertex);
	vertex = NULL;
}

void ReadData(FILE *file, Vertex *vertex) {
	char c;
	int i = 0;
	while ((c = getc(file)) != EOF) {
		fscanf(file, "%d", &i);
		List* b = (List*)calloc(1, sizeof(List));
		if (!b) {
			printf("ERROR: Can't allocate memory\n");
			return;
		}
		if (!(vertex[i].list)) {
			fscanf(file, "%d", &vertex[i].type);
			vertex[i].list = b;
			fscanf(file, "%d", &(b->target));
			fscanf(file, "%lf", &(b->length));
		}
		else {
			List* a = vertex[i].list;
			fscanf(file, "%d", &vertex[i].type);
			while (a->next)
				a = a->next;
			a->next = b;
			fscanf(file, "%d", &(b->target));
			fscanf(file, "%lf", &(b->length));
		}
	}
}

void PrintGraph(Vertex* vertex, int size) {
	FILE* file;
	file = fopen("wyniki.txt", "w");
	if (!file) {
		printf("Can't open file\n");
		return;
	}

	for (int i = 0; i < size; i++) if (!vertex[i].type) {
		fprintf(file, "Path: ");
		int* path = (int*)calloc(size, sizeof(int));
		if (!path) {
			printf("error in calloc\n");
		}
		memcpy(path, vertex[i].allway, size * sizeof(int));
		memset(vertex[i].allway, -1, size * sizeof(int));
		int k = vertex[i].nearestShop;
		vertex[i].allway[0] = k;
		int j = 0;
		for (j = 1; k != i; j++) {
			vertex[i].allway[j] = path[k];
			k = path[k];
		}
		for (int n = 0; n < (j + 1) / 2; n++) {
			int temp = vertex[i].allway[j - n - 1];
			vertex[i].allway[j - n - 1] = vertex[i].allway[n];
			vertex[i].allway[n] = temp;
		}
		for (int j = 0;; j++) {
			if (vertex[i].allway[j] == -1) break;
			fprintf(file, "%d ", vertex[i].allway[j]);
		}
		fprintf(file, "Distance: %.1lf Shop:%d Time:%.1lf minutes\n", vertex[i].wayToShop, vertex[i].nearestShop, vertex[i].timeAll);
	}
	fclose(file);
}