// Full Name: Nur Suhaira Bte Badrul Hisham
// Full Time
// Declaration: It is my own work
// Task:
// NRIC is made up of 7 digits and a letter behind.
// This letter is calculated from the first 7 digits using the
// modulus 11 method.
// The steps involved to obtain the check digit is
/*
1. Multiply each digit in the NRIC number by its weight.
2. Add together the above products.
3. Modulus the resulting sum obtained from (2) by 11
4. Subtract the remainder from 11 to give the value of the check digit.
5. Check the check digit against the table to obtain the alphabet.
*/
#include <cctype>
#include <iostream>
#include <iomanip>
using namespace std;

// To print welcome message to user with a length parameter
int displayWelcome();

// To get (the returning value) the weight table of specific length (parameter)
int getWeightTable (int);

//Calling out subfunction checkLength for weight validation
bool checkWeight(int, int);

// To check (true or false) if the weight OR NRIC no is of specific length (the two
// parameters)
bool checkLength (int, int);

//Display a separation in between menu displays
void printPartition();

//Display menu message only if weight is validated with length
int displayMenu(bool);

//To validate first letter of NRIC (T or S)
bool checkFirstLetterIC(char);

//Find the sum of product of corresponding digits of NRIC number and the weight
int sumNRICweight(int, int);

// To get the check digit with certain value (less than or equal to 11)
char checkDigit (int);

//Process functions in service 1
void processService1(int, int, char);

//Process functions in service 2
char getAlphabet(int, int);

int main()
{   
	int length,weight, serviceNo, NRIC, IC;

	char firstLetterIC, lastLetterIC, upperLastLetter;

	bool errorWeight, errorNRIC, firstLetterOK;
	
	length = displayWelcome();

	do
	{
		weight =  getWeightTable(length);

		errorWeight = checkWeight(length, weight);

		if (errorWeight == true)
		{
			cout<< "Weight table must have length = "
				<< length
				<< endl
				<< endl;
		}

	} while (errorWeight == true);

	do
	{
		printPartition();

		serviceNo = displayMenu(errorWeight);

		switch(serviceNo)
		{
			case 1: printPartition();

					do
					{
						cout<< endl
							<< "Checking of valid NRIC"
							<< endl
							<< "======================"
							<< endl << endl
							<< "Enter your NRIC: ";

						cin >> firstLetterIC >> IC >> lastLetterIC;

						cin.ignore (100, '\n');

						firstLetterOK = checkFirstLetterIC(firstLetterIC);

						upperLastLetter = toupper(lastLetterIC);

						if (firstLetterOK == true)
						{
							errorNRIC = checkLength (length, IC);

							if (errorNRIC == true)
							{
								cout<< "NRIC No must of length = "
									<< length
									<< endl
									<< endl;
							}
						}

					} while ((firstLetterOK == false) || (errorNRIC == true));

					processService1(IC, weight, upperLastLetter);

					break;

			case 2:	printPartition();

					do
					{
						cout<< "To compute check digit"
							<< endl
							<< "======================"
							<< endl << endl
							<< "Enter only the no: ";
						cin >> NRIC;

						cin.ignore (100, '\n');

						errorNRIC = checkLength (length, NRIC);

						if (errorNRIC == true)
						{
							cout<< "NRIC No must of length = "
								<< length
								<< endl
								<< endl;
						}

					} while (errorNRIC == true);

					cout<< "The check digit is "
						<< getAlphabet(NRIC, weight)
						<< endl;

					break;

			case 9: printPartition();

					cout<< "Looking forward serving you again";
					break;
		}
	} while (serviceNo != 9);

	cout<< endl
		<< "Thank you for using the system"
		<< endl;
}

void printPartition()
{
	cout<< endl
		<< endl
		<< "***********************************************"
		<< endl
		<< endl;
}

int displayWelcome()
{
	int size;

	cout<< "Welcome to the NRIC Development System"
		<< endl
		<< "......................................"
		<< endl
		<< endl;

	cout<< "Enter the length of NRIC: ";

	cin >> size;

	cout << endl << endl;

	return size;
}

int getWeightTable (int length)
{
	int weight;

	cout<< "Enter weight table: ";

	cin >> weight;

	cin.ignore (100, '\n');

	return weight;
}

bool checkWeight(int length, int weight)
{
	bool error;

	error = checkLength(length, weight);

	return error;
}

bool checkLength (int length, int weight)
{
	int valLength = 0;

	while (weight > 0)
	{
		weight /= 10;
		++valLength;
	}

	if (valLength != length)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int displayMenu(bool errorLength)
{
	int num;

	if (errorLength == false)
	{
		cout<< "We provide two services"
			<< endl << endl
			<< "1. To check valid NRIC"
			<< endl
			<< "2. To compute NRIC check digit"
			<< endl
			<< "9. Quit"
			<< endl << endl
			<< "Service No: ";

		cin >> num;

		return num;
	}
}

bool checkFirstLetterIC(char firstLetterIC)
{
	bool ok;

	if ((firstLetterIC == 'T') || (firstLetterIC == 'S') ||
		(firstLetterIC == 't') || (firstLetterIC == 's'))
	{
		ok = true;
	}
	else
	{
		ok = false;
	}

	return ok;
}

void processService1(int IC, int weight, char upperLastLetter)
{
	int sum;

	char alpha;

	sum =  sumNRICweight(IC, weight);
	alpha = checkDigit(sum);

	cout<< "The computed check digit is "
		<< alpha
		<< endl;

	if (alpha == upperLastLetter)
	{
		cout<< endl
			<< "Valid check digit"
			<< endl;
	}
	else
	{
		cout<< endl
			<< "Invalid check digit"
			<< endl;
	}
}

int sumNRICweight(int NRIC, int weight)
{
	int sum = 0, lastDigitNRIC, lastDigitWeight;
	while ((NRIC > 0) || (weight > 0))
	{
		lastDigitNRIC = NRIC % 10;
		lastDigitWeight = weight % 10;

		sum += (lastDigitWeight * lastDigitNRIC);

		NRIC /= 10;
		weight /= 10;
	}

	return sum;
}

char checkDigit (int sum)
{
	int digit;

	digit = sum % 11;
	digit = 11 - digit;

	while (digit <= 11)
	{
		switch(digit)
		{
			case 1: return 'A';
					break;
			case 2: return 'B';
					break;
			case 3:	return 'C';
					break;
			case 4: return 'D';
					break;
			case 5: return 'E';
					break;
			case 6: return 'F';
					break;
			case 7: return 'G';
					break;
			case 8: return 'H';
					break;
			case 9: return 'I';
					break;
			case 10:return 'Z';
					break;
			case 11:return 'J';
					break;
		}
	}
}

char getAlphabet(int NRIC, int weight)
{
	int sum, digit;

	sum = sumNRICweight(NRIC, weight);

	digit = sum % 11;
	digit = 11 - digit;

	while (digit <= 11)
	{
		switch(digit)
		{
			case 1: return 'A';
					break;
			case 2: return 'B';
					break;
			case 3:	return 'C';
					break;
			case 4: return 'D';
					break;
			case 5: return 'E';
					break;
			case 6: return 'F';
					break;
			case 7: return 'G';
					break;
			case 8: return 'H';
					break;
			case 9: return 'I';
					break;
			case 10:return 'Z';
					break;
			case 11:return 'J';
					break;
		}
	}
}

