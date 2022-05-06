#pragma once
#include "header.h"
void checkFileOpening(FILE* file, char* argv);
void FileClosing(FILE* file1, FILE* file2);
void freeAll(InstrumentTree tr, Musician** musician_group, int number_of_musicians, Musician*** MusiciansCollection, int number_of_instrumnets);
void checkAllocation(void* ptr);
void make_double_space(int* size, void*** arr);