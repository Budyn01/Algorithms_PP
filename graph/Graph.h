#include "stdafx.h"
#pragma once


typedef struct List {
	int target;
	double length;
	double time;
	List *next;
} List;

typedef struct Vertex {
	List *list;
	int nearestShop;
	int type;
	double wayToShop;
	int *allway;
	double timeAll;
} Vertex;

void DFS(Vertex *vertex, int speed, int *T, int n);
double Dijkstra(Vertex *veretex, int size, int first);
void PrintGraph(Vertex *vertex, int size);
void ReadData(FILE *file, Vertex *vertex);
Vertex* CreateVertex(int size);
void DeleteVertex(Vertex **vertex, int size);