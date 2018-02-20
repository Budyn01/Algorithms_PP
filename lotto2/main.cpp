#include "stdafx.h"

void HeapCheck();
void CalcStat(int* bet5, int* bet2, LottoPlayer** bets, int numberBets);
void Sort(LottoPlayer** bets, int numberBets);
int strCompare(char* string1, char* string2);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: JackpotLottery.exe <input_file> <output_file>  \n");
		return 1;
	}

	LottoPlayer** playersTab = NULL;

	int currentPlayerNumber = 0;

	if ((currentPlayerNumber = ReadData(&playersTab, argv[1])) == 0) {
		printf("Data read error. No information readed.\n");
		return 2;
	}

	int* resultBet5 = (int*)calloc(RESULT5, sizeof(int));
	int* resultBet2 = (int*)calloc(RESULT2, sizeof(int));

	if (!resultBet2 || !resultBet5) {
		printf("Memory Allocation Error.\n");
		return 0;
	}
	CalcStat(resultBet5, resultBet2, playersTab, currentPlayerNumber);

	Sort(playersTab, currentPlayerNumber);

	FILE* fileOut = fopen(argv[2], "w");
	if (!fileOut) {
		printf("Can not open \"%s\" file to write. Error.\n", argv[2]);
		return 0;
	}
	PrintResults(fileOut, resultBet5, resultBet2, playersTab, currentPlayerNumber);

	FreeMem(playersTab, currentPlayerNumber);
	playersTab = NULL;
//freee!!!!!!!!!!!!!
	HeapCheck();

	system("PAUSE");
	return 0;
}

void HeapCheck()
{
	int  heapstatus;
	// Check heap status  
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

void CalcStat(int* bet5, int* bet2, LottoPlayer** bets, int numberBets)
{
	int* p2 = bet2;
	int* p5 = bet5;

	for (int i = 0; i < numberBets; i++) {
		LottoPlayer* pPlayer = bets[i];

		for (int j = 0; j < pPlayer->currentBets; j++) {
			Bet pDraw = pPlayer->bets[j];
			int* pDraw5 = pDraw.bet5;
			for (int k = 0; k < SIZE5; k++, pDraw5++) {
				if (*pDraw5 > 0 && *pDraw5 <= RESULT5)
					p5[*pDraw5 - 1]++;
				else
					printf("Picked value: %d is out of allowed reach. CalcStat().", *pDraw5);
			}

			int* pDraw2 = pDraw.bet2;
			for (int k = 0; k < SIZE2; k++, pDraw2++) {
				if (*pDraw2 > 0 && *pDraw2 <= RESULT2)
					p2[*pDraw2 - 1]++;
				else
					printf("Picked value: %d is out of allowed reach. CalcStat().", *pDraw2);
			}
		}
	}
}

void Sort(LottoPlayer** bets, int numberBets) {
	for (int i = 0; i < numberBets - 1; i++) {
		int index = i;
		LottoPlayer* min = bets[i];

		int res;

		for (int j = i + 1; j < numberBets; j++) {
			if ((res = strCompare(min->lastName, bets[j]->lastName)) > 0) {
				min = bets[j];
				index = j;
			}
			else if (!res) {
				if (strCompare(min->firstName, bets[j]->firstName) > 0) {
					min = bets[j];
					index = j;
				}
			}
		}
		bets[index] = bets[i];
		bets[i] = min;
	}
}

int strCompare(char* string1, char* string2) {
	char* copyS1 = (char*)calloc(strlen(string1) + 1, sizeof(char));
	char* copyS2 = (char*)calloc(strlen(string2) + 1, sizeof(char));
	memcpy(copyS1, string1, strlen(string1) + 1);
	memcpy(copyS2, string2, strlen(string2) + 1);

	_strlwr(copyS1);
	_strlwr(copyS2);

	int res = strcmp(copyS1, copyS2);

	free(copyS1);
	free(copyS2);

	return res;
}