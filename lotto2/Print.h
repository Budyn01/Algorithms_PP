#pragma once
#include "stdafx.h"

void PrintResults(FILE* file, int* bet5, int* bet2, LottoPlayer** allBets, int nDrawsNo);
void PrintSex(FILE* file, LottoPlayer* player);
void PrintDate(FILE* file, LottoPlayer* player);
void PrintBets(FILE* file, LottoPlayer* player);

