# Calculator #
- - - -
## Quick Start ##
This program provides basic arithmetic operations for any length integer numbers
such as addition, multiplication, power, division, modulo and base change. It takes 
input file and saves results to the output file
## Implementation ##
- Compile the program using a C compiler in C89 standart
- Run the program with two arguments separeted by space
   - First argument: input file directory
   - Second argument: output file directory
- If there is no output file, program will create the file
- If there is no input file, program will print error 8

## Error Handling ##
Program handles some common errors returning error codes and messages:
- Error code 1. Incorrect operation and system line.
- Error code 2. Incorrect number.
- Error code 3. Incorrect file format for example numbers written line after line
- Error code 8. Error opening file
- Error code 402. No number after the operation
- Error code 404. No operation before number of only one number in two arguments operation
## Input Format ##
```
[operation] [system]

[first number]

[second number]



[operation] [system]

[first number]

[second number]

[third number]


[system 1] [system 2]

[number]
```
Operation signs
- \+ Addition
- \* Multiplication
- / Division
- ^ Powering
- % Modulo
## Example input file
```
+ 10

123

15



* 16

FF

1E
```
## Example output file
```
+ 10

123

15

138



* 16

FF

1E

1DE2

```
## Implementation
### General
Numbers are written from right to left (units digit is the first) as char arrays ended with null sign '\0' 
### Addition
Algorithm is based on basic written addition algorithm, numbers are aligned that unit digits are under each other and then digits added from end to the start from the nubmer with carry if sum is greater than system
### Multiplication
Algorithm is based on basic written multiplication algorithm - every digit is multiplicated with each other and added to the correct digit of the result, if the digit is greater than system carry is used
### Power
Algorithm is based on fast powering algorithm, dividing the exponent by two and saving modulos of two till it's equal zero, then based on the modulos array multiplicating result with itself 
### Division
Algorithm is based on binary search algorithm: searching the number which multiplicated by second number is the first number
### Modulo
Simple algorithm of int division the first number by second, then multiplication the result by second number and finally substracion first result from second result 
### Base change
Algorithm divided into two parts - first: base change from any to decimal, by multiplying the i-th digit by system to the power i, and second: base chagne from decimal to any, by doing modulo system and reading it from right to left.

## Functions 
### int len(char string[])
Description: Function that returns length of string (or number of digits)
Arguments: 
- char string[]: char array which length is unknown

### int max(int a, int b)
Description: Function that returns bigger number
Arguments: 
- int a: first number
- int b: second number

### int compare(char *first, char *second)
Description: Function that compares two numbers written as strings, bigger first: 1, second: -1, equal: 0
Arguments: 
- char *first: first string representing number
- char *second: second string representing number

### void rem_0_rev(char *number)
Description: Function which removes zeros from the beginning of the number
Arguments: 
- char *number: the string from which to remove zeros

### void file_print(char *number, int reversed, FILE *output)
Description: Function that prints number into file
Arguments: 
- char *number: string representing number
- int reversed: a flag specifying whether the number should be printed from end to beginning
- FILE *output: pointer to the file to which the number is to be printed

### char* create(char str_num[])
Description: Function which creates array of chars like given number and returns pointer to allocated space in memory
Arguments: 
- char str_num[]: string representing number

### char* create_reversed(char str_num[], int system)
Description: Function which creates array of chars like given number but reversed and returns pointer to allocated space in memory
Arguments: 
- char str_num[]: string representing number
- int system: system of the number

### char find_operation(char first, int system[], char line[])
Description: Function for finding actual operation, activated when current line is operation line
Arguments: 
- char first: first sign of the line
- int system[]: array with systems of the numbers
- char line[]: string holding line of the file

### char * add(char *first_number, char *second_number, int system)
Description: Function for finding the sum of two numbers returning pointer to the sum
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- int system: base of the numbers

### char * sub1(char *first, int system)
Description: Subtracting one from any number
Arguments: 
- char *first: string representing number
- int system: base of the numbers

### int mod_2(char *num, int system)
Description: Function that returns modulo 2 of the number
Arguments: 
- char *num: string representing number
- int system: base of the numbers

### char * div_2(char *first, int system)
Description: Function that divides number by 2 (for binary system bitwise shift right)
Arguments: 
- char *first: string representing number
- int system: base of the numbers

### char * mul(char *first_number, char* second_number, int system)
Description: Function that multiplies two numbers
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- int system: base of the numbers
  
### char * division(char *first_number, char *second_number, int system)
Description: Function that divides two numbers
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- int system: base of the numbers

### char * power(char *first_number, char *second_number, int system)
Description: Function that returns first_number to the power of second_number
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- int system: base of the numbers

### char * sub(char *first_number, char *second_number, int system)
Description: Function that subtracts two numbers used in modulo function
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- int system: base of the numbers

### char * modulo(char *first_number, char *second_number, int system)
Description: Function that returns modulo of two numbers
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- int system: base of the numbers

### char * increment(char *iterator)
Description: Function that increments number by one used in changing systems functions
Arguments: 
- char *iterator: string representing number

### char * sys_to_string(int system)
Description: Function that returns system as string
Arguments: 
- int system: system of the number

### char * to_decimal(char *first_number, int system)
Description: Function that changes number from any system to decimal
Arguments: 
- char *first_number: string representing number
- int system: original base of the number

### char * from_decimal(char *first_number, int system)
Description: Function that changes number from decimal to any system
Arguments: 
- char *first_number: string representing number
- int system: target base of the number

### char * arithmetics(char *first_number, char *second_number, char operation, int system[])
Description: Function that returns result of arithmetic operation
Arguments: 
- char *first_number: string representing number
- char *second_number: string representing number
- char operation: sign of the operation
- int system[]: array with systems

### void print_error(int error_code, FILE *output)
Description: Function that prints error code
Arguments: 
- int error_code: error code
- FILE *output: pointer to the file to print the error to

### void calculate(char INPUT[40], char output[40])
Description: Main function of the program that reads file and writes results to file
Arguments: 
- char INPUT[40]: input file name
- char output[40]: output file name

### int main(int argc, char *argv[])
Description: Main function that starts the program
Arguments: 
- char INPUT[40]: input file name
- char output[40]: output file name