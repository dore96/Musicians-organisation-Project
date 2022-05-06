#include "treeSupport.h"
//here we will write function that have complete use of the tree
int findInsId(InstrumentTree tree, char* instrument)
{//this function gets as input a tree and instruments name and returns its id.
	return findInsIdRec(tree.root, instrument);
}
int findInsIdRec(TreeNode* root, char* instrument)
{
	//finds instrument in tree and return its id
	if (root == NULL)//means instrument does not exist
	{
		return INSTRUMENT_DOES_NOT_EXIST;
	}
	else if (!strcmp(instrument, root->instrument))//if found the instrument
	{
		return root->insId;
	}
	else
	{
		//if not found and not end of tree, we will compare with sub trees
		if (strcmp(root->instrument, instrument) > 0)
		{
			return findInsIdRec(root->left, instrument);
		}
		else
		{
			return findInsIdRec(root->right, instrument);
		}
	}
}
int getAmountOfInstruments(InstrumentTree musicInstrumentsTree)
{//function purpose is to return amount of instrument for given tree.
	return getAmountOfInstrumentsRec(musicInstrumentsTree.root);
}
int getAmountOfInstrumentsRec(TreeNode* root)
{//function purpose is to return amount of instrument for given root.(recursively).
	if (root == NULL)
	{
		return NONE;
	}
	else
	{
		return getAmountOfInstrumentsRec(root->left) + getAmountOfInstrumentsRec(root->right) + 1;
	}
}
