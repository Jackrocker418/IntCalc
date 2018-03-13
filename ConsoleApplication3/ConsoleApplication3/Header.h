#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

class Calculator {
	// This class will take in a users expression as a string and return the computed value.

public:

	std::string equation;//where the users function/solution will be stored;

	std::string read(std::string userEquation) {
		// Reads in the users input and begins solving

		deBug("Read started");

		equation = userEquation;
		deleteSpaces();
		parseEquation(equation);
		finalNegative(equation);
		return equation;

		deBug("Read ended");
	}

	void deleteSpaces() {
		// Removes spaces from the user input
		
		deBug("delete spaces started");
		
		for (int i = 0; i <= equation.length(); i++) {
			if (equation[i] == ' ') {
				equation.erase(i,1);
			}
		}
		
		deBug("delete spaces ended");

	}

private:

	bool debug = true;
	int debugLimit = 2000;
	int debugCount = 0;

	void parseEquation(std::string& currentEquation) {
		// Applies order of operation to the string.

		deBug("parseEquation started");

		lookForParentheses(currentEquation);
		lookForExponents(currentEquation);
		lookForMultiplication(currentEquation);
		lookForDivision(currentEquation);
		lookForAddition(currentEquation); 
		lookForSubtraction(currentEquation);

		deBug("parseEquation ended");
	}

	void parseNewEquation(std::string& currentEquation) {
		// This is for solving sub equations in parentheses

		deBug("parseNewEquationStarted");

		lookForExponents(currentEquation);
		lookForMultiplication(currentEquation);
		lookForDivision(currentEquation);
		lookForAddition(currentEquation);
		lookForSubtraction(currentEquation);

		deBug("parseNewEquationEndded");
	}
	
	void lookForParentheses(std::string& currentEquation) {
		// Solves 'highest' level parentheses recursively and replaces with solved values until all parenthases are removed

		bool hasParenthases = false;
		int start=0, end=0;

		deBug("par started");

		for (int i = 0; i <= currentEquation.length();i++) {
			switch (currentEquation[i]){
			case '(':
				start = i;
				hasParenthases = true;
				break;
			case ')':
				if (hasParenthases == false) {
					std::cout << "missing one or more (";
					break;
				}
				end = i;
				newEquation(currentEquation, start, end);
				hasParenthases = false;
				break;
			default:
				deBug("not a par");
				break;
			}
		}

		deBug("par ended");
	}

	void lookForExponents(std::string& currentEquation) {
		// Passes through the equation until all '^' are solved and removed
		// can only handle single integer variables such as
		// (5^7) not (12^4 or 4^12)
		
		deBug("exp started");
		
		bool it;
		do {
			it = solve(currentEquation, '^');
			deBug("newEq=" + currentEquation);
		} while (it == true);
		
		deBug("exp ended");

	}

	void lookForMultiplication(std::string& currentEquation) {
		//Passes through the equation until all '*' are solved and removed
		
		deBug("* started");
		
		bool it;
		do {
			it = solve(currentEquation, '*');
			deBug("newEq=" + currentEquation);
		} while (it == true);
		
		deBug("* ended");

	}

	void lookForDivision(std::string& currentEquation) {
		// Passes through the equation until all '/' are solved and removed
		
		deBug("/ started");
		
		bool it;
		do {
			it = solve(currentEquation, '/');
			deBug("newEq=" + currentEquation);
		} while (it == true);
		
		deBug("/ ended");

	}

	void lookForAddition(std::string& currentEquation) {
		// Passes through the equation until all '+' are solved and removed
		
		deBug("+ started");
		
		bool it;
		do {
			it = solve(currentEquation, '+');
		} while (it == true);
		
		deBug("+ endded");

	}

	void lookForSubtraction(std::string& currentEquation)	{
		// Passes through the equation until all '-' are solved and removed
		
		deBug("- started");
		
		if (!negFirstNum(currentEquation)) {
			bool it;
			do {
				it = solve(currentEquation, '-');

				deBug("newEq=" + currentEquation);

			} while (it == true);
		}
		deBug("- ended");

	}

