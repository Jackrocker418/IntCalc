# IntCalc
string read calculator

RULES:
No negative numbers at any point in the equation for anyhting but Version 2
All fractions and division must have denominators and numerators grouped by parentheses
   and must themselves be surrounded by parentheses
No BIGInts
No decimals

V1 is stable
V1p1 is stable but is messing up on order of operations
V2 not working - trying to implement negative number handling
__________________________________________________________________________________________
V1.1 - apply PEMDAS correctly (*/ or /* and +- or -+)
V2 - handle negative numbers without destroying

__________________________________________________________________________________________
Calc: comments/hours/lessons learned:

core code V1: 4hrs

problems:
	Used wrong overload of string.erase() - didnt include length so it deleted the rest of 
   the string
 
testing - v1 - v2 8hrs: no negative, int only, no decimels
	-lessons learned: negative numbers will most likely be handled by flags and seperate 
   functions. do not include value inverters (A*= -1;) within the original setA function;

v1.1 - v1.2 5hrs: no negative, fully usable, correct order of operations
	-lessons learned: */ and +- need to be searched left to right in order of apperance. 
   This lead to moving the parse loop to a wrapper that also recursively checks the equation.
