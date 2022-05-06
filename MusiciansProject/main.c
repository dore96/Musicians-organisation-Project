//this program was made by:
//Dor Edelman 315315812
//Maor Halevi 207691080
#include "header.h"
#include "concertCreation.h"
#include "musicianGroup.h"
#include "tree.h"
#include "treeSupport.h"
#include "utility.h"
#include "musicianCollection.h"

int main(int argc, char* argv[])
{
	Musician** MusiciansGroup;
	Musician*** MusiciansCollection;
	int number_of_musicians = 0, numberOfInstruments;
	int* musicianCollectionArraySizes;
	FILE* instrumentsFile = fopen(argv[1], "r");//open instrument file
	checkFileOpening(instrumentsFile, argv[1]);
	FILE* MusiciansFile = fopen(argv[2], "r");//open musicians file
	checkFileOpening(MusiciansFile, argv[2]);
	InstrumentTree musicInstrumentsTree = BuildInstrumentTree(instrumentsFile);//create instruments tree
	numberOfInstruments = getAmountOfInstruments(musicInstrumentsTree);//how many instruments in tree
	MusiciansGroup = get_musicians(musicInstrumentsTree, MusiciansFile, &number_of_musicians, numberOfInstruments);//array of musicians
	MusiciansCollection = createMusicianCollection(MusiciansGroup, number_of_musicians, numberOfInstruments, &musicianCollectionArraySizes);//creates matrix of musicians by instrument
	bookAConcert(MusiciansCollection, musicianCollectionArraySizes, musicInstrumentsTree);//creates and prints concert
	FileClosing(instrumentsFile, MusiciansFile);//closes files
	free(musicianCollectionArraySizes);//free memory
	freeAll(musicInstrumentsTree, MusiciansGroup, number_of_musicians, MusiciansCollection, numberOfInstruments);
	_CrtDumpMemoryLeaks();
	return 0;
}