#include "musicianGroup.h"
#include "utility.h"
#include "treeSupport.h"
Musician** get_musicians(InstrumentTree musicInstrumentsTree, FILE* file, int* number_of_musicians, int numberOfInstruments)
{//function perpuse is to get the musicians one by one from Musician.txt file and put them in arr of musicians pointers.
	Musician** arr = (Musician**)malloc(sizeof(Musician*));     //check no musicians***
	checkAllocation(arr);
	int logical_size = NONE, physical_size = 1;					//logical and physical size of musician arr ptr.
	char line[MAX_LINE_LEN];

	while (fgets(line, MAX_LINE_LEN, file))						//while there are still musicians.
	{
		if (physical_size == logical_size)						//if logical size equal to phisical - make logical size double space.
			make_double_space(&physical_size, &arr);
		arr[logical_size] = get_one_musician(line, musicInstrumentsTree, numberOfInstruments); //get musician ptr to his location in arr 
		logical_size++;											//update logical size.
	}
	arr = realloc(arr, logical_size * sizeof(Musician*));		//reallocate arr by logical space size.
	checkAllocation(arr);
	*(number_of_musicians) = logical_size;						//update number of existing musicians and return arr.
	return arr;
}
Musician* get_one_musician(char* line, InstrumentTree musicInstrumentsTree, int numberOfInstruments)
{//function perpuse is to get one musician fron a given line in text and return a pointer to him.
	Musician* musician = (Musician*)malloc(sizeof(Musician));
	checkAllocation(musician);
	initiate_musician(musician, numberOfInstruments);			//initiate basic musician parameters.
	char* tok = strtok(line, DELIMETERS);						//token of line , splited by delimeters.
	bool is_name = true;										
	int number_of_inserted_names = NONE;
	while (tok != NULL && tok[FIRST_IND] != END_OF_LINE)		//while there is data to musician.
	{
		if (isdigit(tok[FIRST_IND]) && is_name)    //if we have arrived to first price in line. (first instrument char* is now in last place of musician name)
		{
			is_name = false;
			insert_data_to_end_of_list(&musician->instruments, musician->name[number_of_inserted_names - 1], musicInstrumentsTree);
			update_musician(musician, number_of_inserted_names - 1, tok);
		}
		else if (is_name)						  //else if tokken is a name or first instrument.
		{
			insert_name_word(tok, &musician->name, &musician->number_of_names, number_of_inserted_names);
			number_of_inserted_names++;
		}
		else							  //else, if tokken is a number update price and price arr, if instrument appeand to linneked list.
		{
			if (isdigit(tok[FIRST_IND]))
			{
				musician->instruments.tail->price = atof(tok);
				musician->prices[musician->instruments.tail->insID] = musician->instruments.tail->price;
			}
			else
				insert_data_to_end_of_list(&musician->instruments, tok, musicInstrumentsTree);
		}
		tok = strtok(NULL, DELIMETERS);
	}
	return musician;
}
void make_empty_MusicianPriceInstrument_list(MPIList* lst) 
{//the function purpose is to make an empty list.
	lst->head = NULL;
	lst->tail = NULL;
}
void insert_data_to_end_of_list(MPIList* lst, char* instrument, InstrumentTree musicInstrumentsTree)   
{//the function purpose is to insert a new data to the lineked list.
	MusicianPriceInstrument* new_node;
	new_node = create_new_list_node(instrument, NULL, musicInstrumentsTree);    //make a new node with data - by id tree finder.
	insert_node_to_end_of_list(lst, new_node);									//insert instrument to end of linked list.
}
MusicianPriceInstrument* create_new_list_node(char* instrument, MusicianPriceInstrument* next, InstrumentTree musicInstrumentsTree) 
{//the function purpose is to create a new node with data, returns a node pointer.
	MusicianPriceInstrument* res = (MusicianPriceInstrument*)malloc(sizeof(MusicianPriceInstrument));
	checkAllocation(res);                                          //allocation and check allocation of a new node.
	res->insID = findInsId(musicInstrumentsTree, instrument);      //value update.
	res->next = next;
	return res;
}
void insert_node_to_end_of_list(MPIList* lst, MusicianPriceInstrument* newTail)   
{ //the function purpose is to insert data to the end of lineked list.
	if (lst->head == NULL)
	{
		lst->head = newTail;
		lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
void insert_name_word(char* name_word, char*** names_array, int* physical_size, int logical_size)
{//the function purpose is to insert a given name to name char** arr.
	char* temp;
	int word_len = strlen(name_word);
	temp = (char*)malloc((word_len + 1) * sizeof(char));  //allocate space for name to append to arr.
	checkAllocation(temp);
	strcpy(temp, name_word);							  //copy given name.
	if (*physical_size == logical_size)					  //if there is no more space in arr - double it.
		make_double_space(physical_size, names_array);
	*(*names_array + logical_size) = temp;				  //place name in arr.
}
float* createPricesArr(int size)
{//the function purpose is to create price arr for each musician and initiate valuse.
	int i;
	float* prices;
	prices = (float*)malloc(size * sizeof(float));   //allocate space for price arr by number of instrument in total.
	checkAllocation(prices);
	for (i = NONE; i < size; i++)				 //initiate prices.
		prices[i] = NOT_PLAYING;
	return prices;
}
void update_musician(Musician* musician, int number_of_names, char* tok)
{//the function purpose is to update musician that his last name in name arr is an instrument.
	free(musician->name[number_of_names]);				//free the instrumen in names arr.
	musician->name = realloc(musician->name, number_of_names * sizeof(char*)); //reallocate the name arr by number of names.(shrink by 1)
	checkAllocation(musician->name);
	musician->instruments.tail->price = atof(tok);		//insert price to lineked list.
	musician->prices[musician->instruments.tail->insID] = musician->instruments.tail->price;//insert price to price arr;
	musician->number_of_names = number_of_names;		//update number of names.
	musician->is_playing = false;						//update musician in not playing yet.
}
void initiate_musician(Musician* musician, int numberOfInstruments)
{//the function purpose is to initiate musician valuse.
	musician->number_of_names = 2;						//minimum 2 names - update and allocate name arr space.
	musician->name = (char**)malloc(2 * sizeof(char*));
	checkAllocation(musician->name);
	musician->prices = createPricesArr(numberOfInstruments); //create price arr;
	make_empty_MusicianPriceInstrument_list(&musician->instruments); //make empty lineked list of instrument to musician.
}
void freeMusicianGroup(Musician** musician_group, int number_of_musicians)
{//frees all the data of each musician
	int i, j;
	for (i = 0; i < number_of_musicians; i++)
	{
		free(musician_group[i]->prices);//free his prices array
		freeMPIList(musician_group[i]->instruments);//free linked list of instruments
		for (j = 0; j < musician_group[i]->number_of_names; j++)//this for loop frees all the players names
		{
			free(musician_group[i]->name[j]);
		}
		free(musician_group[i]->name);
		free(musician_group[i]);
	}
	free(musician_group);
}
void freeMPIList(MPIList lst)
{//the function recives a linked list of instruments as input and frees all the memory it takes
	MusicianPriceInstrument* p = NULL, * q = NULL;
	if (lst.head == NULL)
		return;
	p = lst.head;
	while (p->next != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
}