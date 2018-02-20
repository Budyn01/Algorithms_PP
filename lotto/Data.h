#pragma once

int  ReadData(LottoPlayer*** pAllDraws, const char* fileName);
int  AllocAddMem(LottoPlayer*** playerTab, int size);
void FreeMem(LottoPlayer** playerTab, int drawsNumber);
int  SetSex(LottoPlayer* player, char c);
int  SetDate(LottoPlayer* player, int day, int month, int year);