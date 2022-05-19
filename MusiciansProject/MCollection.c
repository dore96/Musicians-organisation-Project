#include "musicianCollection.h"
#include "utility.h"
Musician*** createMusicianCollection(Musician** MusiciansGroup, int number_of_musicians, int numOfInstruments, int** musicianCollectionArraySizes)
{//function purpose is to create musician collection and returns it.
	MusicianPriceInstrument* currentInstrument;         //pointer to instrument linked list.
	int i, intsrument_id;								//instrument id variable is int that represents the corrent instrument unique number. 
	int* physical_size = make_arr_instrument_players_counter(numOfInstruments, LOGICAL_INITH); //makes an arr of instruments physical size.
	int* logical_size = make_arr_instrument_players_counter(numOfInstruments, PHIYSICAL_INITH);//makes an arr of instruments logical size.
	Musician*** MusicianCollection = make_empty_Musician_Collection_arr(numOfInstruments);
	for (i = 0; i < number_of_musicians; i++)		//for every musician.
	{
		currentInstrument = MusiciansGroup[i]->instruments.head;	//update currentInstrument to be the head instrument in linked list.
		while (currentInstrument != NULL)							//while there are no more instruments to musician.
		{
			intsrument_id = currentInstrument->insID;				//update intsrument_id to be the instrument id.
			if (physical_size[intsrument_id] == logical_size[intsrument_id]) //if there is no space to musician pointer in instrument specifice arr - double the place. 
				make_double_space(&(physical_size[intsrument_id]), &MusicianCollection[intsrument_id]);
			MusicianCollection[intsrument_id][(logical_size[intsrument_id])] = MusiciansGroup[i]; //place musician pointer in correct spot.
			logical_size[intsrument_id]++;														  //update logical size.
			currentInstrument = currentInstrument->next;										  //go to next instrument.
		}
	}
	shrinks_unnecessary_space_in_arrs(MusicianCollection, logical_size, numOfInstruments);		//shrink MusicianCollection arrs by logical_size arr.
	free(physical_size);
	*musicianCollectionArraySizes = logical_size;												//update in calling func the value of musicianCollectionArraySizes.
	return MusicianCollection;
}
int* make_arr_instrument_players_counter(int number_of_instruments, int size)
{//function purpose is to create instrument size arr of int (logical\phisical).
	int i;
	int* instrument_players_counter = (int*)malloc(number_of_instruments * sizeof(int)); //make arr size by number of instrumnets and check allocation.
	checkAllocation(instrument_players_counter);
	for (i = 0; i < number_of_instruments; i++)   //for every instrumnet - initiate size.
		instrument_players_counter[i] = size;
	return instrument_players_counter;			  //returns the arr.
}
Musician*** make_empty_Musician_Collection_arr(int number_of_instruments)
{//function purpose is to create empty MusicianCollection and returns it.
	int i;
	Musician*** MusicianCollection = (Musician***)malloc(number_of_instruments * sizeof(Musician**));//make dynamic space size by number of instrumnets and check allocation.
	checkAllocation(MusicianCollection);
	for (i = 0; i < number_of_instruments; i++)   //for every insturment.
	{
		MusicianCollection[i] = (Musician**)malloc(sizeof(Musician*));  //make dynamic space for at least on player pointer and check allocation.
		checkAllocation(MusicianCollection[i]);
	}
	return MusicianCollection;
}
void shrinks_unnecessary_space_in_arrs(Musician*** MusicianCollection, int* instrument_players_counter, int number_of_instruments)
{//function purpose is to shrink space or arrs in MusicianCollection.
	int i;
	for (i = NONE; i < number_of_instruments; i++)  //for every array in MusicianCollection.
	{//realloc by the logical size of the instrument pointers to players.
		*(MusicianCollection + i) = realloc(*(MusicianCollection + i), (instrument_players_counter[i]) * sizeof(Musician*));
		checkAllocation(*(MusicianCollection + i));
	}
}
void freeMusicianCollaction(Musician*** MusiciansCollection, int number_of_instrumnets)
{//frees all the the memory saved for arrays of players in musician collection
	int i;
	for (i = 0; i < number_of_instrumnets; i++)
	{
		free(MusiciansCollection[i]);
	}
	free(MusiciansCollection);
}