	bool negFirstNum(std::string& currentEquation) {
		int numOfSub = 0;
		bool skip = false;
		if (currentEquation[0] == '-') {
			// This searches the equation for any remaining subtractions

			for (int i = 0; i < currentEquation.length(); i++) {
				if (currentEquation[i] == '-') {
					numOfSub++;
				}
			}
			if (numOfSub == 1) {
				skip = true;
				return skip;
			}
		}
		else {
			skip = false;
			return skip;
		}
	}

	bool solve(std::string& currentEquation, char lookFor) {
		// Actually steps through the equation solving operator dependent on caller
		bool more = true, isNegative = false, secondCheck = false;
		double special;
		int replace;
		int a, b, sizeOfA, sizeOfB, start, end;
		std::string rep;
		
		deBug("solve started");
		
		for (int pos = 0; pos <= currentEquation.length(); pos++) {
			if (currentEquation[pos] == lookFor) {
				switch (lookFor) {
				case '^':
					setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
					special = pow(a, b);
					replace = floor(special + 0.5);
					isNegative = negativeCheck(replace);
					rep = std::to_string(replace);
					replaceMe(currentEquation, start, end, rep, isNegative);
					return more;
					break;
				case '*':
					setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
					replace = a * b;
					isNegative = negativeCheck(replace);
					rep = std::to_string(replace);
					replaceMe(currentEquation, start, end, rep, isNegative);
					return more;
					break;
				case '/':
					setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
					replace = a / b;
					isNegative = negativeCheck(replace);
					rep = std::to_string(replace);
					replaceMe(currentEquation, start, end, rep, isNegative);
					return more;
					break;
				case '+':
					setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
					replace = a + b;
					isNegative = negativeCheck(replace);
					rep = std::to_string(replace);
					replaceMe(currentEquation, start, end, rep, isNegative);
					return more;
					break;
				case '-':
					setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
					replace = a - b;
					isNegative = negativeCheck(replace);
					rep = std::to_string(replace);
					replaceMe(currentEquation, start, end, rep, isNegative);
					return more;
					break;
				default:
					more = false;
					return more;
					break;
				}
				
				deBug("solve ended");

			}
		}
	}
	
	void setAB(std::string currentEquation, int& A, int& B,int& sizeOfA, int& sizeOfB, int& start, int& end, int pos) {
		// Assigns A and B for operations and finds the size of the integers and maintains location in the equation
		// for replacement
		
		deBug("setAB started");
		
		sizeOfA = setA(currentEquation, A, pos);
		sizeOfB = setB(currentEquation, B, pos);
		start = pos - (sizeOfA);
		end = pos + (sizeOfB);
		
		deBug("setAB endded");

	}

	int setA(std::string currentEquation, int& A, int& pos){
		// Sets variable A to the value of the integer to the left of the operand
		
		deBug("setA start");

		A = 0;
		int numOfDigits = 0, run = pos - 1, retNum;
		if (pos == 0) {
			// This searches the equation for subtraction from back to from mitigating problems of leading negative numbers
			for (int i = 0; i < currentEquation.length(); i++) {
				if (currentEquation[i] == '-') {
					pos = i;
				}
			}
			run = pos - 1;
		}
		while (isdigit(currentEquation[run])) {
			// Counts the number of digits in the integer

			numOfDigits++;
			if (run != 0) {
				run--;
			}
			else {
				break;
			}
		}
		retNum = numOfDigits;
		for (numOfDigits; numOfDigits >= 1; numOfDigits--) {
			// Writes the number to A by multiplying A by 10 to make room for the next digit

			if (currentEquation[run] == '-') {
				run++;
				numOfDigits++;
			} else {
				A *= 10;
				int temp = (currentEquation[run] - '0');
				A += temp;
				run++;
			}
		}
		if (currentEquation[0] = '-') {
			A *= (-1);
		}

		deBug("setA end, A = ", A);
		
		return retNum;
	}

