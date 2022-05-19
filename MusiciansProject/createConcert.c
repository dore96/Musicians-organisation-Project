#include "concertCreation.h"
#include "utility.h"
#include "treeSupport.h"
int currInst;//global variale
void bookAConcert(Musician*** MusiciansCollection, int* musicianCollectionArraySizes, InstrumentTree musicInstrumentsTree)
{//this function recives as input a matrix of musicians by instrument, each array size and a tree of instruments
	//it will recive additional input from the user and create a concert if possible according to his demands if not will print not available
	Concert myConcert;
	char c;
	Musician** musicians_for_concert;
	bool concert_is_able;
	while ((c = getchar()) != END_OF_LINE)
	{//we will recive concert details until user has entered an empty line
		myConcert = getConcertDetails(c, musicInstrumentsTree);//get concert details
		sort_musician_arrs(MusiciansCollection, musicianCollectionArraySizes, myConcert);//sorts musicians according to importance
		concert_is_able = build_concert(MusiciansCollection, musicianCollectionArraySizes, myConcert, &musicians_for_concert);//if possible builds a concert
		if (concert_is_able)//if the concert was successfully built we will print it
			print_concert(myConcert, musicians_for_concert);
		else//else we will print it was not able to create a concert
			printf("Could not find musicians for the concert %s\n\n", myConcert.name);
		free(myConcert.name);
		freeConcertInstrumentList(myConcert.instruments);//free list of wanted instruments for concert
		free(musicians_for_concert);
	}
}
Concert getConcertDetails(char firstLetter, InstrumentTree musicInstrumentsTree)
{/*this function will recive input from the user such as date and name of the concert and will create a linked
 list containing what instruments are needed and how many players of each instrument
 */
	Concert currentConcert;
	int amount;
	float hours, mins;
	char currInstrument[MAX_LINE_LEN];
	char importance, currChar = DEFAULT_CHAR;
	createEmptyInstrumentList(&currentConcert.instruments);//creates empty list
	currentConcert.name = getName(firstLetter);//get name of concert
	scanf("%d %d %d %f:%f", &currentConcert.date_of_concert.day, &currentConcert.date_of_concert.month, &currentConcert.date_of_concert.year, &hours, &mins);//get date and time
	currentConcert.date_of_concert.hour = GET_TIME(hours,mins);
	while (currChar != END_OF_LINE)
	{//as long as we have not finished the line reffering to current cocnert, get info about instruments
		scanf(" %s %d %c", currInstrument, &amount, &importance);
		insertInstrumentData(&currentConcert.instruments, currInstrument, amount, importance, musicInstrumentsTree);//creates list node with instrument data
		currChar = getchar();//get next char which  is space or end of line
	}
	return currentConcert;//return concert info
}
char* getName(char firstChar)
{//this function recives a first char of string as input and will get the rest of string and return it
	char c;
	char* name;
	int physicalSize, logicalSize;
	physicalSize = 2;
	logicalSize = 1;
	name = (char*)malloc((physicalSize + 1) * sizeof(char));
	name[0] = firstChar;
	checkAllocation(name);
	while ((c = getchar()) != ' ')
	{//as long as we are still in name of concert
		if (physicalSize == logicalSize)//if memory size needs expansion
		{
			physicalSize *= 2;
			name = realloc(name, (physicalSize + 1) * sizeof(char));
			checkAllocation(name);
		}
		name[logicalSize] = c;
		logicalSize++;
	}
	name = realloc(name, (logicalSize + 1) * sizeof(char));
	checkAllocation(name);
	name[logicalSize] = '\0';//end of string char at the end of the name
	return name;//return name of concert
}
void createEmptyInstrumentList(CIList* lst)
{//creates empty list
	lst->head = lst->tail = NULL;
}
ConcertInstrument* createConcertInstrumentListNode(char* instrument, int amount, char importance, ConcertInstrument* next, InstrumentTree musicInstrumentsTree)
{//this function will create a new node in the concert instruments linked list and insert in it the input data it recives
	ConcertInstrument* newNode = malloc(sizeof(ConcertInstrument));
	checkAllocation(newNode);
	newNode->importance = importance;
	newNode->num = amount;
	newNode->inst = findInsId(musicInstrumentsTree, instrument);
	newNode->next = next;
	strcpy(newNode->instrument_name, instrument);
	return newNode;
}
void insertInstrumentData(CIList* lst, char* instrument, int amount, char importance, InstrumentTree musicInstrumentsTree)
{//this function gets data to create a new linked list node in the concert instrument list and inserts it to the end of the list
	ConcertInstrument* newNode;
	newNode = createConcertInstrumentListNode(instrument, amount, importance, NULL, musicInstrumentsTree);
	insertInstrumentNodeToEnd(lst, newNode);
}
void insertInstrumentNodeToEnd(CIList* lst, ConcertInstrument* newTail)
{//gets a list and node as input as inserts the node to be in the end of the list
	if (lst->head == NULL)//if list is empty, create new head and tail
	{
		lst->head = newTail;
		lst->tail = newTail;
	}
	else//update tail only
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
void sort_musician_arrs(Musician*** MusiciansCollection, int* musicianCollectionArraySizes, Concert myConcert)
{//this function recives a pointer to the musicans collection and will sort the musicians of each instrument depending on the importance of the instrument in the inputted concert
	ConcertInstrument* concert_ins_ptr = myConcert.instruments.head;
	while (concert_ins_ptr)//run on all instruments which will be in the inputted concers
	{
		currInst = concert_ins_ptr->inst;//get instrument id
		pointerSort(MusiciansCollection[currInst], musicianCollectionArraySizes[currInst], concert_ins_ptr->importance);//sort by importance
		concert_ins_ptr = concert_ins_ptr->next;//go to next instrument
	}
}
void pointerSort(Musician** arr, int size, char importance)
{//this function will sort the arr of musicians by importance
	if (importance == IMPORTANT)//if important sort for highest price to lowesr
	{
		qsort(arr, size, sizeof(Musician*), compare1);
	}
	else//sort from lowest to highest
	{
		qsort(arr, size, sizeof(Musician*), compare2);
	}
}
int compare1(const void* a, const void* b)
{//compare function for qsrot high to low
	Musician** p1 = (Musician**)a;
	Musician** p2 = (Musician**)b;
	return (int)((*p2)->prices[currInst] - (*p1)->prices[currInst]);
}
int compare2(const void* a, const void* b)
{//compare function for qsrot low to high
	Musician** p1 = (Musician**)a;
	Musician** p2 = (Musician**)b;
	return (int)((*p1)->prices[currInst] - (*p2)->prices[currInst]);
}
bool build_concert(Musician*** MusiciansCollection, int* musicianCollectionArraySizes, Concert myConcert, Musician*** musicians_for_concert)
{/*this function recives a pointer to musician collection an array of size of each musician array, a concert and will retrurn true of false if the concert
 can be made or not and will return an array of the musicians that will be used of each instrument with the musician for concert pointer*/
	ConcertInstrument* concert_ins_ptr = myConcert.instruments.head;
	int num_curr_instrument, i, playersOnThisInstrumentTaken = 0, logical_size = 0, physical_size = 1;
	*musicians_for_concert = (Musician**)malloc(sizeof(Musician*));
	checkAllocation(*musicians_for_concert);
	while (concert_ins_ptr)//while still needs to go thorugh instrumnets that are needed for concert
	{
		num_curr_instrument = concert_ins_ptr->num;///get num of musicians needed from this instrument
		if (num_curr_instrument > musicianCollectionArraySizes[concert_ins_ptr->inst])//if needed more than availbe return false
		{
			resetPlayers(*musicians_for_concert, logical_size);
			return false;
		}
		for (i = 0; i < num_curr_instrument; i++)//else we will find the wanted musicians
		{
			if (logical_size == physical_size)//if musicians for concert needs more space, we will expand it
			{
				physical_size *= 2;
				*musicians_for_concert = realloc(*musicians_for_concert, (physical_size) * sizeof(Musician*));
				checkAllocation(*musicians_for_concert);
			}
			while (MusiciansCollection[concert_ins_ptr->inst][i + playersOnThisInstrumentTaken]->is_playing)//this while loop will run until we will find the most sutible musician for this instrument who is availble
			{
				playersOnThisInstrumentTaken++;
				if (playersOnThisInstrumentTaken + i >= musicianCollectionArraySizes[concert_ins_ptr->inst])//if not enough availble musicians return false
				{
					resetPlayers(*musicians_for_concert, logical_size);//reset players for next concert
					return false;
				}
			}
			MusiciansCollection[concert_ins_ptr->inst][i + playersOnThisInstrumentTaken]->is_playing = true;//set selected player to be playing
			*(*musicians_for_concert + logical_size) = MusiciansCollection[concert_ins_ptr->inst][i + playersOnThisInstrumentTaken];//add him to the array in the right place
			logical_size++;
		}
		concert_ins_ptr = concert_ins_ptr->next;//go to next instrument
		playersOnThisInstrumentTaken = NONE;
	}
	return true;//concert can be made
}
void print_concert(Concert myConcert, Musician** musicians_for_concert)
{//this function recives as input a concert and matrix of musicians of each instrument, it will print all the details and musicians which are playing in this concert
	int i, players_so_far = NONE, j;
	float totalPrice = NONE;
	printf("Concert name: %s\n", myConcert.name);//prints concert name
	printf("Concert date: %02d/%02d/%04d\n", myConcert.date_of_concert.day, myConcert.date_of_concert.month, myConcert.date_of_concert.year);//print date
	printf("Concert time: %02d:%02d\n", (int)myConcert.date_of_concert.hour, (int)((myConcert.date_of_concert.hour - (int)myConcert.date_of_concert.hour) * 60));//print time
	printf("Concert players:\n");
	ConcertInstrument* concert_ins_ptr = myConcert.instruments.head;
	while (concert_ins_ptr)//run on all instruments that are needed for this concert
	{
		for (i = 0; i < concert_ins_ptr->num; i++)//run on the number of players needed for this instrument
		{
			printf("Player number %d: ", players_so_far + 1);//print player number
			for (j = 0; j < musicians_for_concert[players_so_far + i]->number_of_names; j++)//print all his names
			{
				printf("%s ", musicians_for_concert[players_so_far + i]->name[j]);
			}
			printf("playing the %s ", concert_ins_ptr->instrument_name);//print instrument name
			printf("price - %.2f\n", musicians_for_concert[players_so_far + i]->prices[concert_ins_ptr->inst]);//print price he is taking
			totalPrice += musicians_for_concert[players_so_far + i]->prices[concert_ins_ptr->inst];//add his price to total price
			(musicians_for_concert[players_so_far + i])->is_playing = false;//set him to be active for next concert
		}
		players_so_far += i;//increase player number
		concert_ins_ptr = concert_ins_ptr->next;//go to next instrument
	}
	printf("Total price of concert: %.2f\n\n", totalPrice);//print total price of concert
}
void resetPlayers(Musician** players, int size)
{//this function will reset all platers in the array to be available and in not playing mode
	int i;
	for (i = 0; i < size; i++)
		players[i]->is_playing = false;
}
void freeConcertInstrumentList(CIList lst)
{//free list of instrument for the concert
	ConcertInstrument* p = NULL, * q = NULL;
	if (lst.head == NULL)
		return;
	p = lst.head;
	while (p->next != NULL)//run until the last instrument that needs to be freed
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
}
