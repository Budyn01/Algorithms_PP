#include "stdafx.h"

int  AllocAddMem(LottoPlayer*** tab, int size);
int	 AllocAddMemDraw(Bet** tab, int size);
int  SetSex(LottoPlayer* player, char c);
int  SetDate(LottoPlayer* player, int day, int month, int year);


//===========================================================================
int  ReadData(LottoPlayer*** allBets, const char* fileName) {

	FILE* file = NULL;
	if ((file = fopen(fileName, "r")) == NULL) {
		printf("Error ReadData()\n");
		return 0;
	}

	int playerNumber = 0;
	int maxPlayer = 0;

	LottoPlayer** pDraws = *allBets;

	while (!feof(file))
	{
		char c;
		if ((c = getc(file)) != '*')
			ungetc(c, file);

		if (playerNumber == maxPlayer) {
			maxPlayer += AllocAddMem(&pDraws, playerNumber);
			if (playerNumber == maxPlayer) break;
		}

		LottoPlayer* player = pDraws[playerNumber] = (LottoPlayer*)calloc(1, sizeof(LottoPlayer));
		if (!player) {
			printf("Error. ReadData().\n");
			break;
		}

		char sex;
		int day, month, year;
		Swift* swift = &(player->bank.swift);
		IBAN* iban = &(player->bank.iban);
		//!!!!!!!!
		fscanf(file, "%s %s %c %8c%3c %2c%2c%10c%14c %d/%d/%d %10c",
			player->lastName,
			player->firstName,
			&sex,
			swift->code, swift->bank,
			iban->country, iban->control, iban->bank, iban->user,
			&day, &month, &year,
			player->pesel);																																								// wczytanymi danymi

		if (!SetSex(player, sex) || !SetDate(player, day, month, year)) {
			printf("Erro: ReadData error.\n");
			break;
		}

		fscanf(file, "\n");

#ifdef _DEBUG_PRINT_
		printf("PLAYER READ: %s %s \n", &player->firstName, &player->lastName);
#endif // _DEBUG_PRINT_

		int DrawRead = 0;
		Bet* pDrawTab = NULL;

		while ((c = getc(file)) != '*' && !feof(file)) {
			ungetc(c, file);

			if (DrawRead == player->numberBets) {
				player->numberBets += AllocAddMemDraw(&player->bets, DrawRead);
				if (DrawRead == player->numberBets) break;
			}

			pDrawTab = player->bets;

			int* p2 = pDrawTab[DrawRead].bet2 = (int*)calloc(SIZE2, sizeof(int));
			int* p5 = pDrawTab[DrawRead].bet5 = (int*)calloc(SIZE5, sizeof(int));

			if (!p2 || !p5) {
				printf("Error. Can not allocale.");
				break;
			}

			for (int k = 0; k < SIZE5; k++)
				fscanf(file, "%d", p5 + k);
			fscanf(file, "%d %d", p2, p2 + 1);

#ifdef _DEBUG_PRINT_
			printf("BET READ: ");
			for (int i = 0; i < SIZE5; i++)
				printf(" %2d ", *p5++);
			printf(" | ");
			for (int i = 0; i < SIZE2; i++)
				printf("%2d ", *p2++);
			printf("\n");
#endif // _DEBUG_PRINT_

			DrawRead++;
			fscanf(file, "\n");
		}
		player->currentBets = DrawRead;
		playerNumber++;
	}

	fclose(file);
	*allBets = pDraws;

	return playerNumber;		//ilosc_wczytanych_graczy;
}


int  AllocAddMem(LottoPlayer*** pTab, int nCurrSize)
{
	LottoPlayer** copy = *pTab;
	*pTab = (LottoPlayer**)realloc(*pTab, nCurrSize * sizeof(*(*pTab)) + RESIZE5 * sizeof(*(*pTab)));

	if (!*pTab) {
		printf("Reallocation memory error. AllocAddMem(). \n");
		*pTab = copy;
		return 0;
	}

	memset(*pTab + nCurrSize, 0, RESIZE5 * sizeof(*(*pTab)));
	return RESIZE5;
}

int AllocAddMemDraw(Bet** bets, int size) {
	Bet* copy = *bets;
	*bets = (Bet*)realloc(*bets, size * sizeof(*(*bets)) + RESIZE3 * sizeof(*(*bets)));

	if (!*bets) {
		printf("\nReallocation memory error. AllocAddMemDraw(). \n");
		*bets = copy;
		return 0;
	}

	memset(*bets + size, 0, RESIZE3 * sizeof(*(*bets)));

	return RESIZE3;
}

void FreeMem(LottoPlayer** tab, int numberBets) {
	for (int i = 0; i < numberBets; i++) {
		LottoPlayer* p1 = tab[i];
		Bet* p2 = p1->bets;
		for (int j = 0; j < p1->currentBets; j++, p2++) {
			free(p2->bet2);
			free(p2->bet5);
		}
		free(p1->bets);
		free(p1);
	}
	free(tab);
}

int  SetSex(LottoPlayer* player, char c) {
	switch (c) {
	case 'f':
	case 'F': player->sex = FEMALE; return 1;
	case 'm':
	case 'M': player->sex = MALE; return 1;
	default: return 0;
	}
}

int  SetDate(LottoPlayer* p, int d, int m, int y) {
	if (!(d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 1900)) {
		printf("Date out of allowed reach. SetDate() error. ;(\n");
		return 0;
	}

	struct tm time_r = { 0 };
	if (!&time_r) {
		printf("Memory Allocation Error. SetSate().");
		return 0;
	}

	time_r.tm_mday = d;
	time_r.tm_mon = m - 1;
	time_r.tm_year = y - 1900;

	if (mktime(&time_r) == -1) {
		printf("Data computing error :(. Setdate().");
		return 0;
	}

	Date p1 = p->date;

	p1.day = d;
	p1.year = y;

	switch (m) {
	case 1: p1.month = JAN; break;
	case 2: p1.month = FEB; break;
	case 3: p1.month = MAR; break;
	case 4: p1.month = APR; break;
	case 5: p1.month = MAY; break;
	case 6: p1.month = JUN; break;
	case 7: p1.month = JUL; break;
	case 8: p1.month = AUG; break;
	case 9: p1.month = SEP; break;
	case 10: p1.month = OCT; break;
	case 11: p1.month = NOV; break;
	case 12: p1.month = DEC; break;
	}

	switch (time_r.tm_wday) {
	case 0: p1.dayName = SUNDAY;  break;
	case 1: p1.dayName = MONDAY;  break;
	case 2: p1.dayName = TUESDAY;  break;
	case 3: p1.dayName = WEDNESDAY; break;
	case 4: p1.dayName = THURSDAY; break;
	case 5: p1.dayName = FRIDAY;   break;
	case 6: p1.dayName = SATURDAY; break;
	}
	p->date = p1;
	return 1;
}