	int setB(std::string currentEquation, int& B, int pos) {
		// Sets the variable to the right of the operand
		
		deBug("setB start");
		
		B = 0;
		int numOfDigits = 0, run = pos + 1, retNum;
		while (isdigit(currentEquation[run])) {
			// Determins the number of digits of the number
			
			numOfDigits++;
			run++;
		}
		retNum = numOfDigits;
		run = pos + 1;
		for (numOfDigits; numOfDigits >= 1; numOfDigits--) {
			// Loads the number into B
		
			if (currentEquation[run] == '.') {
				cout << "I dont accept floats yet Line63/setAB" << endl;
				run++;
			}
			else {
			
				// Multiplies the left most place by 10 to the power of the number of digits in the integer
				// then adds it to B, is different to A because of how 'run' needs to 
				// increment forward instead of backward like in 'setA()'
				
				int temp = (currentEquation[run] - '0');
				temp *= (pow(10,numOfDigits - 1));
				B += temp;
				run++;
			}
		}
		deBug("B = ", B);
		
		deBug("setB end");
	
		return retNum;
	}

	bool negativeCheck(int result) {
		// Checks for negative values then flagging them

		deBug("negativeCheck Started");

		if (result < 0) {
			result *= (-1);
			
			deBug("negativeCheck ended True");
			
			return true;
		}
		else {
			
			deBug("negativeCheck ended False");

			return false;
		}
	}

	void replaceMe(std::string& currentEquation, int start, int end, std::string replace, bool isNegative) {
		// Replaces the original section of the equation with the result

		deBug("replaceMe started = ", currentEquation);

		if (isNegative) {
			deBug("start = ", start);
			deBug("end = ", end);
			deBug("rep = ", replace);
			currentEquation.erase(start, ((end + 1) - start));
			replace = "-" + replace;
			currentEquation.insert(start, replace);
		}
		else {
			currentEquation.erase(start, ((end + 1) - start));
			currentEquation.insert(start, replace);
		}
		finalNegative(currentEquation);
		deBug("replaceMe ended = ", currentEquation);

	}
	
	void newEquation(std::string& currentEquation, int start, int end) {
		// This splits up an equation with parentheses into the equations within the parentheses
		// it then replaces the local parentheses with the local solution until all parentheses are handled
		
		std::string newEq;
		bool isNegative = false;
		
		deBug("newEquation started");
		
		newEq.append(currentEquation, (start + 1), ((end - 1) - start));
		parseNewEquation(newEq);
		finalNegative(newEq);
		replaceMe(currentEquation, start, end, newEq, isNegative);
		parseEquation(currentEquation);
		
		deBug("newEquation ended");
	}

	void finalNegative(std::string& currentEquation) {
		// Erases any duplicate '-'

		deBug("finalNegative begin");
		int i = 0, numberOfNeg = 0;
		if (currentEquation[0] == '-') {
			if (currentEquation[1] == '-') {
				while (currentEquation[i] == '-') {
					numberOfNeg++;
					i++;
				}
				numberOfNeg--;
				currentEquation.erase(0, numberOfNeg);
			}	
		}
	

		deBug("finalNegative end");
	}

	void deBug(std::string message) {
		if (debugCount < debugLimit) {
			if (debug == true) {
				debugCount++;
				std::cout << message << ": count# " << debugCount << std::endl;
			}
		}
		else {
			system("PAUSE");
		}
	}

	void deBug(std::string message, int value) {
		if (debugCount < debugLimit) {
			if (debug == true) {
				debugCount++;
				std::cout << message << value << ": count# " << debugCount << std::endl;
			}
		}
		else {
			system("PAUSE");
		}
	}

	void deBug(std::string message, std::string equation) {
		if (debugCount < debugLimit) {
			if (debug == true) {
				debugCount++;
				std::cout << message << equation << ": count# " << debugCount << std::endl;
			}
		}
		else {
			system("PAUSE");
		}
	}
};

class UserInput {
	// User Interface class

public:

	void Begin() {
		start();
	}


private:

		Calculator  calc;
		char usersEntry[256];
		std::string usersEquation;
		char yN;
		bool first;

	void start() {
		// User interface
		
		if (!first) {
			getchar();
		}
		first = false;
		std::cout << "Please enter your equation using ( ) ^ * / + - as acceptable operators." << std::endl;
		std::cin.getline(usersEntry,256);
		usersEquation = usersEntry;
		//usersEquation = "-2-1";
		std::cout << "The answer is: " << calc.read(usersEquation) << std::endl;
		std::cout << "Would you like to solve another? (y/n)";
		std::cin >> yN;
		yesNo(yN);
	}

	void yesNo(char yN) {
		switch (yN) {
		case 'N':
			break;
		case 'n':
			break;
		default:
			start();
			getchar();
		}
	}

};