#pragma once
#include "header.h"
//funcs that are involved in the creation of the tree

InstrumentTree BuildEmptyTree();
TreeNode* createTreeNode(char* data, TreeNode* left, TreeNode* right);
void Insert(InstrumentTree* tree, char* data);
TreeNode* FindPlace(TreeNode* tree, char* data);
InstrumentTree BuildInstrumentTree(FILE* instrumentsFile);
void freeTree(InstrumentTree tr);
void FreeTreeRec(TreeNode* tr);