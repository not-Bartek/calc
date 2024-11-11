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
    if(n > m) return 1;
    else if(n < m) return -1;
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
            continue;
        } if(number[i] == '0') {
            number[i] = '\0';
            continue;
        } else break;
    } 
}

void print_number(char *number, int reversed) {
    /*Function printing number from char array used for testing*/
    int i = 0;
    if(reversed > 0) {
        /*Number written from end to beggining*/
        while(i < len(number)) {
            printf("%c", number[len(number) -1 - i]);
            i++;
        }
    }else {
        while(i < len(number)) {
            printf("%c", number[i]);
            i++;
        }
    }
    printf("\n");
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
    }else {
        while(i < len(number)) { /*Number written from begging to end*/
            if(number[i] == 48 && start == 0) { 
                i++;
                printf("%c, %d", number[i], start);
                continue;
            } else { /*Letter in systems that are bigger that decimal*/
                if(number[i] > 57) number[i] += 7;
                start = 1;
                fprintf(output, "%d ", number[i]);
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

char* create_reversed(char str_num[MAX_NUMBER]) {
    /*function which creates array of chars like given number but reversed and returns pointer to 
    allocated space in memory, allocates as many bytes as digits of the number*/
    char *ptr = calloc(len(str_num)+1, sizeof(*ptr));
    int i = 0;
    int n = len(str_num);
    while(i < n) {
        if(str_num[n - 1 - i] > 57) ptr[i] = str_num[n - 1 - i] - 7;
        else ptr[i] = str_num[n - 1 - i];
        i++;
    }
    ptr[len(str_num)] = '\0';
    return ptr;
}

int newline(char *result, int newline_streak, FILE *output) {
    /*function activated when first char is the newline sign, returns newline variable incremented
    and frees memory*/
    if(!newline_streak) {
        file_print(result, 1, output);
        if(result != NULL) {
            free(result);
            printf("freed result\n");
            result = NULL;
        }
    }
    newline_streak++;
    return newline_streak;
}

char find_operation(char first, int system[], char line[]) {
    /*function for finding actual operation, activated when current line is operation line 
    returns +, *, ^, *, /, %, z */
    char operation;
    int i=0, j=0;
    char sys1_str[2], sys2_str[2];
    if (first > 47 && first < 58) {
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
        /*dzialanie arytmetyczne*/
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
    return operation;
}


char * add(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n > m ? n : m;
    int i = 0;
    char *first_number2, *second_number2;
    int previous = 0;
    /*zwiekszanie rozmiaru first number 1 i 2 o 1 bajt*/
    first_number2 = (char *)malloc(bigger_n + 1);
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    second_number2 = (char *)malloc(bigger_n + 1);
    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    /*Dopisywanie zer na początku liczby i przepisywanie liczb*/
    for (i = 0; i < bigger_n + 1; i++) {
        if (i <  n) {
            first_number2[i] = first_number[i];
        } else {
            first_number2[i] = '0';
        }
    }
    for (i = 0; i < bigger_n + 1; i++) {
        if (i <  m) {
            second_number2[i] = second_number[i];
        } else {
            second_number2[i] = '0';
        }
    }
    /*Dodawanie*/
    for (i = 0; i < bigger_n + 1; i++) {
        int sum = (first_number2[i] - '0') + (second_number2[i] - '0') + previous;
        if (sum >= system) {
            first_number2[i] = (sum % system) + '0';
            previous = 1;
        } else {
            first_number2[i] = sum + '0';
            previous = 0;
        }
    }
    /*Usunięcie wiodących zer*/ 
    rem_0_rev(first_number2);
    /*Zwolnienie pamięci*/ 
    free(second_number2);
    first_number2[len(first_number2)] = '\0';
    return first_number2;
}

char * sub1(char *first, int system) {
    /*odejmowanie 1 od dowolnej liczby*/
    int n = len(first);
    int i = 0;
    int previous = 0;
    char *result;
    result = (char *)malloc(n);
    for(i=0; i < n; i++) {
        result[i] = first[i];
    }

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
    int sum = 0;
    int i = 0;
    if(system % 2 == 0) return ((num[0]-48) %2);
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
    int n = len(first), i=0, j=0;
    int previous = 0;
    char *wyn = calloc(n, sizeof(*wyn));

    if(system == 2) {
        /*system dwojkowy dzielenie na 2 <=> przesuniecie bitowe w prawo*/
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
                /*printf("if spelniony first[i] =%c previous=%d\t wyn[j]=%c\n",first[n - 1 - i], previous, wyn[j]);*/
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
    /*Usuniecie wiodacych zer*/
    rem_0_rev(wyn);
    wyn[len(wyn)] = '\0';
    return wyn;
}

char * mul(char *first_number, char* second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n + m;
    int i = 0, j=0, multiply, previous = 0;
    char *first_number2, *second_number2, *result;
    /*alokowanie pamięci */
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
    /*Dopisywanie zer na początku liczby i przepisywanie liczb*/
    
    for (i = 0; i < bigger_n; i++) {
        result[i] = '0';
    }
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
    /*Usunięcie wiodących zer*/
    rem_0_rev(result);
    /*zwalnienie pamięci*/
    free(first_number2);
    free(second_number2);
    result[len(result)] = '\0';
    return result;
}

char * division(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    char *low, *high, *result, *multiplicated, *summed, *max_first, *x, *y=NULL;
    int new_n = n - m + 1;
    int i = 0, j = 0;
    printf("%d", j);
    /*pierwsza mniejsza od drugiej*/
    if(compare(first_number, second_number) < 0) {
        result = create("0");
        return result;
    }
    if(compare(second_number, "0") == 0) {
        result = create_reversed("NIE DZIEL PRZEZ ZERO CHOLERO");
        return result;
    }
    if(compare(second_number, "1") == 0) {
        result = create(first_number);
        return result;
    }
    if(compare(second_number, "2") == 0) {
        result = div_2(first_number, system);
        return result;
    }
    /*alokowanie result, high i low*/
    result = (char *)malloc(new_n);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    high = (char *)malloc(new_n);
    if (high == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
    low = (char *)malloc(new_n);
    if (low == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        free(high);
        return NULL;
    }

    /* inicjowanie result, high i low*/
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
    for (i = 0; i < new_n; i++) {
        if(i == 0) {
            result[new_n-1 - i] = system/2 + 48;
            high[new_n-1 - i] = system - 1 + 48;
        } else if(i==1) {
            result[new_n-1 - i] = '0';
            high[new_n-1 - i] = system - 1 + 48;
        }
        else {
            result[new_n -1- i] = '0';
            high[new_n -1- i] = system - 1 + 48;
        }
    }
    
    printf("result: ");
    print_number(result, 1);
    printf("high: ");
    print_number(high, 1);
    printf("low: ");
    print_number(low, 1);

    /*dzielenie (bin search)*/
    multiplicated = mul(result, second_number, system);
    printf("multiplicated: ");
    print_number(multiplicated, 1);
    max_first = add(first_number, second_number, system);
    printf("max_first: ");
    print_number(max_first, 1);
    j=0;
    while(!(compare(multiplicated, first_number) >= 0 && compare(multiplicated, max_first) < 0))
    {
        if(j>= 40) break;
        if(compare(multiplicated, first_number) > 0) {
            high = result;
        } else {
            low = result;
        }
        summed = add(high, low, system);
        result = div_2(summed, system);
        printf("result: ");
        print_number(result, 1);
        printf("second_number: ");
        print_number(second_number, 1);

        multiplicated = mul(result, second_number, system);
        free(summed);
        printf("multiplicated przed usunieciem zer: ");
        print_number(multiplicated, 1);
        /*Usuniecie zer*/
        rem_0_rev(multiplicated);
        rem_0_rev(result);
        j++;
    }
    if(multiplicated != NULL) free(multiplicated);
    /*sprawdzenie czy wynik jest za duzy*/
    multiplicated = mul(result, second_number, system);
    if(compare(multiplicated, first_number) > 0) {
        x = sub1(result, system);
        multiplicated = mul(x, second_number, system);
        if(compare(multiplicated, first_number) >= 0 && compare(multiplicated, max_first)){
            y = sub1(x, system);
            free(multiplicated);
            multiplicated = mul(y, second_number, system);
            if(compare(multiplicated, first_number) >= 0 && compare(multiplicated, max_first)) {
                free(result);
                free(x);
                result = y;
            }
        } else {
            if(y != NULL) free(y);
            free(result);
            result = x;
        }
    }
    /*Usuniecie zer*/
    rem_0_rev(result);
    /*zwalnianie pamięci*/
    if(multiplicated != NULL) free(multiplicated);
    if(max_first != NULL) free(max_first);
    if(high != NULL) free(high);
    if(low != NULL) free(low);
    result[len(result)] = '\0';
    return result;
}

char * power(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int new_n = n * pow(system, m);
    int i = 0;
    char *result, *exponent=NULL, *x, *y;
    int *mod = calloc((pow(system, m)), sizeof(*mod));
    /*alokowanie pamięci */
    rem_0_rev(second_number);
    exponent = create(second_number);
    if(exponent == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    result = (char *)malloc(new_n);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    /*usuniecie zer*/
    rem_0_rev(exponent);
    /*exp = 0*/
    if(compare(exponent, "0") == 0) {
        if(result != NULL) free(result);
        result= create("1");
        free(exponent);
        free(mod);
        return result;
    }
    if(compare(exponent, "1") == 0) {
        if(result != NULL) free(result);
        result = create(first_number);
        if(exponent != NULL) free(exponent);
        return result;
    }
    /*petla w dol*/
    for(i=0; i < n; i++) {
        result[i] = first_number[i];
    }
    i=0;
    while(compare(exponent, "1") > 0) {
        if(mod_2(exponent, system) == 0) {
            mod[i] = 0;
            x = div_2(exponent, system);
            free(exponent);
            exponent = x;
            x = NULL;
            i++;
        } else {
            mod[i] = 1;
            x = div_2(exponent, system);
            free(exponent);
            exponent = x;
            x = NULL;
            i++;
        }
    }
    i--; /*petla w gore*/
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
    free(exponent);
    free(mod);
    result[len(result)] = '\0';
    return result;
}
char *sub(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int new_n = max(n, m);
    int i = 0;
    char *first_number2, *second_number2, *result=NULL;
    int previous = 0;
    if(compare(first_number, second_number) < 0) {
        result = create_reversed("NIE MOZNA ODEJMOWAC WIEKSZEJ LICZBY OD MNIEJSZEJ");
        return result;
    }
    if(compare(first_number, second_number) == 0) {
        result = create_reversed("0");
        return result;
    }
    /*alokowanie pamięci */
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
    /*przepisywanie liczb*/
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
    /*odejmowanie*/
    for (i = 0; i < new_n; i++) {
        int sub = (first_number2[i] - '0') - (second_number2[i] - '0') + previous;
        printf("sub=%d\n", sub);
        if (sub < 0) {
            first_number2[i] = (sub + system) + '0';
            previous = -1;
            printf("first_number2[i]=%c\n", first_number2[i]);
        } else {
            first_number2[i] = sub + '0';
            previous = 0;
            printf("first_number2[i]=%c\n", first_number2[i]);
        }
    }
    result = first_number2;
    /*Usuniecie zer*/
    rem_0_rev(result);
    /*zwalnianie pamięci*/
    free(second_number2);
    result[len(result)] = '\0';
    return result;
}
char * modulo(char *first_number, char *second_number, int system) {
    char *result = division(first_number, second_number, system), *x;
    x = mul(result, second_number, system);
    free(result);
    result = sub(first_number, x, system);
    free(x);
    return result;
}
char * increment(char *iterator) {
    int n = len(iterator);
    int i = 0;
    int previous = 1;
    char * result;
    result = (char *)malloc(n+1);
    if(result == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for(i = 0; i < n+1; i++) {
        if(i < n) {
            result[i] = iterator[i];
        } else {
            result[i] = '0';
        }
    }
    printf("INCREMENT\n");
    printf("iterator: ");
    print_number(iterator, 1);
    for(i=0; i < n+1; i++) {
        if(result[i] + previous > '9') {
            printf("iterator[i]=%c\n", result[i]);
            result[i] = '0';
            previous = 1;
        } else {
            printf("iterator[i]=%c\n", result[i]);
            result[i] = result[i] + previous;
            previous = 0;
            break;
        }
    }
    printf("iterator: ");
    print_number(result, 1);
    free(iterator);
    return result;
}
char * sys_to_string(int system) {
    char *result = (char *)malloc(2);
    if(result == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    if(system < 10) {
        result[0] = system + 48;
    } else {
        result[0] = (system % 10) + 48;
        result[1] = (system / 10) + 48;
    }
    return result;
}

char * to_decimal(char *first_number, int system) {
    int n = len(first_number);
    int i = 0, new_n =2 * n, decimal = 10; /*2 ≥ log_10(16)*/
    char *result = (char *)malloc(new_n),*powered, *y, *x, *iterator, *sys, *string_current;
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for(i=0; i < new_n; i++) {
        result[i] = '0';
    }
    
    iterator = malloc(n);
    if(iterator == NULL) {
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
    for(i=0; i < n; i++) {
        iterator[i] = '0';
    }
    sys = sys_to_string(system);
    printf("sys: ");
    print_number(sys, 1);
    for(i=0; i < n; i++) {
        /*potegowanie system ^ i*/
        printf("i=%d\n", i);
        printf("iterator: ");
        print_number(iterator, 1);
        
        powered = power(sys, iterator, decimal);
        printf("powered: ");
        print_number(powered, 1);
        /*x = mul(first[i], powered)*/
        printf("first_number[i]=%c\n", first_number[i]);
        string_current = (char *)malloc(3);
        if(string_current == NULL) {
            printf("UNABLE TO ALLOCATE MEMORY");
            free(result);
            free(iterator);
            free(powered);
            return NULL;
        }

        if(first_number[0] > '9') {
            string_current[0] = (first_number[i]-48) % 10 + 48;
            string_current[1] = (first_number[i]-48) / 10 + 48;        
            string_current[2] = '\0';
        } else {
            string_current[0] = first_number[i];
            string_current[1] = '\0';
            string_current[2] = '\0';
        }
        
        /*zamienienie cyfry na liczbe dziesietna*/
        printf("string_current: ");
        print_number(string_current, 1);
        x = mul(string_current, powered, decimal);
        printf("x: ");
        print_number(x, 1);
        /*y = add(result, x)*/
        printf("result: ");
        print_number(result, 1);
        y = add(result, x, decimal);
        printf("y: ");
        print_number(y, 1);
        /*result = y*/
        result = y;
        /*zwalnianie zmiennych*/
        free(powered);
        printf("freed powered\n");
        free(x);
        printf("freed x\n");
        free(string_current);
        printf("freed current\n");
        /*iterator++*/
        printf("result: ");
        print_number(result, 1);
        iterator = increment(iterator);
        printf("iterator: ");
        print_number(iterator, 1);
    }
    /*Usuniecie zer*/
    rem_0_rev(result);
    /*zwalnianie pamięci*/
    free(iterator);
    free(sys);

    printf("RESULT DECIMAL:");
    print_number(result, 1);
    return result;
}

char * from_decimal(char *first_number, int system) {
    int n = len(first_number);
    int i = 0, new_n =4 * n, decimal = 10; /*4 ≥ log_2(10)*/
    char *result = (char *)malloc(new_n), *first_number2, *sys, *x;
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for(i=0; i < new_n; i++) {
        result[i] = '0';
    }
    first_number2 = create(first_number);
    i = 0;
    sys = sys_to_string(system);
    printf("sys: ");
    print_number(sys, 1);
    do {
        printf("i=%d\n", i);
        printf("first_number2: ");
        print_number(first_number2, 1);
        printf("sys: ");
        print_number(sys, 1);
        x = modulo(first_number2, sys, decimal);
        printf("x: ");
        print_number(x, 1);
        if(len(x) > 1) {
            result[i] = ((x[1]-48) * 10) + x[0]-48 + 48;
        } else {
            result[i] = x[0];
        }
        printf("result[i]=%c\n", result[i]);
        printf("result: ");
        print_number(result, 1);
        x = division(first_number2, sys,  decimal);
        free(first_number2);
        first_number2 = x;
        i++;
    } while(compare(first_number2, "0") > 0);
    /*Usuniecie zer*/
    rem_0_rev(result);
    /*zwalnianie*/
    free(first_number2);
    free(sys);

    return result;
}

char * arithmetics(char *first_number, char *second_number, char operation, int system[]) {
    char * result=NULL, *x;
    if(operation == '+')  result = add(first_number, second_number, system[0]);
    else if(operation == '*') result = mul(first_number, second_number, system[0]);
    else if(operation == '^') result = power(first_number, second_number, system[0]);
    else if(operation == '/') result = division(first_number, second_number, system[0]);
    else if(operation == '%') result = modulo(first_number, second_number, system[0]);
    else if(operation == '-') result = sub(first_number, second_number, system[0]);
    else if(operation == 'z') {
        printf("zamiana");
        result = to_decimal(first_number, system[0]);
        x = first_number;
        printf("x: ");
        print_number(x, 1);
    }
    else if(operation == 'D') {
        result = div_2(first_number, system[0]);
    }
    else if(operation == 'M') {
        result = div_2(first_number, system[0]);
        printf("first number: ");
        print_number(first_number, 1);
        printf(mod_2(first_number, system[0]) == 1 ? "nieparzysta\n" : "parzysta\n");
    }
    return result;
}

void calculate(char INPUT[40], char output[40]) {
    /*głowna funkcja programu czytająca plik i wpisująca wyniki do pliku*/
    FILE *ptr_in;
    FILE *ptr_out;
    char *first_number, *second_number, *result=NULL;
    int newline_streak = 3, number_streak = 0;
    char operation;
    int systems[2]; 
    char line[MAX_NUMBER];
    double delta;
    time_t starts, ends;
    systems[0] = 0;
    systems[1] = 0;
    /*otwieranie pliku*/
    ptr_in = fopen(INPUT, "r");
    ptr_out = fopen(output, "w");
    /*glowna petla funkcji*/
    while(fgets(line, MAX_NUMBER, ptr_in)) {
        if(line[0] == '\n') {
            newline_streak = newline(result, newline_streak, ptr_out);
            ends = time(NULL);
            delta = (double)ends - starts;
            printf("czas operacji: %f\n", delta);
        } else {
            /*linijka operacji - zapisanie operacji i systemu lub systemu i systemu docelowego*/
            if(newline_streak > 0) {
                starts = time(NULL);
                operation = find_operation(line[0], systems, line);
                printf("operation=%c, system=%d, ew. system 2 = %d\n", operation, systems[0], systems[1]);
                newline_streak = 0;
                number_streak = 0;
                fprintf(ptr_out, "%s", line);
            }
            /*pierwsza liczba */
            else if(newline_streak == 0 && number_streak == 0) {
                first_number = create_reversed(line);
                rem_0_rev(first_number);
                printf("first_number reversed: ");
                print_number(first_number, 1);
                number_streak++;
                fprintf(ptr_out, "%s", line);
                if(operation == 'z') {
                    result = arithmetics(first_number, NULL, operation, systems);
                    free(first_number);
                    printf("freed first_number\n");
                    number_streak++;
                }

            /*kolejna liczba */
            } else if(newline_streak == 0 && number_streak > 0) {
                second_number = create_reversed(line);
                rem_0_rev(second_number);
                printf("second_number reversed: ");
                print_number(second_number, 1);
                fprintf(ptr_out, "%s", line);
                result = arithmetics(first_number, second_number, operation, systems);

                free(first_number);
                printf("freed first_number\n");
                free(second_number);
                second_number = NULL;
                printf("freed second_number\n");
                first_number = result;
                number_streak++;
            }
        }
    }
    
    /*wypisanie na koniec*/
    if(result != NULL) {
        fprintf(ptr_out, "\n");
        file_print(result, 1, ptr_out);
        ends = time(NULL);
        delta = (double)ends - starts;
        printf("czas operacji: %f\n", delta);
        result = NULL;
        printf("freed result\n");
    }
    fclose(ptr_in);
    fclose(ptr_out);
}

int main(void) {
    calculate("small_input.txt", "out.txt");
    return 0;
}
