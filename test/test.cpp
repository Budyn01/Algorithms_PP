// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <iostream>

using namespace std;
#define FILE_NAME "lotto0.txt"

//int isNewPlayer(FILE *file) {
//	char star = getc(file);
//	if (star == '*') {
//		cout << "New Player\n";
//		return 1;
//	}
//	ungetc(star, file);
//	return 0;
//}
//
//char* getString(FILE *file) {
//	char* str = (char*)calloc(30, sizeof(char));
//	fscanf(file, "%s", str);
//	if (str[0] == '*') return NULL;
//	return str;
//}
//
//int* readBet(FILE *file) {
//	int *tab = (int*) calloc(7, sizeof(int));
//	fscanf(file, "%d %d %d %d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5], &tab[6]);
//	return tab;
//}
//
//void ReadFileTrololo() {
//
//	FILE* file = NULL;
//
//	if ((file = fopen(FILE_NAME, "r")) == NULL) {
//		printf("ERROR: can't read file!\n");
//		return;
//	}
//
//	while (true) {
//		isNewPlayer(file);
//		cout << "Last Name: " << getString(file) << endl;
//		cout << "First Name: " << getString(file) << endl;
//		cout << "Sex: " << getString(file) << endl;
//		cout << "SWIFT: " << getString(file) << endl;
//		cout << "Account Number: " << getString(file) << endl;
//		cout << "Date: " << getString(file) << endl;
//		cout << "Pesel: " << getString(file) << endl;
//
//		int *bet = readBet(file);
//		while (!isNewPlayer(file)) {
//			if (feof(file) != 0) {
//				break;
//			}
//			cout << "Bet: ";
//			for (int i = 0; i < 7; i++)	{
//				cout << bet[i] << ",";
//			}
//			cout << "\b \n";
//			bet = readBet(file);
//		}
//
//		if (feof(file) != 0) {
//			break; 
//		}
//	}
//
//
//
//	fclose(file);
//
//}

short licznik = 0;

class moja {
public:
	void wypisz(void);
	void ustaw(int a) {
		moja::licznik = a;
	}
	void wypisz(int a) {
		licznik = a;
		cout << licznik;
	}
	void modyfikuj(int c) {
		f = c;
	}
private: 
	int licznik;
	int f;
};
void moja::wypisz(void) {
	const long licznik = 10;
	cout << licznik;
	cout << moja::licznik;
	cout << ::licznik;
}

int main() {
	moja obiekt;
	obiekt.wypisz(2);
	obiekt.ustaw(5);
	obiekt.wypisz(3);
	obiekt.wypisz();
	system("PAUSE");
	return 0;
}

class Aparat {
private:
	char* producent;
	char* typ;
	int numer_seryjny;
	//Reszta danych
public:
	char* AE_Title;
	void ustawProducent(char* prod) {
		producent = prod;
	}
	char* pobierzProducent() {
		return producent;
	}
	//Itd dla reszty
};

int main() {
	Aparat aparat;
	return 0;
}
