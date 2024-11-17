#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_NUMBER 1000000

int len(char string[MAX_NUMBER]) {
    /*Function that returns length of string (or number of digits)*/
    int i = 0;
    while(string[i] != '\0' && string[i] != '\n') i++;
    return i;
}

int max(int a, int b){
    /*Function that returns bigger number*/
    if (a>b) return a;
    else return b;
}

int compare(char *first, char *second) {
    /*Funtion that compares two numbers written as strings bigger first: 1,second: -1, equal: 0, */
    int n = len(first);
    int m = len(second);
    int i = 0;
    /*if one length is greater than another bigger number is obvious*/
    if(n > m) return 1;
    else if(n < m) return -1;
    /*else comparing every digit from left to right*/
    else {
        while(i < n) {
            if(first[n-1-i] > second[n-1-i]) return 1;
            else if(first[n-1-i] < second[n-1-i]) return -1;
            i++;
        }
    }
    return 0;
}
void rem_0_rev(char *number) {
    /*Functon which removes zeros from the beggining of the number*/
    int i = 0;
    for(i=len(number)-1; i >= 0; i--) {
        if(i==0 && number[i] == '0') {
            /*If all numbers are 0, changes the number to one digit zero*/
            number[0] = '0';
            number[1] = '\0';
            continue;
        } if(number[i] == '0') {
            number[i] = '\0';
            continue;
        } else break;
    } 
}

void file_print(char *number, int reversed, FILE *output) {
    /*Function that prints number into file*/
    int i = 0;
    int start = 0;
    if(reversed > 0) { /*Number written from end to beggining*/
        while(i < len(number)) {
            if(number[len(number) -1 - i] == 48 && start == 0){
                i++;
                continue;
            } else { /*Letter in systems that are bigger that decimal*/
                if(number[len(number) -1 - i] > 57) number[len(number) -1 - i] +=7;
                start = 1;
                fprintf(output, "%c", number[len(number) -1 - i]);
                i++;
            }
        }
        if(start == 0) fprintf(output, "0");
    }
    fprintf(output, "\n");
}

char* create(char str_num[MAX_NUMBER]) {
    /*function which creates array of chars like given number and returns pointer to 
    allocated space in memory, allocates as many bytes as digits of the number*/
    char *ptr = calloc(len(str_num)+1, sizeof(*ptr));
    int i = 0;
    while(i < len(str_num)) {
        if(str_num[i] > 57) ptr[i] = str_num[i]-7;
        else ptr[i] = str_num[i];
        i++;
    }
    ptr[len(str_num)] = '\0';
    return ptr;
}

