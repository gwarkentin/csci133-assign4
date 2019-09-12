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
	//store lock code into array	
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

	//only update entry array still has space	
	if (currentInd < lockSize)
	{
		entrysDirs[currentInd][0] = endNum;
		entrysDirs[currentInd][1] = dir;
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
	cout << endl;	
	*/
	
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


// Class which tests combo lock to ensure it correctly handles different usage
class ComboLockTester {
	//create array of combinations so different numbers can be tested easily
	int combos[5][3] =
		{
			{10,20,30},
			{30,20,10},
			{9,10,11},
			{11,10,9},
			{1,1,1}
		};

	bool results[5]; //stores each test's result. To spec returns 4
	bool test0(int, int, int); //zeroth test. Should be TRUE
	bool test1(int, int, int); //first  test. Should be FALSE
	bool test2(int, int, int); //second test. Should be FALSE
	bool test3(int, int, int); //third  test. Should be FALSE
	bool test4(int, int, int); //forth  test. Should be FALSE

	public:
	int tester(); //calls each other test
};

//tester to call from program, call each other test. Returns count of false tests
int ComboLockTester::tester(){
	
	/* print combos testing purposes
	cout << combos[0][0] << ", " << combos[0][1] << ", " << combos[0][2] << endl;
	cout << combos[1][0] << ", " << combos[1][1] << ", " << combos[1][2] << endl;
	cout << combos[2][0] << ", " << combos[2][1] << ", " << combos[2][2] << endl;
	cout << combos[3][0] << ", " << combos[3][1] << ", " << combos[3][2] << endl;
	cout << combos[4][0] << ", " << combos[4][1] << ", " << combos[4][2] << endl << endl;
	*/

	//run each test function with a new line from the combos array
	//bool results from each test are stored in an array
	
	results[0] = test0(combos[0][0],combos[0][1],combos[0][2]);
	results[1] = test1(combos[1][0],combos[1][1],combos[1][2]);
	results[2] = test2(combos[2][0],combos[2][1],combos[2][2]);
	results[3] = test3(combos[3][0],combos[3][1],combos[3][2]);
	results[4] = test4(combos[4][0],combos[4][1],combos[4][2]);

	//count each false result
	int falses = 0;
	for (int i = 0; i < 5; i++)
	{
		if ( ! results[i])
		{
			falses++;
		}
	}
	return falses; //return qty of false results in tests
}

//Find correct numbers in correct order with correct turns. Should be TRUE
bool ComboLockTester::test0(int first, int second, int third){

	ComboLock c0(first, second, third); //create ComboLock obj with given code
	c0.turnRight(40 - first); //turn to initial code value
	c0.turnLeft(second - c0.getDialPosition()); //turn to second code value
	c0.turnRight(40 - third + c0.getDialPosition()); //turn to third code value
	return c0.open(); //try to open lock, should eval to TRUE
}

//Find correct numbers in correct order, all right turns. Should be FALSE
bool ComboLockTester::test1(int first, int second, int third){

	ComboLock c1(first, second, third); //create ComboLock obj with given code
	c1.turnRight(40 - first); //turn to initial code value
	c1.turnRight(40 - second + c1.getDialPosition() ); //turn to second code value
	c1.turnRight(40 - third + c1.getDialPosition() ); //turn to third code value
	return c1.open(); //try to open lock, should eval to FALSE
}

//Right to correct, left to wrong, right to correct. Should be FALSE
bool ComboLockTester::test2(int first, int second, int third){

	ComboLock c2(first, second, third); //create ComboLock obj with given code
	c2.turnRight(40 - first); //turn to first code value
	c2.turnLeft(50 + second - c2.getDialPosition() ); //turn to wrong second code
	c2.turnRight(40 - third + c2.getDialPosition() ); //turn to third code value
	return c2.open(); //try to open lock, should eval to FALSE
}

//Right to wrong, left to wrong, right to correct. Should be FALSE
bool ComboLockTester::test3(int first, int second, int third){

	ComboLock c3(first, second, third); //create ComboLock obj with given code
	c3.turnRight(50 - first); //turn to wrong first number
	c3.turnLeft(40 + second); //turn to wrong second code
	c3.turnRight(40 - third + c3.getDialPosition() ); //turn to correct third code
	return c3.open(); //try to open lock, should eval to FALSE
}

//Find correct numbers in correct order with correct turns. Should be TRUE
bool ComboLockTester::test4(int first, int second, int third){

	ComboLock c4(first, second, third); //create ComboLock obj with given code
	c4.turnRight(40 - first); //turn to initial code value
	c4.turnLeft(40 + second - c4.getDialPosition()); //turn to second code value
	c4.turnRight(40 - third + c4.getDialPosition()); //turn to third code value
	c4.reset(); //reset lock
	return c4.open(); //try to open lock, should eval to FALSE
}

int main(){
	
	ComboLockTester t1; //creates ComboLockTesting object which will make it's own locks to test 
	cout << "Non-opens exp. : 4" << endl; //tests have been set up for 4 to return false
	cout << "Non-opens act. : " << t1.tester() << endl; //if 4 false opens then combolock works correctly
	return 0;
}
