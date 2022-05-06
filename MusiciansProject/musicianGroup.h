#pragma once
#include "header.h"
//defines that will be used
#define DELIMETERS " ,.;:?!-\t'()[]{}<>~_"
#define NOT_PLAYING -1
#define FIRST_IND 0	
#define NONE 0

//function relating to the creation of musician group.
void make_empty_MusicianPriceInstrument_list(MPIList* lst); //the function purpose is to make an empty list.
void insert_data_to_end_of_list(MPIList* lst, char* instrument, InstrumentTree musicInstrumentsTree);   //the function purpose is to insert a new data to the lineked list.
MusicianPriceInstrument* create_new_list_node(char* instrument, MusicianPriceInstrument* next, InstrumentTree musicInstrumentsTree); //the function purpose is to create a new node with data, returns a node pointer.
void insert_node_to_end_of_list(MPIList* lst, MusicianPriceInstrument* newTail);    //the function purpose is to insert data to the end of lineked list.
void insert_name_word(char* name_word, char*** names_array, int* logical_size, int physical_size);
Musician** get_musicians(InstrumentTree musicInstrumentsTree, FILE* file, int* number_of_musicians, int numberOfInstruments);
Musician* get_one_musician(char* line, InstrumentTree musicInstrumentsTree, int numberOfInstruments);
float* createPricesArr(int size);
void update_musician(Musician* musician, int number_of_names, char* tok);
void initiate_musician(Musician* musician, int numberOfInstruments);
void freeMusicianGroup(Musician** musician_group, int number_of_musicians);
void freeMPIList(MPIList lst);