#pragma once

#define SIZE 20
#define PESELSIZE 10
#define SWIFTCODE_LENGTH 8
#define SWIFTBANK_LENGTH 3
#define IBAN_CONTROL 2
#define IBAN_COUNTRY 2
#define IBAN_BANK 10
#define IBAN_USER 14


#define DEBUG true

typedef enum {
	MALE,
	FEMALE
} Sex;

typedef enum  {
	SUNDAY = 1,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THRUSDAY,
	FRIDAY,
	SATURDAY
} Day;

typedef enum {
	JAN = 1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC
} Month;

typedef struct {
	int *bet2;
	int *bet5;
} Bet;

typedef struct  {
	char code[SWIFTCODE_LENGTH];
	char swiftBank[SWIFTBANK_LENGTH];
} Swift;

typedef struct  {
	char country[IBAN_COUNTRY];
	char control[IBAN_CONTROL];
	char bank[IBAN_BANK];
	char user[IBAN_USER];
} IBAN;

typedef struct {
	IBAN iban;
	Swift swift;
} Bank;

typedef struct  {
	int day;
	int dayName;
	int month;
	int year;
} Date;

typedef struct {
	char firstName[SIZE];
	char lastName[SIZE];
	Sex sex;
	Bank bank;
	char pesel[PESELSIZE];
	Date *date;
	Bet *bets;
	int betNumber;
	int currentBet;
} LottoPlayer;