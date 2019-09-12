#include <iostream>
#include <random>

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
	codesDirs[0][0] = first;
	codesDirs[1][0] = second;
	codesDirs[2][0] = third;
	
	//makes directions -1, +1, -1, +1, -1 ... in case we wanted bigger lock	
	//private function to add entry and move others back one
	int positive = -1;	
	for (int i = 0; i < lockSize; i++)
	{
		codesDirs[i][1] = positive;
		positive *= -1;
	}
	
	/* was test to ensure they captured correctly.
	for (int i = 0; i < lockSize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << codesDirs[i][j] << ", ";
		}
		cout << endl;
	}	
	*/

	reset(); //rather than including these in class declaration
}

//resets the lock and entry values
void ComboLock::reset(){
	dialPos = 0;
	currentInd = 0;
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
	
	if (currentInd < lockSize)
	{
		entrysDirs[currentInd][0] = endNum;
		entrysDirs[currentInd][1] = dir;
	}

	for (int i = 0; i < lockSize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << entrysDirs[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl;	
	
	//move "first empty" over one for next entry
	currentInd++;
}


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

bool ComboLock::open()
{
	bool status[lockSize] = {false};
	bool allStat = true;	
	for (int i = 0; i < lockSize; i++)
	{
		if ((entrysDirs[i][0] == codesDirs[i][0]) && (entrysDirs[i][1] == codesDirs[i][1]))
		{
			status[i] = true;
		}
			
	}
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
	if (allStat) //if all true then reset lock.
	{
		reset();
	}
	return allStat; //returns true if all values true, otherwise false
}



class ComboLockTester {
	int combos[5][3] =
		{
			{10,20,30},
			{30,20,10},
			{9,10,11},
			{11,10,9},
			{1,1,1}
		};


	bool results[5]; //stores each test's result
	bool test0(int, int, int);
	bool test1(int, int, int);
	//bool test2(int, int, int);
	//bool test3(int, int, int);
	//bool test4(int, int, int);

	public:
	int tester(); //calls each other test
};

//tester to call from program, call each other test. Returns count of false tests
int ComboLockTester::tester(){

	results[0] = test0(combos[0][0],combos[0][1],combos[0][2]);
	results[1] = test1(combos[1][0],combos[1][1],combos[1][2]);

	int falses = 0;
	for (int i = 0; i < 2; i++)
	{
		if ( ! results[i])
		{
			falses++;
		}
	}

	return falses;

}

bool ComboLockTester::test0(int first, int second, int third){

	
	ComboLock c0(first, second, third);

	c0.turnRight(40 - first);
	c0.turnLeft(40 + second - c0.getDialPosition());
	c0.turnRight(40 - third + c0.getDialPosition());
	return c0.open();
}

bool ComboLockTester::test1(int first, int second, int third){

	ComboLock c1(first, second, third);
	c1.turnRight(40 - first);
	c1.turnRight(40 - second + c1.getDialPosition() );
	c1.turnRight(40 - third + c1.getDialPosition() );
	return c1.open();
}


int main(){
	
	ComboLockTester t1;
	cout << "Non-opens exp. : 4" << endl;
	cout << "Non-opens act. : " << t1.tester() << endl;
	return 0;
}
