#include "stdafx.h"

void PrintResults(FILE* fileOut, int* bet5, int* bet2, LottoPlayer** bets, int betsNumbers) {
	for (int i = 0; i < betsNumbers; i++) {
		LottoPlayer* player = bets[i];
		fprintf(fileOut, "**%s %s\t", player->lastName, player->firstName);
		PrintSex(fileOut, player);
		PrintDate(fileOut, player);

		IBAN* iban = &(player->bank.iban);
		Swift* swift = &(player->bank.swift);

		fprintf(fileOut, "Swift:%.8s%.3s\tIban:%.2s%.4s%.10s%.14s  ",
			swift->code,
			swift->bank,
			iban->country,
			iban->control,
			iban->bank,
			iban->user);
		fprintf(fileOut, "\n----------------  BETS  ----------------\n");
		PrintBets(fileOut, player);
	}

	fprintf(fileOut, "\n====================================\n||      S T A T I S T I C S       ||\n====================================\n\n\n");

	int* p5 = bet5;
	for (int i = 0; i < RESULT5; i++, p5++) {
		fprintf(fileOut, "%2d:%2d  ", i + 1, *p5);
		if (!((i + 1) % 10)) fprintf(fileOut, "\n");
	}

	fprintf(fileOut, "\n");

	int* p2 = bet2;
	for (int i = 0; i < RESULT2; i++, p2++) {
		fprintf(fileOut, "%2d:%2d  ", i + 1, *p2);
	}

	fprintf(fileOut, "\n\nDziekujemy za udzial w loterii, gratulujemy wygranych. :)");

	fclose(fileOut);
}

void PrintSex(FILE* fileOut, LottoPlayer* player) {
	switch (player->sex) {
	case FEMALE: fprintf(fileOut, "*Panienka*    "); break;
	case MALE: fprintf(fileOut, "*Facet*    ");
	}
}

void PrintDate(FILE* fileOut, LottoPlayer* player) {
	switch (player->date.dayName) {
	case SUNDAY: fprintf(fileOut, "Sun, "); break;
	case MONDAY: fprintf(fileOut, "Mon, "); break;
	case TUESDAY: fprintf(fileOut, "Tue, "); break;
	case WEDNESDAY: fprintf(fileOut, "Wed, "); break;
	case THURSDAY: fprintf(fileOut, "Thr, "); break;
	case FRIDAY: fprintf(fileOut, "Fri, "); break;
	case SATURDAY: fprintf(fileOut, "Sat, ");
	}

	fprintf(fileOut, "%d/", player->date.day);

	switch (player->date.month) {
	case JAN: fprintf(fileOut, "Jan/"); break;
	case FEB: fprintf(fileOut, "Feb/"); break;
	case MAR: fprintf(fileOut, "Mar/"); break;
	case APR: fprintf(fileOut, "Apr/"); break;
	case MAY: fprintf(fileOut, "May/"); break;
	case JUN: fprintf(fileOut, "Jun/"); break;
	case JUL: fprintf(fileOut, "Jul/"); break;
	case AUG: fprintf(fileOut, "Aug/"); break;
	case SEP: fprintf(fileOut, "Sep/"); break;
	case OCT: fprintf(fileOut, "Oct/"); break;
	case NOV: fprintf(fileOut, "Nov/"); break;
	case DEC: fprintf(fileOut, "Dec/");
	}

	fprintf(fileOut, "%d\n", player->date.year);
}

void PrintBets(FILE* fileOut, LottoPlayer* player) {
	Bet* bets = player->bets;
	for (int i = 0; i < player->currentBets; i++, bets++) {
		int* p5 = bets->bet5;
		for (int j = 0; j < SIZE5; j++)
			fprintf(fileOut, " %2d ", *p5++);

		fprintf(fileOut, "  |  ");

		int* p2 = bets->bet2;
		for (int j = 0; j < SIZE2; j++)
			fprintf(fileOut, " %2d ", *p2);

		fprintf(fileOut, "\n");
	}
	fprintf(fileOut, "\n");
}