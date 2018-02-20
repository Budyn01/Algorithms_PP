#pragma once

#define SIZE 20	
#define PESELSIZE 10
#define IBAN_CONTROL 2
#define IBAN_COUNTRY 2
#define IBAN_BANK 10
#define IBAN_USER 14
#define SWIFTCODE_LENGTH 8
#define SWIFTBANK_LENGTH 3

#define SIZE5 5
#define SIZE2 2

#define RESIZE3 3
#define RESIZE5 5

#define RESULT5 50
#define RESULT2 10

#define _DEBUG_PRINT_

typedef enum { FEMALE, MALE } Sex;
typedef enum { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY } Day;
typedef enum { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC } Month;

typedef struct {
	int* bet2;
	int* bet5;
} Bet;

typedef struct {
	char code[SWIFTCODE_LENGTH];
	char bank[SWIFTBANK_LENGTH];
} Swift;

typedef struct {
	char country[IBAN_COUNTRY];
	char control[IBAN_CONTROL];
	char bank[IBAN_BANK];
	char user[IBAN_USER];
} IBAN;

typedef struct {
	IBAN iban;
	Swift swift;
} Bank;

typedef struct {
	int dayName;
	int day;
	int month;
	int year;
} Date;

typedef struct {
	char firstName[SIZE+1];
	char lastName[SIZE+1];
	Sex sex;
	Bank bank;
	char pesel[PESELSIZE];
	Date date;
	Bet* bets;
	int numberBets;
	int currentBets;
} LottoPlayer;