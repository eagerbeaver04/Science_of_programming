# Calculator
## Calculator on C++ with parser and dll support

Commit history is on another repository https://github.com/eagerbeaver04/Calculator .
This project is calculator based on Shunting yard algorithm which produce Reverse Polish notation for input expression. 

## Base functions 
1. Addition - "+"
2. Substraction - "-"
3. Multiplication - "*"
4. Division - "/"

## Download dll files from plugins folder for some new functions
1. Pow - "^" 
2. Factorial - "!"
3. Sine - "sin"

## Example of input expression

Input: 
```
(4! - sin(3.25 + 4^(1+2!) - sin(2.12)) - 9/4) * 3.2
```

Output:
```
1. (4! - sin(3.25 + 4^(1+2!) - sin(2.12)) - 9/4) * 3.2
2. (0) = 4 ! = 24
3. (1) = 2 ! = 2
4. (2) = 1 + (1) = 3
5. (3) = 4 ^ (2) = 64
6. (4) = 3.25 + (3) = 67.25
7. (5) = sin 2.12 = 0.85294
8. (6) = (4) - (5) = 66.3971
9. (7) = sin (6) = -0.411057
10. (8) = (0) - (7) = 24.4111
11. (9) = 9 / 4 = 2.25
12. (10) = (8) - (9) = 22.1611
13. (11) = (10) * 3.2 = 70.9154
14. Result : (11) = 70.9154
```

## Examples of exceptions
```
Input: 2.5!
Output: 
1. (0) = Factorial is function for integer non-negative numbers

Input: (0-0.5)^0.5
Output: 
1. (0) = 0 - 0.500000 = -0.5
2. (1) = Negative number in a fractional power

Input: (0-3)!
Output:
1. (0) = 0 - 3 = -3
2. (1) = Factorial is function for integer non-negative numbers

Input: 1&3
Output:
1. Unavaliable operation: &

Input: (2+9
Output:
1. Error: parentheses mismatched

Input: (2+)
1. (0) = Error: insufficient arguments in expression
```