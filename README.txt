# IntCalc
string read calculator

RULES:
No negative numbers at any point in the equation for anyhting but Version 2
All fractions and division must have denominators and numerators grouped by parentheses
   and must themselves be surrounded by parentheses
No BIGInts
No decimals

Two test scripts are available, 

	user.testScript(); - Has 5 preset equations to test each operator and the order of operations.
			     This script was my final test after I would bugfix.
	user.smallTest(); -  A single equation script that can be used to rapidly test during development.
			     I used this to quickly test my changes.


__________________________________________________________________________________________
V1.2 - stable

The program first accepts a string input. 

It erases all spaces incase of user error.

It then steps through the string looking for the first lowest level '(' then finds the matching ')'.

The operation within these parentheses is then solved by stepping through this new equation looking
in order - for '^', '*' or '/', and '+' or '-'.

When it finds one of the operators, it assigns the values to the left and right and applies the 
operation. 

It then replaces the values and operator with the solution.

The program will then parse the new equation again. If there are no more operators, it will remove 
the parenthese.

Once all parentheses have been solved/removed, it will parse the equation until only a solution remains.
__________________________________________________________________________________________

Calc: comments/hours/lessons learned:

core code V1: 4hrs

problems:
	Used wrong overload of string.erase() - didnt include length so it deleted the rest of 
   	the string
 
testing - v1 - v2 8hrs: no negative, int only, no decimels
	-lessons learned: negative numbers will most likely be handled by flags and seperate 
   	 functions. do not include value inverters (A*= -1;) within the original setA 
	 function.

v1.1 - v1.2 5hrs: no negative, incorrect order of operations
	-lessons learned: */ and +- need to be searched left to right in order of apperance. 
   	 This lead to moving the parse loop to a wrapper that also recursively checks the 
	 equation.
	
v1.2 - 3hrs: no negative, tested stable, correct order of operations
	-lessons lerned: moving the loop control from solve() removed the need for flagging of
	 searches. lookFor* step through evolving currentEquation by self itarating.
