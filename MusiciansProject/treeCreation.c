#include "tree.h"
#include "utility.h"
InstrumentTree BuildEmptyTree()
{//this function builds empty tree
	InstrumentTree tr;
	tr.root = NULL;
	return tr;
}
TreeNode* createTreeNode(char* data, TreeNode* left, TreeNode* right)
{//this fucntion recives a data and creates a tree node with this data.
	static int id = 0;//we will use static int to insert id to each instrument
	TreeNode* newNode;
	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	checkAllocation(newNode);
	newNode->insId = id;
	id++;
	newNode->instrument = data;
	newNode->left = left;
	newNode->right = right;
	return newNode;
}
void Insert(InstrumentTree* tree, char* data)
{
	/*this function recives a data as input,it will create
	a new tree node with this data and it will find where the new node with this data needs to be inserted in an existing
	tree and insert it*/
	TreeNode* father;
	TreeNode* new_one;

	new_one = createTreeNode(data, NULL, NULL);//create new node with the inputted data.

	if (tree->root == NULL)//if tree is empty put it as root
		tree->root = new_one;
	else//find its place and insert it
	{
		father = FindPlace(tree->root, data);
		if (strcmp(father->instrument, data) > 0)
			father->left = new_one;
		else
			father->right = new_one;
	}
}
TreeNode* FindPlace(TreeNode* tree, char* data)	// Returning the parent of the new val needed to be inserted
{//uses strcmp to find the right place for the new node to be inserted
	if (strcmp(tree->instrument, data) > 0)
	{
		if (tree->left == NULL)
			return tree;
		else
			return FindPlace(tree->left, data);
	}
	else
	{
		if (tree->right == NULL)
			return tree;
		else
			return FindPlace(tree->right, data);
	}
}
InstrumentTree BuildInstrumentTree(FILE* instrumentsFile)
{
	//this function builds a tree of playing insturments it get from a file
	char currentInstrument[MAX_LINE_LEN];
	InstrumentTree tr = BuildEmptyTree();
	while (fgets(currentInstrument, MAX_LINE_LEN, instrumentsFile))//while not read all file
	{
		int len = strcspn(currentInstrument,"\n"); //get the length of string until end of line
		char* currentData = malloc((len + 1) * sizeof(char));
		checkAllocation(currentData);
		strncpy(currentData, currentInstrument, len);//copies string without the end of line char
		currentData[len] = '\0';//put end of string char
		Insert(&tr, currentData);//insert the instrument to the tree
	}
	return tr;
}
void freeTree(InstrumentTree tr)
{//frees tree
	FreeTreeRec(tr.root);
}
void FreeTreeRec(TreeNode* tr)
{//frees all nodes in the tree
	if (tr != NULL)
	{
		FreeTreeRec(tr->left);
		FreeTreeRec(tr->right);
		free(tr->instrument);
		free(tr);
	}
}