char* create_reversed(char str_num[MAX_NUMBER], int system) {
    /*function which creates array of chars like given number but reversed and returns pointer to 
    allocated space in memory, allocates as many bytes as digits of the number and one more for '\0' */
    int i = 0;
    int n = len(str_num);
    char *ptr = calloc(n+1, sizeof(*ptr));
    if(ptr == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    while(i < n) {
        /*error control*/
        if(system < 11) {
            if(str_num[n - 1 - i] < 48 || str_num[n - 1 - i] > 48 + system - 1) {
                return NULL;
            }
        } else {
            if(str_num[n - 1 - i] > 96 && str_num[n - 1 - i] < 103) {
                /*Upper casing small letters*/
                str_num[n - 1 - i] = str_num[n - 1 - i] - 32;
            }
            if(str_num[n - 1 - i] < 48 || (str_num[n - 1 - i] > 57 && str_num[n - 1 - i] < 65) || str_num[n - 1 - i] > 65 + system - 11) {
                return NULL;
            }
        }
        if(str_num[n - 1 - i] > 57) ptr[i] = str_num[n - 1 - i] - 7;
        else ptr[i] = str_num[n - 1 - i];
        i++;
    }
    ptr[len(str_num)] = '\0';
    return ptr;
}

char find_operation(char first, int system[], char line[]) {
    /*function for finding actual operation, activated when current line is operation line 
    returns +, *, ^, *, /, %, z */
    char operation;
    int i=0, j=0, space = 0;
    char sys1_str[2], sys2_str[2];
    system[0] = 0;
    system[1] = 0;
    if(len(line) > 5) {
        return 1;
    }
    if (first > 47 && first < 58) {
        /*Checking if it's something other than systems*/
        space = 0;
        for(i = 0; i<len(line); i++) {
            if(line[i] == ' ') {
                space = 1;
            }
        }
        if(space == 0) {
            return 1;
        }
        i=0;
        operation = 'z';
        while(line[i] != ' ') {
            sys1_str[i] = line[i];
            i++;
        }
        i++;
        while(i < len(line)) {
            sys2_str[j] = line[i];
            j++;
            i++;
        }
        if(len(sys1_str) > 1) system[0]= (int)(sys1_str[0] - 48) * 10 +sys1_str[1] -48;
        else system[0] = (int)(sys1_str[0] -48);
        if(len(sys2_str) > 1) system[1]= (int)(sys2_str[0] - 48) * 10 +sys2_str[1] -48;
        else system[1] = (int)(sys2_str[0] -48);
    }else {
        /*arithmetic operation*/
        if(len(line) > 4) {
            return 1;
        }
        space = 0;
        for(i = 0; i<len(line); i++) {
            if(line[i] == ' ') {
                space = 1;
            }
        }
        if(space == 0) {
            return 1;
        }
        operation = first;
        i=2;
        while(i < len(line)) {
            sys1_str[j] = line[i];
            i++;
            j++;
        }
        if(j > 1) system[0]= (int)(sys1_str[0] - 48) * 10 +sys1_str[1] -48;
        else system[0] = (int)(sys1_str[0]- 48);
    }
    if(system[0] < 2 || system[0] > 16) return '\0';
    if(operation == 'z' && (system[1] < 2 || system[1] > 16)) return '\0';
    if(operation != 'z' && system[0] < 10 && len(line) > 3) return '\0';    
    if(operation == '+' || operation == '*' || operation == '^' || operation == '/' || operation == '%' || operation == 'z') return operation;
    else return '\0';
}

char * add(char *first_number, char *second_number, int system) {
    /*Function for finding the sum of two numbers returning pointer to the sum */
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n > m ? n : m;
    int i = 0;
    char *first_number2, *second_number2;
    int previous = 0;
    /*increasing the size of number by 1 byte*/
    first_number2 = (char *)malloc(bigger_n + 2);
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    second_number2 = (char *)malloc(bigger_n + 2);
    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    /*Writing zeros at the start of the numbers and rewriting numbers*/
    for (i = 0; i < bigger_n + 1; i++) {
        if (i <  n) {
            first_number2[i] = first_number[i];
        } else {
            first_number2[i] = '0';
        }
        if (i <  m) {
            second_number2[i] = second_number[i];
        } else {
            second_number2[i] = '0';
        }
    }
    second_number2[bigger_n + 1] = '\0';
    first_number2[bigger_n + 1] = '\0';
    /*Addition*/
    for (i = 0; i < bigger_n+1; i++) {
        int sum = (first_number2[i] - '0') + (second_number2[i] - '0') + previous;
        /*sum is bigger than system: carry = 1*/
        if (sum >= system) {
            first_number2[i] = (sum % system) + '0';
            previous = 1;
        } else {
            first_number2[i] = sum + '0';
            previous = 0;
        }
    }
    /*removing zeros from the start*/ 
    rem_0_rev(first_number2);
    /*Freeing memory*/ 
    free(second_number2);
    return first_number2;
}

char * sub1(char *first, int system) {
    /*Substracting one from any number*/
    int n = len(first);
    int i = 0;
    int previous = 0;
    char *result;
    /*Allocating memory and rewriting number*/
    result = (char *)malloc(n+1);
    for(i=0; i < n; i++) {
        result[i] = first[i];
    }
    result[n] = '\0';
    /*Substraction*/
    for(i=0; i < n; i++) {
        if(result[i] + previous <= '0') {
            result[i] = system - 1 + 48;
            previous = -1;
        } else {
            result[i] = result[i] + previous - 1;
            break;
        }
    }
    return result;
}

int mod_2(char *num, int system) {
    /*Function that returns modulo 2 of the number*/
    int sum = 0;
    int i = 0;
    /*If system is even then it's the modulo 2 of the last digit*/
    if(system % 2 == 0) return ((num[0]-48) %2);
    /*Else it's the modulo 2 of sum of digits*/
    else {
        while(i < len(num)) {
            if( (num[i]-48) % 2 == 1) {
                sum = (sum +1 ) % 2;
            }
            i++;
        }
        return sum % 2;
    }
}

char * div_2(char *first, int system) {
    /*Function that divides number by 2 (for binary system bitwise shift right)*/
    int n = len(first), i=0, j=0;
    int previous = 0;
    char *wyn = calloc(n+1, sizeof(*wyn));
    if(system == 2) {
        /*bitwise shift right*/
        for(i=n-1; i >=  0; i--) {
            if(i == n-1) {
                previous = first[i];
                wyn[i] = '0';
            } else {
                wyn[i] = previous;
                previous = first[i];
            }
        }
    }
    else {
        while(i < n) {
            /*Written division by 2*/
            if((previous + first[n - 1 - i] -48) < 2) {
                if(i == 0) {
                    previous = (first[n - 1 - i]-48) * system;
                    wyn[n - 1 - j] = 0;
                    i++;
                    j++;
                    continue;
                }
                previous = (first[n - 1 - i]-48) * system;
                wyn[n - 1 - j] = 48;
                i++;
                j++;
            } else {
                wyn[n - 1 - j] = ((previous + first[n - 1 - i]-48) / 2) + 48;
                previous = system * ((previous + first[n - 1 - i]-48) % 2);
                i++;
                j++;
            }
        }
    }
    wyn[n] = '\0';
    /*removing zeros*/
    rem_0_rev(wyn);
    return wyn;
}

char * mul(char *first_number, char* second_number, int system) {
    /*Function that multiplies two numbers*/
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n + m;
    int i = 0, j=0, multiply, previous = 0;
    char *first_number2, *second_number2, *result;
    /*Allocating memory*/
    first_number2 = (char *)calloc(bigger_n, sizeof(*first_number2));
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for (i = 0; i < bigger_n; i++) {
        if (i <  n) {
            first_number2[i] = first_number[i];
        } else {
            first_number2[i] = '0';
        }
    }
    second_number2 = (char *)calloc(bigger_n, sizeof(*second_number2));
    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    for (i = 0; i < bigger_n; i++) {
        if (i <  m) {
            second_number2[i] = second_number[i];
        } else {
            second_number2[i] = '0';
        }
    }
    result = (char *)calloc(bigger_n+1, sizeof(*result));
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        free(first_number2);
        free(second_number2);
        return NULL;
    }
    for (i = 0; i < bigger_n; i++) {
        result[i] = '0';
    }
    /*Multiplication like written multiplication algorithm*/
    for(i=0; i < bigger_n; i++) {
       for(j=0; j+i<bigger_n; j++) {
            multiply =  (first_number2[j] - 48) * (second_number2[i] - 48) + previous + (result[i+j]-48); 
            if(multiply >= system) {
                result[j+i] = (multiply % system) + 48;
                previous = multiply / system;
            } else {
                result[j+i] = multiply + 48;
                previous = 0;
            }
       }  
    }
    result[bigger_n] = '\0';
    /*Removing zeros*/
    rem_0_rev(result);
    /*Freeing memory*/
    free(first_number2);
    free(second_number2);
    return result;
}
char * division(char *first_number, char *second_number, int system) {
    /*Function that divides two numbers*/
    int n = len(first_number);
    int m = len(second_number);
    char *low, *high, *result, *multiplicated, *summed, *high_minus, *check, *check_multiplicated;
    int new_n = n - m + 1;
    int i = 0;
    /*Simple cases:*/
    /*First smaller than second*/
    if(compare(first_number, second_number) < 0) {
        result = create("0");
        return result;
    }
    /*Second equals zero*/
    if(compare(second_number, "0") == 0) {
        result = create("YTINIFNI");
        return result;
    }
    /*Second number equals one*/
    if(compare(second_number, "1") == 0) {
        result = create(first_number);
        return result;
    }
    /*Second number equals two - simplier, faster function*/
    if(compare(second_number, "2") == 0) {
        result = div_2(first_number, system);
        return result;
    }
    /*allocating result, high and low*/
    result = (char *)malloc(new_n+1);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    high = (char *)malloc(new_n+1);
    if (high == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
    low = (char *)malloc(new_n+1);
    if (low == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        free(high);
        return NULL;
    }
    /* initializing result, high and low*/
    /*low - 100... } n-m digits*/
    if(new_n == 1) {
        low[0] = '1';
    } else {
        for (i=0; i < new_n; i++) {
            if(i==1) {
                low[new_n-1 - i] = '1';
            } else {
                low[new_n-1 - i] = '0';
            }
        }
    }
    /*high - 999999... } n-m+1 digits, where 9 := system - 1*/
    for (i = 0; i < new_n; i++) {
        if(i == 0) {
            high[new_n-1 - i] = system - 1 + 48;
        } else if(i==1) {
            high[new_n-1 - i] = system - 1 + 48;
        }
        else {
            high[new_n -1- i] = system - 1 + 48;
        }
    }
    /*Null signs after numbers*/
    result[new_n] = '\0';
    high[new_n] = '\0';
    low[new_n] = '\0';
    rem_0_rev(high);
    rem_0_rev(low);

    /*Initial result := mean of high and low rounded down*/
    summed = add(high, low, system);
    result = div_2(summed, system);
    free(summed);
    /*multiplicated := result * second_number*/
    multiplicated = mul(result, second_number, system);
    high_minus = sub1(high, system);
    while(compare(low, high) < 0 && !(compare(result, high) == 0) && !(compare(result, low) == 0)) {
        if(compare(multiplicated, first_number) >= 0) {
            /*result is too high*/
            free(high);
            high = create(result);
        } else {
            /*result is too low*/
            free(low);
            low = create(result);
        }
        summed = add(high, low, system);
        result = div_2(summed, system);
        multiplicated = mul(result, second_number, system);

        high_minus = sub1(high, system);
        if(compare(low, high_minus) == 0) {
            summed = add(high, low, system);
            result = div_2(summed, system);
            free(summed);
            break;
        }
        free(summed);
        /*Removing zeros*/
        rem_0_rev(multiplicated);
        rem_0_rev(result);
    }
    rem_0_rev(result);
    if(multiplicated != NULL) free(multiplicated);
    multiplicated = mul(result, second_number, system);
    /*Are equal*/
    if(compare(multiplicated, first_number) == 0) {
        if(multiplicated != NULL) free(multiplicated);
        if(high != NULL) free(high);
        if(low != NULL) free(low);
        return result;
    }
    /*Checking if result is correct*/
    check = add(result, "1", system);
    rem_0_rev(check);
    check_multiplicated = mul(check, second_number, system);
    if(compare(check_multiplicated, first_number) <= 0) {
        if(multiplicated != NULL) free(multiplicated);
        if(high != NULL) free(high);
        if(low != NULL) free(low);
        if(check_multiplicated != NULL) free(check_multiplicated);
        return check;
    }
    /*Removing zeros*/
    rem_0_rev(result);
    /*Freeing memory*/
    if(multiplicated != NULL) free(multiplicated);
    if(high != NULL) free(high);
    if(low != NULL) free(low);
    return result;
}

char * power(char *first_number, char *second_number, int system) {
    /*Function that returns first_number to the power of second_number*/
    int n = len(first_number);
    int m = len(second_number);
    int new_n = n * pow(system, m);
    int i = 0;
    char *result, *exponent=NULL, *x, *y;
    int *mod = calloc((pow(system, m)), sizeof(*mod));
    /*Allocating memory */
    exponent = (char *)malloc(m+1);
    if (exponent == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    /*Rewriting second number*/
    rem_0_rev(second_number);
    rem_0_rev(first_number);
    for(i = 0; i < m; i++) {
        exponent[i] = second_number[i];
    }
    exponent[m] = '\0';
    if(exponent == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    result = (char *)malloc(new_n+1);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    result[new_n] = '\0';
    rem_0_rev(exponent);

    /*Simple cases*/
    /*0^0 = 1*/
    if(compare(exponent, "0") == 0) {
        if(result != NULL) free(result);
        result= create("1");
        free(exponent);
        free(mod);
        return result;
    }
    /*x^1 = x*/
    if(compare(exponent, "1") == 0) {
        if(result != NULL) free(result);
        result = create(first_number);
        if(exponent != NULL) free(exponent);
        return result;
    }
    for(i=0; i < n; i++) {
        result[i] = first_number[i];
    }
    i=0;
    /*Loop "down"*/
    while(compare(exponent, "1") > 0) {
        if(mod_2(exponent, system) == 0) {
            /*If exponent is even*/
            mod[i] = 0;
            x = div_2(exponent, system);
            free(exponent);
            exponent = x;
            x = NULL;
            i++;
        } else {
            /*If exponent is odd*/
            mod[i] = 1;
            x = div_2(exponent, system);
            free(exponent);
            exponent = x;
            x = NULL;
            i++;
        }
    }
    i--;
    /*Loop "up"*/
    while(i >= 0) {
        if(mod[i] == 0) {
            x = mul(result, result, system);
            if(result != NULL) free(result);
            result = x;
            i--;
        } else {
            x = mul(result, result, system);
            y = mul(first_number, x, system);
            if(result != NULL) free(result);
            if(x != NULL) free(x);
            result = y;
            i--;
        }
        rem_0_rev(result);
    }
    /*Freeing memory*/
    free(exponent);
    free(mod);
    return result;
}
char *sub(char *first_number, char *second_number, int system) {
    /*Function that substracts two numbers used in modulo function*/
    int n = len(first_number);
    int m = len(second_number);
    int new_n = max(n, m);
    int i = 0;
    char *first_number2, *second_number2, *result=NULL;
    int previous = 0;
    /*error handling*/
    if(compare(first_number, second_number) < 0) {
        result = create_reversed("NIE MOZNA ODEJMOWAC WIEKSZEJ LICZBY OD MNIEJSZEJ", system);
        return result;
    }
    /*Numbers equal*/
    if(compare(first_number, second_number) == 0) {
        result = create_reversed("0", system);
        return result;
    }
    /*Allocating memory*/
    first_number2 = (char *)malloc(new_n);
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    second_number2 = (char *)malloc(new_n);
    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    /*Rewriting numbers*/
    for (i = 0; i < new_n; i++) {
        if (i <  n) {
            first_number2[i] = first_number[i];
        } else {
            first_number2[i] = '0';
        }
    }
    for (i = 0; i < new_n; i++) {
        if (i <  m) {
            second_number2[i] = second_number[i];
        } else {
            second_number2[i] = '0';
        }
    }
    /*Substraction*/
    for (i = 0; i < new_n; i++) {
        int sub = (first_number2[i] - '0') - (second_number2[i] - '0') + previous;
        if (sub < 0) {
            first_number2[i] = (sub + system) + '0';
            previous = -1;
        } else {
            first_number2[i] = sub + '0';
            previous = 0;
        }
    }
    result = first_number2;
    /*Removing zeros*/
    rem_0_rev(result);
    /*Freeing memory*/
    free(second_number2);
    return result;
}
char * modulo(char *first_number, char *second_number, int system) {
    /*Function that returns modulo of two numbers*/
    char *result = division(first_number, second_number, system), *x;
    x = mul(result, second_number, system);
    free(result);
    result = sub(first_number, x, system);
    free(x);
    return result;
}
char * increment(char *iterator) {
    /*Function that increments number by one used in changing systems functions*/
    int n = len(iterator);
    int i = 0;
    int previous = 1;
    char * result;
    result = (char *)malloc(n+1);
    if(result == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    /*Rewriting number*/
    for(i = 0; i < n+1; i++) {
        if(i < n) {
            result[i] = iterator[i];
        } else {
            result[i] = '0';
        }
    }
    result[n+1] = '\0';
    /*Incrementation*/
    for(i=0; i < n+1; i++) {
        if(result[i] + previous > '9') {
            result[i] = '0';
            previous = 1;
        } else {
            result[i] = result[i] + previous;
            previous = 0;
            break;
        }
    }
    /*Removing zeros*/
    rem_0_rev(result);
    free(iterator);
    return result;
}
char * sys_to_string(int system) {
    /*Function that returns system as string*/
    char *result = (char *)malloc(3);
    if(result == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    /*If system is smaller than 10, then it's one digit*/
    if(system < 10) {
        result[0] = system + 48;
        result[1] = '\0';
        result[2] = '\0';
    } else {
        result[0] = (system % 10) + 48;
        result[1] = (system / 10) + 48;
        result[2] = '\0';
    }
    return result;
}

char * to_decimal(char *first_number, int system) {
    /*Function that changes number from any system to decimal*/
    int n = len(first_number);
    int i = 0, new_n =2 * n, decimal = 10; /*2 ≥ log_10(16)*/
    char *result,*powered, *y, *x, *iterator, *sys, *string_current;
    /*Allocating memory and rewriting number*/
    result = (char *)malloc(new_n+1);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for(i=0; i < new_n; i++) {
        result[i] = '0';
    }
    result[new_n] = '\0';
    iterator = malloc(n+1);
    if(iterator == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
    for(i=0; i < n; i++) {
        iterator[i] = '0';
    }
    iterator[n] = '\0';
    /*Changing system to string*/
    sys = sys_to_string(system);

    for(i=0; i < n; i++) {
        rem_0_rev(iterator);
        /*system ^ i*/
        rem_0_rev(iterator);
        powered = power(sys, iterator, 10);
        string_current = (char *)malloc(3);
        if(string_current == NULL) {
            printf("UNABLE TO ALLOCATE MEMORY");
            free(result);
            free(iterator);
            free(powered);
            return NULL;
        }
        /*Multiplying by the digit of the number, two cases for system > 10 and ≤ 10*/
        if(first_number[0] > '9') {
            string_current[0] = (first_number[i]-48) % 10 + 48;
            string_current[1] = (first_number[i]-48) / 10 + 48;        
            string_current[2] = '\0';
        } else {
            string_current[0] = first_number[i];
            string_current[1] = '\0';
            string_current[2] = '\0';
        }
        
        x = mul(string_current, powered, decimal);
        y = add(result, x, decimal);
        free(result);
        result = y;
        /*freeing memory*/
        free(powered);
        free(x);
        free(string_current);
        /*iterator++*/
        iterator = increment(iterator);
    }
    /*removing zeros*/
    rem_0_rev(result);
    /*Freeing memory*/
    free(iterator);
    free(sys);
    return result;
}

char * from_decimal(char *first_number, int system) {
    /*Function that changes number from decimal to any system*/
    int n = len(first_number);
    int i = 0, new_n =4 * n, decimal = 10; /*4 ≥ log_2(10)*/
    char *result, *first_number2, *sys, *x;
    /*Allocating memory and rewriting number*/
    result = (char *)malloc(new_n+1);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for(i=0; i < new_n; i++) {
        result[i] = '0';
    }
    result[new_n] = '\0';
    first_number2 = create(first_number);
    i = 0;
    /*Changing system to string*/
    sys = sys_to_string(system);
    do {
        x = modulo(first_number2, sys, decimal);
        if(len(x) > 1) {
            result[i] = ((x[1]-48) * 10) + x[0]-48 + 48;
        } else {
            result[i] = x[0];
        }
        x = division(first_number2, sys,  decimal);
        free(first_number2);
        first_number2 = x;
        i++;
    } while(compare(first_number2, "0") > 0);
    /*Removing zeros*/
    rem_0_rev(result);
    /*Freeing memory*/
    free(first_number2);
    free(sys);
    return result;
}

char * arithmetics(char *first_number, char *second_number, char operation, int system[]) {
    /*Function that returns result of arithmetic operation*/
    char * result=NULL, *x;
    if(operation == '+')  result = add(first_number, second_number, system[0]);
    else if(operation == '*') result = mul(first_number, second_number, system[0]);
    else if(operation == '^') result = power(first_number, second_number, system[0]);
    else if(operation == '/') result = division(first_number, second_number, system[0]);
    else if(operation == '%') result = modulo(first_number, second_number, system[0]);
    else if(operation == '-') result = sub(first_number, second_number, system[0]);
    else if(operation == 'z') {
        x = to_decimal(first_number, system[0]);
        result = from_decimal(x, system[1]);
    }
    return result;
}

void print_error(int error_code, FILE *output) {
    /*Function that prints error code*/
    switch(error_code) {
        case 1:
            fprintf(output, "Error code 1. Incorrect operation and system line.\n");
            break;
        case 2:
            fprintf(output, "Error code 2. Incorrect number.\n");
            break;
        case 404:
            fprintf(output, "Error code 404. Lonely number :( or too long operation line.\n");
            break;
        case 3:
            fprintf(output, "Error code 3. Incorrect file format\n\n");
            break;
        case 402:
            fprintf(output, "Error code 402. Where number??\n");
            break;
        default:
            break;
    }
}

void calculate(char INPUT[40], char output[40]) {
    /*Main function of the program that reads file and writes results to file*/
    FILE *ptr_in;
    FILE *ptr_out;
    char *first_number, *second_number, *result=NULL;
    int newline_streak = 3, number_streak = 0;
    char operation;
    int systems[2], error_code=0; 
    char line[MAX_NUMBER];
    double delta;
    time_t starts, ends;
    systems[0] = 0;
    systems[1] = 0;
    /*Opening files*/
    ptr_in = fopen(INPUT, "r");
    ptr_out = fopen(output, "w");
    starts = time(NULL);
    if(ptr_in == NULL) {
        fprintf(ptr_out, "Error code 8. Error opening file %s\n", INPUT);
        exit(1);
    }
    /*Main loop of the function*/
    while(fgets(line, MAX_NUMBER, ptr_in)) {
        if(line[0] == '\n') {
            /*newline*/
            if(newline_streak == 2 || newline_streak == 0) {
                fprintf(ptr_out, "\n");
                newline_streak++;
                continue;
            } else if(newline_streak == 1 && error_code == 0) {
                if(result ==NULL) {
                    /*No number error*/
                    error_code = 402;
                    print_error(error_code, ptr_out);
                    error_code = 0;
                    newline_streak++;
                    continue;
                }
                /*printing result*/
                file_print(result, 1, ptr_out);
                fprintf(ptr_out, "\n");
                if(result != NULL) {
                    free(result);
                    result = NULL;
                }
                newline_streak++;
            } else if(newline_streak == 1 && error_code != 0) {
                /*printing error*/
                print_error(error_code, ptr_out);
                error_code = 0;
                newline_streak++;
            }
        } else if(error_code != 0) {
            /*Printing line without doing operations*/
            newline_streak=0;
            fprintf(ptr_out, "%s", line);
            continue;
        } else if(line[0] != '\n' && newline_streak == 0){
            /*Numbers or number and operation written line after line*/
            error_code = 3;
            fprintf(ptr_out, "%s", line);
            continue;
        }else {
            /*Operation line - reading operation and system or two systems*/
            if(newline_streak > 1) {
                operation = find_operation(line[0], systems, line);
                /*Checking if it's number without operation*/
                if(operation == 1) {
                    error_code = 404;
                    newline_streak = 0;
                    number_streak = 0;
                    fprintf(ptr_out, "%s", line);
                    continue;
                }
                /*error code incorrect operation or system*/
                if(operation == '\0') {
                    error_code = 1;
                    newline_streak = 0;
                    number_streak = 0;
                    fprintf(ptr_out, "%s", line);
                    continue;
                }
                newline_streak = 0;
                number_streak = 0;
                fprintf(ptr_out, "%s", line);
            }
            /*First number in operation*/
            else if(newline_streak == 1 && number_streak == 0 && error_code == 0) {
                first_number = create_reversed(line, systems[0]);
                newline_streak=0;
                /*While creating checking if everything is ok*/
                /*If not first_number = NULL*/
                if(first_number == NULL) {
                    fprintf(ptr_out, "%s", line);
                    error_code = 2;
                    newline_streak = 0;
                    continue;
                }
                fprintf(ptr_out, "%s", line);
                /*removing zeros*/
                rem_0_rev(first_number);
                /*Incrementing number streak - next number is not first*/
                number_streak++;
                if(operation == 'z') {
                    /*If operation is changing system, then we don't need second number to do operation*/
                    result = arithmetics(first_number, NULL, operation, systems);
                    free(first_number);
                    number_streak++;
                }

            /*Second/Next number*/
            } else if(newline_streak == 1 && number_streak > 0 && error_code == 0) {
                second_number = create_reversed(line, systems[0]);
                newline_streak=0;
                /*While creating checking if everything is ok*/
                /*If not first_number = NULL*/
                if(second_number == NULL) {
                    fprintf(ptr_out, "%s", line);
                    error_code = 2;
                    newline_streak = 0;
                    continue;
                }
                rem_0_rev(second_number);
                fprintf(ptr_out, "%s", line);
                result = arithmetics(first_number, second_number, operation, systems);
                /*Freeing memory*/
                free(first_number);
                free(second_number);
                second_number = NULL;
                first_number = result;
                number_streak++;
            } 
        }
    }
    
    /*Printing at the end*/
    if(error_code != 0) {
        /*Printing error*/
        fprintf(ptr_out, "\n");
        print_error(error_code, ptr_out);
        error_code = 0;
        
    } else if(result != NULL) {
        /*Printing result if error_code = 0*/
        fprintf(ptr_out, "\n");
        fprintf(ptr_out, "\n");
        file_print(result, 1, ptr_out);
        result = NULL;
    }
    fclose(ptr_in);
    fclose(ptr_out);
    ends = time(NULL);
    delta = (double)ends - starts;
    printf("czas operacji: %f sekund\n", delta);
}

int main(int argc, char *argv[]) {
    char *input_file, *output_file;
    if (argc != 3) {
        printf("Correct run command ./calc <input_file> <output_file>\n");
        return 1;
    }

    input_file = argv[1];
    output_file = argv[2];

    calculate(input_file, output_file);
    return 0;
}
