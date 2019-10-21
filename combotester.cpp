#include <iostream>
#include <string>
#include <sstream>
#include "combolock.h" //combolock class

using namespace std;


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
	
	// print combos testing purposes
	cout << "Combos: " << endl;
	cout << combos[0][0] << ", " << combos[0][1] << ", " << combos[0][2] << endl;
	cout << combos[1][0] << ", " << combos[1][1] << ", " << combos[1][2] << endl;
	cout << combos[2][0] << ", " << combos[2][1] << ", " << combos[2][2] << endl;
	cout << combos[3][0] << ", " << combos[3][1] << ", " << combos[3][2] << endl;
	cout << combos[4][0] << ", " << combos[4][1] << ", " << combos[4][2] << endl << endl;

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
	c0.turnLeft(40 + second - c0.getDialPosition()); //turn to second code value
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

//Find correct numbers in correct order with correct turns. Reset. Should be FALSE
bool ComboLockTester::test4(int first, int second, int third){

	ComboLock c4(first, second, third); //create ComboLock obj with given code
	c4.turnRight(40 - first); //turn to initial code value
	c4.turnLeft(40 + second - c4.getDialPosition()); //turn to second code value
	c4.turnRight(40 - third + c4.getDialPosition()); //turn to third code value
	c4.reset(); //reset lock
	return c4.open(); //try to open lock, should eval to FALSE
}




int main(){
	ComboLockTester test;	
	cout << "False results: " << test.tester() << endl;
	return 0;
}
