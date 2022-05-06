#include "header.h"
#include "tree.h"
#include "musicianGroup.h"
#include "musicianCollection.h"

void checkAllocation(void* ptr)
{//this function checks if the memory was allocated well.
	if (ptr == NULL)
	{
		printf("Memory allocation failed!!!");
		exit(1);
	}
}
void make_double_space(int* size, void*** arr)
{//the function purpose is to double the space of a given arr.
	MULTY_BY_TWO(*size);
	*arr = realloc(*arr, *size * sizeof(void*));
	checkAllocation(arr);
}
//hi gil
void checkFileOpening(FILE* file, char* argv)
{//checks if file has opened successfully
	if (file == NULL)
	{
		printf("File %s does not exist", argv);
		exit(1);
	}
}
void FileClosing(FILE* file1, FILE* file2)
{//closes open files
	if (fclose(file1) || fclose(file2))
	{
		exit(1);
	}
}
void freeAll(InstrumentTree tr, Musician** musician_group, int number_of_musicians, Musician*** MusiciansCollection, int number_of_instrumnets)
{//this function frees the data structurs in this program
	freeTree(tr);
	freeMusicianGroup(musician_group, number_of_musicians);
	freeMusicianCollaction(MusiciansCollection, number_of_instrumnets);
}