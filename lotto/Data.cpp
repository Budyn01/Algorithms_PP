#include "stdafx.h"


int AllocAddMemDraw(Bet** pTab, int size);
int AllocAddMem(LottoPlayer*** pTab, int size);

int ReadData(LottoPlayer*** pAllDraws, const char* fileName)
{
	FILE *file = fopen(fileName, "r");
	if (!file) {
		printf("ERROR ReadData(): Input file read error.\n");
		return 0;
	}

	int playerNumber = 0;
	int maxPlayer = 0;

	LottoPlayer **copy = *pAllDraws;

	while (!feof(file)) {
		char c;
		if ((c = getc(file)) != '*') {
			ungetc(c, file);
			if (playerNumber == maxPlayer) {
				maxPlayer += AllocAddMem(&copy, playerNumber);
				if (playerNumber == maxPlayer) break;
			}

			LottoPlayer *player = copy[playerNumber] = (LottoPlayer*)calloc(1, sizeof(LottoPlayer));
			if (!player) {
				printf("ERROR: Allocation\n");
				break;
			}

			char sex;
			int day, month, year;
			fscanf(file, "%s %s %c %8c%3c %2c%2c%10c%14c %d/%d/%d %10c",
				player->lastName,
				player->firstName,
				&sex,
				player->bank.swift.code,
				player->bank.swift.swiftBank,
				player->bank.iban.country,
				player->bank.iban.control,
				player->bank.iban.bank,
				player->bank.iban.user,
				&day, &month, &year,
				player->pesel);

			if (!SetSex(player, sex) || !SetDate(player, day, month, year)) {
				printf("ERROR: Can not set sex or date.\n");
				break;
			}
			fscanf(file, "\n");

#if DEBUG
			printf("\nWczytano Zawodnika: %s %s \n", &player->firstName, &player->lastName);
#endif 
			int drawRead = 0;
			Bet *betTab = NULL;

			while ((c = getc(file)) != '*' && !feof(file)) {
				ungetc(c, file);
				if (drawRead == player->betNumber) {
					player->betNumber += AllocAddMemDraw(&player->bets, drawRead);
					if (drawRead == player->betNumber) break;
				}

				betTab = player->bets;

				int* b2 = betTab[drawRead].bet2 = (int*)calloc(2, sizeof(int));
				int* b5 = betTab[drawRead].bet5 = (int*)calloc(5, sizeof(int));

				if (!b2 || !b5) {
					printf("ERROR: bets allocation \n");
					break;
				}

				for (int k = 0; k < 5; k++)	fscanf(file, "%d", &b5[k]);
				fscanf(file, "%d %d", b2, b2 + 1);

#if DEBUG
				printf("Wczytano Zaklad: ");
				for (int i = 0; i < 5; i++)
					printf(" %2d ", b5[i]);
				printf(" | ");
				printf("%2d %2d", b2[0], b2[1]);
				printf("\n");
#endif
				drawRead++;
				fscanf(file, "\n");
			}
			player->currentBet = drawRead;
			playerNumber++;
		}
	}
	fclose(file);
	*pAllDraws = copy;

	return playerNumber;
}

int AllocAddMem(LottoPlayer*** pTab, int size) {
	LottoPlayer **copy = *pTab;
	*pTab = (LottoPlayer**)realloc(*pTab, size * sizeof(*(*pTab)) + 5 * sizeof(*(*pTab)));
	if (!*pTab)	{
		printf("Reallocation memory error.\n");
		*pTab = copy;
		return 0;
	}
	memset(*pTab + size, 0, 5 * sizeof(*(*pTab)));
	return 5;
}

int AllocAddMemDraw(Bet** pTab, int size) {
	Bet *copy = *pTab;
	*pTab = (Bet*)realloc(*pTab, size * sizeof(*(*pTab)) + 3 * sizeof(*(*pTab)));

	if (!*pTab)	{
		printf("Reallocation memory error.\n");
		*pTab = copy;
		return 0;
	}

	memset(*pTab + size, 0, 3 * sizeof(*(*pTab)));

	return 3;
}

void FreeMem(LottoPlayer** pTab, int nDrawsNo)
{
	for (int i = 0; i<nDrawsNo; i++)
	{
		LottoPlayer* player1 = pTab[i];
		Bet* p2 = player1->bets;
		for (int j = 0; j<player1->currentBet; j++, p2++)
		{
			free(p2->bet2);
			free(p2->bet5);
		}
		free(player1->date);
		free(player1);
	}
	free(pTab);
}

int SetSex(LottoPlayer* player, char c)
{
	switch (toupper(c)) {
	case 'F': player->sex = FEMALE; return 1;
	case 'M': player->sex = MALE; return 1;
	default: return 0;
	}
}

int SetDate(LottoPlayer* player, int day, int month, int year)
{
	if (!(day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900))	{
		printf("ERROR: Date \n");
		return 0;
	}

	struct tm time = {0};
	time.tm_mday = day;
	time.tm_mon = month - 1;
	time.tm_year = year - 1900;

	if (mktime(&time) == -1) {
		printf("ERROR time\n");
		return 0;
	}

	Date *date = player->date = (Date*)calloc(1, sizeof(Date));
	if (!date) {
		printf("ERROR: date allocation\n");
		return 0;
	}

	date->day = day;
	date->month = Month(month);
	date->year = year;
	date->dayName = Day(time.tm_wday);
	
	return 1;
}