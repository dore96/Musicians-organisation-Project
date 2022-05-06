#pragma once
#include "header.h"
//define that will be used"
#define DEFAULT_CHAR '0'
#define IMPORTANT '1'
#define GET_TIME(x,y) (x) + ((y)/60)
//functions to create the concert
void bookAConcert(Musician*** MusiciansCollection, int* musicianCollectionArraySizes, InstrumentTree musicInstrumentsTree);
Concert getConcertDetails(char firstLetter, InstrumentTree musicInstrumentsTree);
char* getName(char firstChar);
void createEmptyInstrumentList(CIList* lst);
ConcertInstrument* createConcertInstrumentListNode(char* instrument, int amount, char importance, ConcertInstrument* next, InstrumentTree musicInstrumentsTree);
void insertInstrumentData(CIList* lst, char* instrument, int amount, char importance, InstrumentTree musicInstrumentsTree);
void insertInstrumentNodeToEnd(CIList* lst, ConcertInstrument* newTail);
void sort_musician_arrs(Musician*** MusiciansCollection, int* musicianCollectionArraySizes, Concert myConcert);
void pointerSort(Musician** arr, int size, char importance);
bool build_concert(Musician*** MusiciansCollection, int* musicianCollectionArraySizes, Concert myConcert, Musician*** musicians_for_concert);
void print_concert(Concert myConcert, Musician** musicians_for_concert);
void resetPlayers(Musician** players, int size);
int compare1(const void* a, const void* b);
int compare2(const void* a, const void* b);
void freeConcertInstrumentList(CIList lst);