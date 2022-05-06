#pragma once
#include "header.h"

#define LOGICAL_INITH 1
#define PHIYSICAL_INITH 0

Musician*** createMusicianCollection(Musician** MusiciansGroup, int number_of_musicians, int numOfInstruments, int** musicianCollectionArraySizes);
int* make_arr_instrument_players_counter(int number_of_instruments, int size);
Musician*** make_empty_Musician_Collection_arr(int number_of_instruments);
void shrinks_unnecessary_space_in_arrs(Musician*** MusicianCollection, int* instrument_players_counter, int number_of_instruments);
void freeMusicianCollaction(Musician*** MusiciansCollection, int number_of_instrumnets);