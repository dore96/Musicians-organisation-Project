#pragma once
#include "header.h"
#define INSTRUMENT_DOES_NOT_EXIST -1
#define NONE 0

//function that use the tree
int findInsId(InstrumentTree tree, char* instrument);
int findInsIdRec(TreeNode* root, char* instrument);
int getAmountOfInstruments(InstrumentTree musicInstrumentsTree);
int getAmountOfInstrumentsRec(TreeNode* root);