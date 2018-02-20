#include "stdafx.h"

void PrintSex(FILE *file, LottoPlayer *player);
void PrintDate(FILE* file, LottoPlayer* player);
void PrintBets(FILE* file, LottoPlayer* player);

void PrintResults(FILE *file, int* bet5, int *bet2, LottoPlayer **pDraws, int drawsNumber) {
	for (int i = 0; i < drawsNumber; i++) {
		LottoPlayer *player = pDraws[i];
		fprintf(file, "**%s %s\t", player->lastName, player->firstName);
		PrintSex(file, player);
		PrintDate(file, player);

		IBAN *iban = &(player->bank.iban);
		Swift *swift = &(player->bank.swift);

		fprintf(file, "Swift:%.8s%.3s\tIban:%.2s%.4s%.10s%.14s  ",
			swift->code,
			swift->swiftBank,
			iban->country,
			iban->control,
			iban->bank,
			iban->user);
		fprintf(file, "\n----------------  BETS  ----------------\n");
		PrintBets(file, player);
		fprintf(file, "\n====================================\n||      S T A T I S T I C S       ||\n====================================\n\n\n");

		int *b5 = bet5;
		for (int i = 0; i < 5; i++, b5++) {
			fprintf(file, "%2d:%2d  ", i + 1, *b5);
			if (!((i + 1) % 10)) fprintf(file, "\n");
		}

		fprintf(file, "\n");

		int* b2 = bet2;
		for (int i = 0; i < 2; i++, b2++) {
			fprintf(file, "%2d:%2d  ", i + 1, *b2);
		}

		fprintf(file, "\n\nWygrana wlolo xD\n");

		fclose(file);
	}
}

void PrintSex(FILE *file, LottoPlayer *player) {
	switch (player->sex) {
	case FEMALE: fprintf(file, "*Panienka*    "); break;
	case MALE: fprintf(file, "*Facet*    ");
	}
}

void PrintDate(FILE* file, LottoPlayer* player) {
	switch (player->date->dayName) {
	case 1: fprintf(file, "Sun, "); break;
	case 2: fprintf(file, "Mon, "); break;
	case 3: fprintf(file, "Tue, "); break;
	case 4: fprintf(file, "Wed, "); break;
	case 5: fprintf(file, "Thr, "); break;
	case 6: fprintf(file, "Fri, "); break;
	case 7: fprintf(file, "Sat, ");
	}

	fprintf(file, "%d/", player->date->day);

	switch (player->date->month) {
	case 1: fprintf(file, "Jan/"); break;
	case 2: fprintf(file, "Feb/"); break;
	case 3: fprintf(file, "Mar/"); break;
	case 4: fprintf(file, "Apr/"); break;
	case 5: fprintf(file, "May/"); break;
	case 6: fprintf(file, "Jun/"); break;
	case 7: fprintf(file, "Jul/"); break;
	case 8: fprintf(file, "Aug/"); break;
	case 9: fprintf(file, "Sep/"); break;
	case 10: fprintf(file, "Oct/"); break;
	case 11: fprintf(file, "Nov/"); break;
	case 12: fprintf(file, "Dec/");
	}

	fprintf(file, "%d\n", player->date->year);
}

void PrintBets(FILE* file, LottoPlayer* player) {
	Bet* bet = player->bets;
	for (int i = 0; i < player->currentBet; i++, bet++)
	{
		int* b5 = bet->bet5;
		for (int j = 0; j < 5; j++)
			fprintf(file, " %2d ", *b5++);

		fprintf(file, "  |  ");

		int* b2 = bet->bet2;
		for (int j = 0; j < 2; j++)
			fprintf(file, " %2d ", *b2);

		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}