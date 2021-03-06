#include "stdafx.h"

void HeapCheck();
void CalcStat(int* pNums5, int* pNums2, LottoPlayer** pDraws, int nDrawsNo);
void Sort(LottoPlayer** pDraws, int nDrawsNo);
int strCompare(char* s1, char* s2);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR: <input_file> <output_file>\n");
		system("PAUSE");
		return 1;
	}

	LottoPlayer** playerTab = NULL;

	int currentPlayerNumber = 0;

	if ((currentPlayerNumber = ReadData(&playerTab, argv[1])) == 0) {
		printf("ERROR: read playerNumber.\n");
		system("PAUSE");
		return 2;
	}

	int* results5 = (int*)calloc(5, sizeof(int));
	int* results2 = (int*)calloc(2, sizeof(int));

	if (!results2 || !results5) {
		printf("Memory Allocation Error.\n");
		system("PAUSE");
		return 0;
	}

	CalcStat(results5, results2, playerTab, currentPlayerNumber);

	Sort(playerTab, currentPlayerNumber);

	FILE* file = fopen(argv[2], "w");
	if (!file) {
		printf("Can not open \"%s\" file.\n", argv[2]);
		system("PAUSE");
		return 0;
	}
	PrintResults(file, results5, results2, playerTab, currentPlayerNumber);

	FreeMem(playerTab, currentPlayerNumber);
	playerTab = NULL;

	//HeapCheck();


	system("PAUSE");
	return 0;
}

void HeapCheck() {
	int  heapstatus;
	heapstatus = _heapchk();
	switch (heapstatus)
	{
	case _HEAPOK:
		printf("\n OK - heap is fine\n");
		break;
	case _HEAPEMPTY:
		printf("\n OK - heap is empty\n");
		break;
	case _HEAPBADBEGIN:
		printf("\nERROR - bad start of heap\n");
		break;
	case _HEAPBADNODE:
		printf("\nERROR - bad node in heap\n");
		break;
	}
}

void CalcStat(int* bet5, int* bet2, LottoPlayer** draws, int drawsNumber) {
	for (int i = 0; i < drawsNumber; i++) {
		LottoPlayer* player = draws[i];

		for (int j = 0; j < player->currentBet; j++) {
			Bet bet = player->bets[j];
			int* pDraw5 = bet.bet5;
			for (int k = 0; k < 5; k++, pDraw5++) {
				if (*pDraw5 > 0 && *pDraw5 <= 50) bet5[*pDraw5 - 1]++;
				else printf("Picked value: %d is out of allowed reach. CalcStat().", *pDraw5);
			}
			int* pDraw2 = bet.bet2;
			for (int k = 0; k < 2; k++, pDraw2++) {
				if (*pDraw2 > 0 && *pDraw2 <= 10) bet2[*pDraw2 - 1]++;
				else printf("Picked value: %d is out of allowed reach. CalcStat().", *pDraw2);
			}
		}
	}
}

void Sort(LottoPlayer** pDraws, int nDrawsNo) {
	for (int i = 0; i < nDrawsNo - 1; i++) {
		int indeks = i;
		LottoPlayer* min = pDraws[i];

		int res;

		for (int j = i + 1; j < nDrawsNo; j++) {
			if ((res = strCompare(min->lastName, pDraws[j]->lastName)) > 0) {
				min = pDraws[j];
				indeks = j;
			}
			else if (!res) {
				if (strCompare(min->firstName, pDraws[j]->firstName) > 0) {
					min = pDraws[j];
					indeks = j;
				}
			}
		}
		pDraws[indeks] = pDraws[i];
		pDraws[i] = min;
	}
}

int strCompare(char* s1, char* s2) {
	char* copyS1 = (char*)calloc(strlen(s1) + 1, sizeof(char));
	char* copyS2 = (char*)calloc(strlen(s2) + 1, sizeof(char));
	memcpy(copyS1, s1, strlen(s1) + 1);
	memcpy(copyS2, s2, strlen(s2) + 1);

	_strlwr(copyS1);
	_strlwr(copyS2);

	int res = strcmp(copyS1, copyS2);

	//free(copyS1);
	//free(copyS2);

	return res;
}

