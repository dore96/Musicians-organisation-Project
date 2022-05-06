#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <crtdbg.h>
#define MAX_LINE_LEN 150
#define END_OF_LINE '\n'
#define NONE 0
#define MULTY_BY_TWO(X) ((X)*=(2))
typedef struct treeNode {
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;
typedef struct tree {
	TreeNode* root;
} InstrumentTree;
typedef struct MusicianPriceInstrument
{
	unsigned short insID;			 // מספר מזהה של כלי נגינה 
	float price;					 //	מחיר שדורש הנגן עבור נגינה בכלי זה
	struct MusicianPriceInstrument* next;	 //	next item in linked list.
} MusicianPriceInstrument;
typedef struct MPIList
{
	MusicianPriceInstrument* head;	 //	head item in linked list.
	MusicianPriceInstrument* tail;	 //	tail item in linked list.
} MPIList;
typedef struct Musician
{
	char** name; // מערך של השמות המרכיבים את שמו המלא
	int number_of_names;
	bool is_playing;
	float* prices;
	MPIList instruments; // MusicianPriceInstrument כלי הנגינה ברשימה מקושרת של 
} Musician;
typedef struct Date
{
	int day, month, year;
	float hour;
} Date;
typedef struct ConcertInstrument
{
	int num; // כמה מאותו הכלי
	int inst; // מספר מזהה של כלי הנגינה
	char importance; // (1 / 0 )האם לכלי נגינה זה יש תקציב עבור נגנים יקרים
	char instrument_name[MAX_LINE_LEN];
	struct ConcertInstrument* next;
} ConcertInstrument;
typedef struct CIList
{
	ConcertInstrument* head;
	ConcertInstrument* tail;
}CIList;
typedef struct Concert
{
	Date date_of_concert; // ההופעה קיום תאריך
	char* name;//שם ההופעה
	CIList instruments;// כלי הנגינה ברשימה מקושרת של ConcertInstruments
} Concert;
