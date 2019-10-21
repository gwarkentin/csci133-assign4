#include <iostream>
#include <string>

#ifndef combolock
#define combolock
using namespace std;

//Comination lock class. Needs to land on the right numbers in the right order going in the correct direction to open.
class ComboLock {
	int lockSize; //so we could easily make bigger lock	
	int dialPos; //current position of dial	
	int currentInd; //current entry index
	int codesDirs[10][2]; //code will be stored here, dirs left = 1, right = -1
	int entrysDirs [10][2]; //array for entered values and dirs
	
	void addEntry(int, int);
	public:
       	ComboLock (int, int, int); //delcares the class initialization
	int getDialPosition(){return dialPos;}; //returns the current position of the dial
	void reset(); //resets the lock
	void turnLeft(int); //turns lock left by desired number of ticks
	void turnRight(int); //turns lock right by desired number of ticks
	bool open(); //checks if entries are correct so lock can be openned, if so reset and return true
};

//initialize the class given the 3 lock codes in order, rest has been coded so this can be expanded to larger lock
ComboLock::ComboLock (int first, int second, int third){
	lockSize = 3;
	//store lock code into array	
	codesDirs[0][0] = first;
	codesDirs[1][0] = second;
	codesDirs[2][0] = third;
	
	//makes directions -1, +1, -1, +1, -1 ... in case we wanted bigger lock	
	int positive = -1;	
	for (int i = 0; i < lockSize; i++)
	{
		codesDirs[i][1] = positive;
		positive *= -1;
	}
	reset(); //rather than including these in class declaration
}

//resets the lock and entry values
void ComboLock::reset(){
	dialPos = 0;
	currentInd = 0;
	//set every entry+dir to 0
	for (int i = 0; i < lockSize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			entrysDirs[i][j] = 0;
		}

	}
}

//add entry to array given the end number and direction
void ComboLock::addEntry(int endNum, int dir){
	//only update entry if array still has space	
	if (currentInd < lockSize)
	{
		entrysDirs[currentInd][0] = endNum;
		entrysDirs[currentInd][1] = dir;
	}
	//move "first empty" over one for next entry
	currentInd++;
}

//takes in tick count, adds to dial position until no more ticks left, resets from 40 to 0 
void ComboLock::turnLeft(int ticks){
	while (ticks > 0)
	{
		dialPos++;
		ticks--;
		if (dialPos == 40)
		{
			dialPos = 0;
		}
	}
	addEntry(dialPos, 1); //adds this to entry list. positive one is left
}

//takes in tick count, subracts from dial position until no more ticks left, resets from -1 to 39
void ComboLock::turnRight(int ticks){
	while (ticks > 0)
	{
		dialPos--;
		ticks--;
		if (dialPos == -1)
		{
			dialPos = 39;
		}
	}
	addEntry(dialPos, -1); //adds this to entry list. negative one is right
}

//Checks if lock is in correct position and turns, if so reset lock and return true. Else return false
bool ComboLock::open()
{
	bool status[lockSize] = {false}; //create bool array to store each value's correctness
	bool allStat = true; //init set all as being true	
	//compare each entry and direction to code
	for (int i = 0; i < lockSize; i++)
	{
		if ((entrysDirs[i][0] == codesDirs[i][0]) && (entrysDirs[i][1] == codesDirs[i][1]))
		{
			status[i] = true; //if entry+dir is correct, make corresponding bool true
		}
			
	}
	//if all true, leave true, otherwise its false and stays locked
	for (int i = 0; i < lockSize; i++)
	{
		if (allStat && status[i])
		{
			allStat = true;
		}
		else
		{
			allStat = false;
		}
	}

	/* This was to ensure function was working properly
	for (int i = 0; i < lockSize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << entrysDirs[i][j] << ", ";
		}
		cout << endl;
	}
	cout << allStat << endl;	
	*/
	
	if (allStat) //if all true then reset lock.
	{
		reset();
	}
	return allStat; //returns true if all values true, otherwise false
}

#endif
