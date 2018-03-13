# IntCalc
string read calculator

RULES:
No negative numbers at any point in the equation for anyhting but Version 2
All fractions and division must have denominators and numerators grouped by parentheses
   and must themselves be surrounded by parentheses
No BIGInts
No decimals

__________________________________________________________________________________________
V1.2 - stable

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

v1.1 - v1.2 5hrs: no negative, test scripts usable, incorrect order of operations
	-lessons learned: */ and +- need to be searched left to right in order of apperance. 
   	 This lead to moving the parse loop to a wrapper that also recursively checks the 
	 equation.
	
v1.2 - 3hrs: no negative, tested stable, correct order of operations
	-lessons lerned: moving the loop control from solve() removed the need for flagging of
	 searches. lookFor* step through evolving currentEquation by self itarating.
