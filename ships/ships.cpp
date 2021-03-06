#include "stdafx.h"

//zdefini stale N i M - wymiary  (na 10)
#define DEPTH_MIN 10    // glebokosc zanurzenia okretu
#define COL 10
#define ROW 10

// zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT
enum DIRECTION {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

/*
	depthMap - tabela glebokosci o romiarze row i col
	shipDepth - glebokosc zanurzenia ststku
	x, y - wspol skad robimy kolejny ruch
	solutionMap tablica kolejnych ruchow
	xDestination, yDestination - wsporzedne portu
*/
int root(int** depthMap, int row, int col, int shipDepth, int x, int y, int **solutionMap, int xDestination, int yDestination);

/*
	depthMap - tablica okreslajaca glebokosc w kazdym kwadracie
	row, col - rozmia pTab,
	shipDepth - minimalna glebokosc aby statek przpelynal
	x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
	notMoveDirection - kierunek ruchu
	ps py - nowe wspolrzedne
	solutionMap - tablica pamietajaca ruchy o rozm nRow, nCol
*/
int move(int** depthMap, int row, int col, int depth, int notMoveDirection, int x, int y, int* newX, int* newY, int** solutionMap);

void ReadMap(char* filename, int** seaMap, int row, int col);
int CreateMatrix(int ***pointerMatrix, int row, int col);
void printMap(int **map, int row, int col);
void freeMap(int*** map, int row);

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: map path.\n");
		return 1;
	}

	int **depthMap = NULL;
	if (!CreateMatrix(&depthMap, ROW, COL)) {
		printf("ERROR: with allocation depthMap\n");
		return 1;
	};

	int **solutionMap = NULL;
	if (!CreateMatrix(&solutionMap, ROW, COL)) {
		printf("ERROR: with allocation solutionMap\n");
		return 1;
	};

	ReadMap(argv[1], depthMap, ROW, COL);


	if (root(depthMap, ROW, COL, DEPTH_MIN, 0, 0, solutionMap, 9, 9)) {
		printMap(solutionMap, ROW, COL);
	}
	else {
		printf("No way to get to the port\n");
	}

	freeMap(&depthMap, ROW);
	freeMap(&solutionMap, ROW);

	system("PAUSE");
	return 0;
}

void ReadMap(char* filename, int** seaMap, int row, int col) {

	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("ERROR: can't read file!");
		return;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(file, "%i", &seaMap[i][j]);
		}
	}

	fclose(file);
}

int CreateMatrix(int ***pointerMatrix, int row, int col) {
	*pointerMatrix = (int **)calloc(row, sizeof(int*));
	if (!pointerMatrix) {
		printf("ERROR: Allocation error(1).\n");
		return 0;
	}
	for (int i = 0; i < row; i++) {
		(*pointerMatrix)[i] = (int *)calloc(col, sizeof(int));
		if (!(**pointerMatrix)) {
			printf("ERROR: Allocation error(2).\n");
			return 0;
		}
	}
	return 1;
}

int root(int** depthMap, int row, int col, int shipDepth, int x, int y, int **solutionMap, int xDestination, int yDestination) {
	
	solutionMap[x][y] = 1;		
	if (x == xDestination && y == yDestination)	return 2;
	
	int newX = x;
	int newY = y;
	
	for (int i = UP; i <= LEFT; i++) {
		if (move(depthMap, row, col, shipDepth, i, x, y, &newX, &newY, solutionMap)) {
			if (root(depthMap, row, col, shipDepth, newX, newY, solutionMap, xDestination, yDestination))
				return 2;
		}
	}
	solutionMap[x][y] = 0;
	return 0;
	/*
	//if (x == xDestination && y == yDestination) {
	//	solutionMap[x][y] = 1;
	//	return 1;
	//}

	//solutionMap[x][y] = 1;

	//for (int i = 0; i < 4; i++) {
	//	if (move(depthMap, row, col, shipDepth, i, x, y, &x, &y, solutionMap)) {
	//		if (root(depthMap, row, col, shipDepth, x, y, solutionMap, xDestination, yDestination))
	//			return 1;
	//	}
	//}

	//solutionMap[x][y] = 0;



	//if (isSafe(depthMap, x, y, row, col, shipDepth)) { //for

	//	*(*(solutionMap + x) + y) = 1;
	//	if (direction != UP && root(depthMap, row, col, shipDepth, x + 1, y, solutionMap, xDestination, yDestination, DOWN)) { //go down
	//		return 1;
	//	}

	//	if (direction != LEFT && root(depthMap, row, col, shipDepth, x, y + 1, solutionMap, xDestination, yDestination, RIGHT)) { //go right
	//		return 1;
	//	}
	//	if (direction != DOWN && root(depthMap, row, col, shipDepth, x - 1, y, solutionMap, xDestination, yDestination, UP)) { //go up
	//		return 1;
	//	}
	//	if (direction != RIGHT && root(depthMap, row, col, shipDepth, x, y - 1, solutionMap, xDestination, yDestination, LEFT)) { //go left
	//		return 1;
	//	}

	//	//*(*(solutionMap + x) + y) = 0;
	//	solutionMap[x][y] = 0;
	//	return 0;
	//} */
}

int move(int** depthMap, int row, int col, int shipDepth, int direction, int x, int y, int* newX, int* newY, int** solutionMap) {
	switch (direction) {
	case UP:	*newX = x - 1;	*newY = y; break;
	case RIGHT: *newY = y + 1;	*newX = x; break;
	case DOWN:	*newX = x + 1;	*newY = y; break;
	case LEFT:	*newY = y - 1;	*newX = x; break;
	}
	if (*newX > row - 1 || *newX < 0 || *newY > col - 1 || *newY < 0) return 0;
	if (solutionMap[*newX][*newY]) return 0;
	if (depthMap[*newX][*newY] < shipDepth + 1)	return 0;
	return 1;
}

void printMap(int **map, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) printf(" %d ", map[i][j]);
		printf("\n");
	}
}

void freeMap(int*** map, int row) {
	for (int i = 0; i < row; i++) free((*map)[i]);
	free(*map);
	*map = NULL;
}