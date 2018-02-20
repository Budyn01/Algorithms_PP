#pragma once

int  ReadData(LottoPlayer*** allBets, const char* fileName);
void FreeMem(LottoPlayer** tab, int numberBets);