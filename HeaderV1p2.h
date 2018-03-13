/* Changes V1.2:
	solve no longer loops, those were passed above to the lookFor* functions
	
	lookFor* functions combined to simultaneously look for two operands

	original individual lookFor* now renamed to solveFor*
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

class Calculator {
	// This class will take in a users expression as a string and return the computed value.

public:

	std::string equation;// Where the users function/solution will be stored;

	std::string read(std::string userEquation) {
	// Reads in the users input and begins solving
		
		deBug("Read started");
		
		equation = userEquation;
		deleteSpaces();
		parseEquation(equation);
		return equation;
		
		deBug("Read ended");
	}

	void deleteSpaces() {
		// Removes spaces from the user input
		
		deBug("delete spaces started");
		
		for (int i = 0; i <= equation.length(); i++) {
			if (equation[i] == ' ') {
				equation.erase(i, 1);
			}
		}
		
		deBug("delete spaces ended");

	}

	void rules() {
		std::cout << "No negative numbers at any point in the equation for anyhting but Version 2" << std::endl;
		std::cout << "All fractions and division must have denominators and numerators grouped by parentheses" << std::endl;
		std::cout << "   and must themselves be surrounded by parentheses" << std::endl;
		std::cout << "No BIGInts" << std::endl;
		std::cout << "No decimals" << std::endl;
	}

private:

	bool debug = false;
	int debugLimit = 2000;
	int debugCount = 0;



	void parseEquation(std::string& currentEquation) {
		// Determines order of operation to the string.
		
		deBug("parseEquation started");
		lookForParentheses(currentEquation);
		lookForExponents(currentEquation);
		lookForMultiplicationDivision(currentEquation);
		lookForAdditionSubtraction(currentEquation);
		deBug("parseEquation ended");
	}

	void parseNewEquation(std::string& currentEquation) {
		// This is for solving sub equations in parentheses
		
		deBug("parseNewEquationStarted");
		
		lookForExponents(currentEquation);
		lookForMultiplicationDivision(currentEquation);
		lookForAdditionSubtraction(currentEquation);
		
		deBug("parseNewEquationEndded");
	}

	void lookForParentheses(std::string& currentEquation) {
		// Solves 'highest' level parentheses recursively and replaces with solved values until all Parentheses are removed
		
		bool hasParentheses = false;
		int start = 0, end = 0;
		
		deBug("par started");
		
		for (int i = 0; i <= currentEquation.length(); i++) {
			switch (currentEquation[i]) {
			case '(':
				start = i;
				hasParentheses = true;
				break;
			case ')':
				if (hasParentheses == false) {
					std::cout << "missing one or more (";
					break;
				}
				end = i;
				newEquation(currentEquation, start, end);
				hasParentheses = false;
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
		for (int i = 0; i < currentEquation.length(); i++) {
			bool it;
			do {
				it = solve(currentEquation, i, '^');
			} while (it == true);
		}
		
		deBug("exp ended");
	}

	void lookForMultiplicationDivision(std::string& currentEquation) {
		for (int i = 0; i < currentEquation.length(); i++) {
			switch (currentEquation[i]) {
			case '*':
				solveForMultiplication(currentEquation, i);
				lookForMultiplicationDivision(currentEquation);
				break;
			case '/':
				solveForDivision(currentEquation, i);
				lookForMultiplicationDivision(currentEquation);
				break;
			default:
				break;
			}
		}
	}

	void solveForMultiplication(std::string& currentEquation, int pos) {
		// solves the current '*' operator
		
		deBug("* started");
		
		bool it;
		do {
			it = solve(currentEquation, pos, '*');
		} while (it == true);
		
		deBug("* ended");
	}

	void solveForDivision(std::string& currentEquation, int pos) {
		// solves the current '/' operator
		
		deBug("/ started");
		
		bool it;
		do {
			it = solve(currentEquation, pos, '/');
		} while (it == true);
		
		deBug("/ ended");
	
	}

	void lookForAdditionSubtraction(std::string& currentEquation) {
		for (int i = 0; i < currentEquation.length(); i++) {
			switch (currentEquation[i]) {
			case '+':
				solveForAddition(currentEquation, i);
				lookForAdditionSubtraction(currentEquation);
				break;
			case '-':
				solveForSubtraction(currentEquation, i);
				lookForAdditionSubtraction(currentEquation);
				break;
			default:
				break;
			}
		}
	}

	void solveForAddition(std::string& currentEquation, int pos) {
		deBug("+ started");

		bool it;
		do {
			it = solve(currentEquation, pos, '+');
		} while (it == true);

		deBug("+ endded");
	}

	void solveForSubtraction(std::string& currentEquation, int pos) {
		deBug("- started");

		bool it;
		do {
			it = solve(currentEquation, pos, '-');
		} while (it == true);

		deBug("- ended");
	}

	bool solve(std::string& currentEquation, int pos, char lookFor) {
		// Actually steps through the equation solving operator dependent on caller
	
		bool more = true;
		double special;
		int replace;
		int a, b, sizeOfA, sizeOfB, start, end;
		std::string rep;
		
		deBug("solve started");
		
		if (currentEquation[pos] == lookFor) {
			switch (lookFor) {
			case '^':
				setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
				special = pow(a, b);
				replace = floor(special + 0.5);
				rep = std::to_string(replace);
				replaceMe(currentEquation, start, end, rep);
				return more;
				break;
			case '*':
				setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
				replace = a * b;
				rep = std::to_string(replace);
				replaceMe(currentEquation, start, end, rep);
				return more;
				break;
			case '/':
				setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
				replace = a / b;
				rep = std::to_string(replace);
				replaceMe(currentEquation, start, end, rep);
				return more;
				break;
			case '+':
				setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
				replace = a + b;
				rep = std::to_string(replace);
				replaceMe(currentEquation, start, end, rep);
				return more;
				break;
			case '-':
				setAB(currentEquation, a, b, sizeOfA, sizeOfB, start, end, pos);
				replace = a - b;
				rep = std::to_string(replace);
				replaceMe(currentEquation, start, end, rep);
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

	void setAB(std::string currentEquation, int& A, int& B, int& sizeOfA, int& sizeOfB, int& start, int& end, int pos) {
		// Assigns A and B for operations and finds the size of the integers and maintains location in the equation
		// for replacement
		
		deBug("setAB started");
		
		sizeOfA = setA(currentEquation, A, pos);
		sizeOfB = setB(currentEquation, B, pos);
		start = pos - (sizeOfA);
		end = pos + (sizeOfB);
		
		deBug("setAB endded");
	
	}

	int setA(std::string currentEquation, int& A, int pos) {
		// Sets variable A to the value of the integer to the left of the operand
	

// TODO: setA is malfunctioning when there is an operator to the left of the number (+2*16)

		deBug("setA start");
		
		A = 0;
		int numOfDigits = 0, run = pos - 1, retNum;
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
		while (!isdigit(currentEquation[run])) {
			run++;
		}
		for (numOfDigits; numOfDigits >= 1; numOfDigits--) {
			// Writes the number to A by multiplying A by 10 to make room for the next digit
			
			A *= 10;
			int temp = currentEquation[run] -'0';
			A += temp;
			run++;
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
			if (run != 0) {
				run++;
			}
			else {
				break;
			}
		}
		retNum = numOfDigits;
		run = pos + 1;
		for (numOfDigits; numOfDigits >= 1; numOfDigits--) {
			// Loads the number into B

			if (currentEquation[run] == '.') {
				deBug("I dont accept floats yet setB");
				run++;
			}
			else {
				// Multiplies the left most place by 10 to the power of the number of digits in the integer
				// then adds it to B, is different to A because of how 'run' needs to 
				// increment forward instead of backward like in 'setA()'

				int temp = (currentEquation[run] - '0');
				temp *= (pow(10, numOfDigits - 1));
				B += temp;
				run++;
			}
		}

		deBug("setB end, B =", B);

		return retNum;
	}

	void replaceMe(std::string& currentEquation, int start, int end, std::string replace) {
		// Replaces the original section of the equation with the result
		
		deBug("replaceMe start: ", currentEquation);
		
		currentEquation.erase(start, ((end + 1) - start));
		currentEquation.insert(start, replace);
		
		deBug("replaceMe end: ", currentEquation);

	}

	void newEquation(std::string& currentEquation, int start, int end) {
		// This splits up an equation with parentheses into the equations within the parentheses
		// it then replaces the local parentheses with the local solution until all parentheses are handled
		
		std::string newEq;
		
		deBug("newEquation started: ", currentEquation);
		
		newEq.append(currentEquation, (start + 1), ((end - 1) - start));
		parseNewEquation(newEq);
		replaceMe(currentEquation, start, end, newEq);
		parseEquation(currentEquation);
		
		deBug("newEquation ended: ", currentEquation);
	
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
public:

	void Begin() {
		start();
	}

	void testScript() {
		runTest();
	}

	void smallTest() {
		// Smaller test for deBug

		char choice;
		std::string eQ, solution;

		check();
		std::cout << "Smaller tests for deBug" << std::endl;
		std::cout << "(, ^, *, /, +, -, big" << std::endl;
		std::cin >> choice;
		switch (choice) {
		case '(':
			eQ = "((9+9)+(1+1))";
			solution = "20";
			break;
		case '^':
			eQ = "2^4+2";
			solution = "18";
			break;
		case '*':
			eQ = "9*5*1";
			solution = "45";
			break;
		case '/':
			eQ = "8/2 + 3/2";
			solution = "6 *because of floor()*";
			break;
		case '+':
			eQ = "1+2+3+4+5";
			solution = "15";
			break;
		case '-':
			eQ = "100-5+6-1";
			solution = "100";
		default:
			eQ = "(((18+2)-10)*10)/100+2^2";
			solution = "5";
			break;
		}
		std::cout << eQ << " = " << solution << std::endl;
		std::cout << "computed solution: " << calc.read(eQ) << std::endl;
		again();
	}


private:

	Calculator calc;
	char usersEntry[256];
	std::string usersEquation;
	char yN;
	bool first;

	void runTest() {
		// This is for testing purposes debug is not suggested use smallTest instead
		std::string eQ1 = "(((2000)+(2^2))+1)*5",
					eQ2 = "1+2+3+4+5-1",
					eQ3 = "1000-10+(8/2)*(4^(3-1))",
					eQ4 = "1000-(14+27)-2",
					eQ5 = "(1+2)+(3*4)+(5/5)";

		check();
		std::cout << "This is for testing purposes debug is not suggested use smallTest instead" << std::endl;
		std::cout << eQ1 << " = 10025" << std::endl;
		std::cout << "solution: " << calc.read(eQ1) << std::endl;
		std::cout << eQ2 << " = 14" << std::endl;
		std::cout << "solution: " << calc.read(eQ2) << std::endl;
		std::cout << eQ3 << " = 1054" << std::endl;
		std::cout << "solution: " << calc.read(eQ3) << std::endl;
		std::cout << eQ4 << " = 957" << std::endl;
		std::cout << "solution: " << calc.read(eQ4) << std::endl;
		std::cout << eQ5 << " = 16" << std::endl;
		std::cout << "solution: " << calc.read(eQ5) << std::endl;
		again();


	}

	void start() {
		check();
		std::cout << "Please enter your equation using ( ) ^ * / + - as acceptable operators" << std::endl 
					<< ", or RULES to see rules of calculator" << std::endl;
		std::cin.getline(usersEntry, 256);
		usersEquation = usersEntry;
		if (usersEquation == "RULES") {
			calc.rules();
		}
		else {
			std::cout << "The answer is: " << calc.read(usersEquation) << std::endl;
		}
		again();
	}

	void check() {
		if (!first) {
			getchar();
		}
		first = false;
	}

	void again() {
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