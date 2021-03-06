#include "stdafx.h"

#define SPEED 4

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: args \n");
		return 1;
	}

	FILE *file = fopen(argv[1], "r");
	if (!file) {
		printf("Can't open file. \n");
		return 1;
	}
	int size = 0;
	fscanf(file, "%d", &size);
	Vertex *vertex = CreateVertex(size);
	ReadData(file, vertex);
	fclose(file);

	int* tab = (int*)calloc(size, sizeof(int));
	if (!tab) {
		printf("Failed to allocate memory\n");
		return 1;
	}

	DFS(vertex, SPEED, tab, 1);
	for (int i = 0; i < size; i++) {
		if (!vertex[i].type) {
			vertex[i].wayToShop = Dijkstra(vertex, size, i);
		}
	}

	PrintGraph(vertex, size);
	DeleteVertex(&vertex, size);

	system("PAUSE");
	return 0;
}
