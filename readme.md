**
 * @file calc.c
 * @brief A simple calculator program.
 *
 * This program provides basic arithmetic operations such as addition,
 * subtraction, multiplication, and division. It takes input from the user
 * and performs the requested operation.
 *
 * Usage:
 * - Compile the program using a C compiler.
 * - Run the executable and follow the prompts to enter numbers and select
 *   an operation.
 *
 * Functions:
 * - int len(char string[MAX_NUMBER]): Returns the length of the string.
 * - int max(int a, int b): Returns the larger of two numbers.
 * - int compare(char *first, char *second): Compares two numbers written as strings.
 * - void rem_0_rev(char *number): Removes leading zeros from the number.
 * - void print_number(char *number, int reversed): Prints the number from a char array.
 * - void file_print(char *number, int reversed, FILE *output): Prints the number into a file.
 * - char* create(char str_num[MAX_NUMBER]): Creates an array of chars like the given number.
 * - char* create_reversed(char str_num[MAX_NUMBER]): Creates an array of chars like the given number but reversed.
 * - int newline(char *result, int newline_streak, FILE *output): Handles newline characters.
 * - char find_operation(char first, int system[], char line[]): Finds the actual operation.
 * - char* add(char *first_number, char *second_number, int system): Adds two numbers.
 * - char* sub1(char *first, int system): Subtracts 1 from a number.
 * - int mod_2(char *num, int system): Returns the modulus of the number by 2.
 * - char* div_2(char *first, int system): Divides the number by 2.
 * - char* mul(char *first_number, char* second_number, int system): Multiplies two numbers.
 * - char* division(char *first_number, char *second_number, int system): Divides two numbers.
 * - char* power(char *first_number, char *second_number, int system): Raises a number to the power of another number.
 * - char* sub(char *first_number, char *second_number, int system): Subtracts two numbers.
 * - char* modulo(char *first_number, char *second_number, int system): Returns the modulus of two numbers.
 * - char* increment(char *iterator): Increments a number.
 * - char* sys_to_string(int system): Converts a system to a string.
 * - char* to_decimal(char *first_number, int system): Converts a number to decimal.
 * - char* from_decimal(char *first_number, int system): Converts a number from decimal.
 * - char* arithmetics(char *first_number, char *second_number, char operation, int system[]): Performs arithmetic operations.
 * - void calculate(char INPUT[40], char output[40]): Main function that reads from a file and writes results to a file.
 *
 * Error Handling:
 * - The program checks for division by zero and prompts the user to enter
 *   a valid divisor.
 *
 * Example:
 * @code
 * Enter first number: 5
 * Enter second number: 3
 * Select operation (+, -, *, /): +
 * Result: 8
 * @endcode
 *
 * Function Descriptions:
 * - int len(char string[MAX_NUMBER]): This function returns the length of the string.
 * - int max(int a, int b): This function returns the larger of two numbers.
 * - int compare(char *first, char *second): This function compares two numbers written as strings.
 * - void rem_0_rev(char *number): This function removes leading zeros from the number.
 * - void print_number(char *number, int reversed): This function prints the number from a char array.
 * - void file_print(char *number, int reversed, FILE *output): This function prints the number into a file.
 * - char* create(char str_num[MAX_NUMBER]): This function creates an array of chars like the given number.
 * - char* create_reversed(char str_num[MAX_NUMBER]): This function creates an array of chars like the given number but reversed.
 * - int newline(char *result, int newline_streak, FILE *output): This function handles newline characters.
 * - char find_operation(char first, int system[], char line[]): This function finds the actual operation.
 * - char* add(char *first_number, char *second_number, int system): This function adds two numbers.
 * - char* sub1(char *first, int system): This function subtracts 1 from a number.
 * - int mod_2(char *num, int system): This function returns the modulus of the number by 2.
 * - char* div_2(char *first, int system): This function divides the number by 2.
 * - char* mul(char *first_number, char* second_number, int system): This function multiplies two numbers.
 * - char* division(char *first_number, char *second_number, int system): This function divides two numbers.
 * - char* power(char *first_number, char *second_number, int system): This function raises a number to the power of another number.
 * - char* sub(char *first_number, char *second_number, int system): This function subtracts two numbers.
 * - char* modulo(char *first_number, char *second_number, int system): This function returns the modulus of two numbers.
 * - char* increment(char *iterator): This function increments a number.
 * - char* sys_to_string(int system): This function converts a system to a string.
 * - char* to_decimal(char *first_number, int system): This function converts a number to decimal.
 * - char* from_decimal(char *first_number, int system): This function converts a number from decimal.
 * - char* arithmetics(char *first_number, char *second_number, char operation, int system[]): This function performs arithmetic operations.
 * - void calculate(char INPUT[40], char output[40]): This function reads from a file and writes results to a file.
 *
 * @date
   
