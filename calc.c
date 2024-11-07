#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_NUMBER 1000000


int len(char string[MAX_NUMBER]) {
    /*funkcja zwracajaca długość łańcucha znakow*/
    int i = 0;
    while(string[i] != '\0' && string[i] != '\n') i++;
    return i;
}
int max(int a, int b){
    if (a>b) return a;
    else return b;
}

int compare(char *first, char *second) {
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
/*function printing number from char array used for testing*/
void print_number(char *number, int reversed) {
    int i = 0;
    if(reversed > 0) {
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
    int i = 0;
    int start = 0;
    if(reversed > 0) {
        while(i < len(number)) {
            if(number[len(number) -1 - i] == 48 && start == 0){
                i++;
                continue;
            } else {
                /*Litera*/
                if(number[len(number) -1 - i] > 57) number[len(number) -1 - i] +=7;
                start = 1;
                fprintf(output, "%c", number[len(number) -1 - i]);
                i++;
            }
        }
        if(start == 0) fprintf(output, "0");
    }else {
        while(i < len(number)) {
            if(number[i] == 48 && start == 0) { 
                i++;
                printf("%c, %d", number[i], start);
                continue;
            } else {
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
/*function which creates array of chars like given number*/
char* create(char str_num[MAX_NUMBER]) {
    /*funkcja alokująca pamięć i zwracająca wskaźnik do zaalokowanego miejsca
    alokuje tyle bitow jaka jest dlugosc stringa*/
    char *ptr = calloc(len(str_num), sizeof(*ptr));
    int i = 0;
    while(i < len(str_num)) {
        if(str_num[i] > 57) ptr[i] = str_num[i]-7;
        else ptr[i] = str_num[i];
        i++;
    }
    return ptr;
}
/*function which creates array of chars like given number but reversed*/
char* create_reversed(char str_num[MAX_NUMBER]) {
    /*funkcja alokująca pamiec na liczbe i zapisujaca ja w odwrotnej kolejnosci*/
    char *ptr = calloc(len(str_num), sizeof(*ptr));
    int i = 0;
    int n = len(str_num);
    while(i < n) {
        if(str_num[n - 1 - i] > 57) ptr[i] = str_num[n - 1 - i] - 7;
        else ptr[i] = str_num[n - 1 - i];
        i++;
    }
    return ptr;
}
/*function activated when newline sign*/
int newline(char *result, int newline_streak, FILE *output) {
    /*zwraca zwiększona wartość newline_streak i zwalnia first i second number*/
    if(!newline_streak) {
        file_print(result, 1, output);
        print_number(result, 1);
        if(result != NULL) {
            free(result);
            printf("freed result\n");
            result = NULL;
        }
    }
    newline_streak++;
    return newline_streak;
}
/*function for finding actual operation*/
char find_operation(char first, int system[], char line[]) {
    /*funkcja wywoływana kiedy linijka to operacja zwraca +, *, ^, /, %, z*/
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
    for (i = bigger_n; i >= 0; i--) {
        if(i==0 && first_number2[i] == '0') {
            first_number2[0] = '0';
            continue;
        }
        if (first_number2[i] == '0') {
            first_number2[i] = '\0';
            continue;
        } else break;
    }
    /*Zwolnienie pamięci*/ 
    free(second_number2);

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
    printf("system=%d\n", system);
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
    for(i=n-1; i >= 0; i--) {
        if(i==0 && wyn[i] == '0') {
            wyn[0] = '0';
            continue;
        }
        if(wyn[i] == '0') {
            wyn[i] = '\0';
            continue;
        } else break;
    }
    return wyn;
}

char * mul(char *first_number, char* second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n + m;
    int i = 0, j=0, multiply, previous = 0;
    char *first_number2, *second_number2, *result;
    printf("n=%d, m=%d, bigger_n=%d\n", n, m, bigger_n);
    printf("first_number: ");
    print_number(first_number, 1);
    printf("second_number: ");
    print_number(second_number, 1);

    /*alokowanie pamięci */
    first_number2 = create(first_number);
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    printf("allocated first_number2\n");
    printf("second_number: ");
    print_number(second_number, 1);
    printf("first_number2: ");
    print_number(first_number2, 1);
    
    second_number2 = create(second_number);

    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    printf("allocated second_number2\n");

    result = (char *)malloc(bigger_n);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
    printf("allocated memory\n");
    /*Dopisywanie zer na początku liczby i przepisywanie liczb*/
    for (i = 0; i < bigger_n; i++) {
        if (i <  n) {
            first_number2[i] = first_number[i];
        } else {
            first_number2[i] = '0';
        }
    }

    for (i = 0; i < bigger_n; i++) {
        if (i <  m) {
            second_number2[i] = second_number[i];
        } else {
            second_number2[i] = '0';
        }
    }

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
    /*zwalnienie pamięci*/
    free(first_number2);
    free(second_number2);
    print_number(result, 1);
    return result;
}

char * division(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    char *low, *high, *result, *multiplicated, *summed, *max_first, *x;
    int new_n = n - m + 1;
    int i = 0;


    /*zbugowane i dziala tylko dla systemu dziesietnego*/

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
        low[0] = '0';
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
            printf("result[%d]=%c, high[%d]=%c, low[%d]=%c\n", new_n - i, result[new_n - i], new_n - i, high[new_n - i], new_n - i, low[new_n - i]);
        } else if(i==1) {
            result[new_n-1 - i] = '0';
            high[new_n-1 - i] = system - 1 + 48;
            printf("result[%d]=%c, high[%d]=%c, low[%d]=%c\n", new_n - i, result[new_n - i], new_n - i, high[new_n - i], new_n - i, low[new_n - i]);
        }
        else {
            result[new_n -1- i] = '0';
            high[new_n -1- i] = system - 1 + 48;
            printf("result[%d]=%c, high[%d]=%c, low[%d]=%c\n", new_n - i, result[new_n - i], new_n - i, high[new_n - i], new_n - i, low[new_n - i]);
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
    i=0;
    while(!(compare(multiplicated, first_number) >= 0 && compare(multiplicated, max_first) < 0))
    {
        if(i > 20) break;

        if(compare(multiplicated, first_number) > 0) {
            high = result;
        } else {
            low = result;
        }
        summed = add(high, low, system);
        result = div_2(summed, system);
        multiplicated = mul(result, second_number, system);


        for (i = new_n; i >= 0; i--) {
            if(i==0 && multiplicated[i] == '0') {
                multiplicated[0] = '0';
                continue;
            }
            if (multiplicated[i] == '0') {
                multiplicated[i] = '\0';
                continue;
            } else break;
        }
        for (i = new_n; i >= 0; i--) {
            if(i==0 && result[i] == '0') {
                result[0] = '0';
                continue;
            }
            if (result[i] == '0') {
                result[i] = '\0';
                continue;
            } else break;
        }

        printf("result: ");
        print_number(result, 1);
        printf("high: ");
        print_number(high, 1);
        printf("low: ");
        print_number(low, 1);
        printf("multiplicated: ");
        print_number(multiplicated, 1);
        printf("i=%d\n", i);
        printf("compare:%d", compare(low, result));
        printf("=-=-=-=-=-==-=-=-=-=-=-=-=-\n");
        
        i++;
        /*nieskonczona petla bo result ustawia sie na low+high/2 czyli low dla liczb obok siebie, zmienic low na high*/
        /*dziala dla podzielnych zwiekszone o 1 dla niepodzielnych*/
        /*zly warunek :(*/
    }
    if(compare(multiplicated, first_number) > 0) {
        x = sub1(result, system);
        if(result != NULL) free(result);
        result = x;
    }
    /*zwalnianie pamięci*/
    free(multiplicated);
    free(summed);
    free(high);
    free(low);
    free(max_first);

    return result;
}

/*function which returns first number to the power of second number*/
char * power(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int new_n = n * pow(system, m);
    int i = 0;
    char *x=NULL, *y=NULL, *result=NULL, *exponent=NULL;
    
    printf("-----------| POW | -----------\n");
    printf("n=%d, m=%d, new_n=%d\n", n, m, new_n);
    printf("first_number: ");
    print_number(first_number, 1);
    printf("second_number: ");
    print_number(second_number, 1);
    result = (char *)malloc(new_n);

    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    exponent = (char *)malloc(m);
    if (exponent == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
    for (i = 0; i < m; i++) {
        printf("i=%d\n", i);
        printf("second_number[%d]=%c\n", i, second_number[i]);
        exponent[i] = second_number[i];
    }
    for(i=m; i >= 0; i--) {
        printf("i=%d\n", i);
        if(i==0 && exponent[i] == '0') {
            exponent[0] = '0';
            continue;
        } if(exponent[i] == '0') {
            exponent[i] = '\0';
            continue;
        } else {
            printf("break\n");
            break;
        }
    }
    if(compare(exponent, "0") == 0) {
        printf("second_number=0 x^0 = 0\n");
        if(result != NULL) free(result);
        printf("len(result)=%d\n", len(result));
        result[0] = '1';
        result[1] = '\0';
        if(exponent != NULL) free(exponent);
        if(y != NULL) free(y);
        printf("free y\n");
        if(x != NULL) free(x);
        printf("free x\n");
        return result;
    }
    if(compare(exponent, "1") == 0) {
        printf("potegowanie do 1-=-=-=-=-=");

        if(result != NULL) free(result);

        for(i=0; i <= len(first_number); i++) {
            result[i] = first_number[i];
            printf("result[%d]=%c\n", i, result[i]);
        }
        printf("first_number: ");
        print_number(first_number, 1);
        printf("second_number: ");
        print_number(exponent, 1);
        printf("result: ");
        print_number(result, 1);
        printf("-=-=-=-=-=-=-=-\n");

        if(exponent != NULL) free(exponent);
        if(y != NULL) free(y);
        if(x != NULL) free(x);
        printf("free y\n");
        return result;
    }
    if(compare(exponent, "2") == 0) {
        if(result != NULL) free(result);
        
        result = mul(first_number, first_number, system);
        printf("first_number: ");
        print_number(first_number, 1);
        printf("second_number: ");
        print_number(exponent, 1);
        printf("result: ");
        print_number(result, 1);
        printf("-=-=-=-=-=-=-=-\n");

        if(exponent != NULL) free(exponent);
        if(y != NULL) free(y);
        if(x != NULL) free(x);
        return result;
    }
    if(compare(exponent, "3") == 0) {
        x = mul(first_number, first_number, system);
        y = mul(first_number, x, system);
        if(result != NULL) free(result);
        result = y;
        
        printf("first_number: ");
        print_number(first_number, 1);
        printf("second_number: ");
        print_number(exponent, 1);
        printf("result: ");
        print_number(result, 1);
        printf("-=-=-=-=-=-=-=-\n");
        if(x != NULL) free(x);
        if(exponent != NULL) free(exponent);
        return result;
    }
    if(compare(exponent, "4") == 0) {
        x = mul(first_number, first_number, system);
        y = mul(x, x, system);
        if(result != NULL) free(result);
        result = y;
        
        printf("first_number: ");
        print_number(first_number, 1);
        printf("second_number: ");
        print_number(exponent, 1);
        printf("result: ");
        print_number(result, 1);
        printf("-=-=-=-=-=-=-=-\n");
        if(x != NULL) free(x);
        if(exponent != NULL) free(exponent);
        return result;
    }
    /*rekurencja - wykladnik > 4*/
    if (!(compare(exponent, "1") == 0)) {
        if (mod_2(exponent, system) == 0) {
            /* x^n = x^(n/2) * x^(n/2) */
            x = div_2(exponent, system);
            if(exponent != NULL) free(exponent);
            exponent = x;
            printf("mod2=0, x^n = x^(n/2) * x^(n/2)\n");
            printf("exponent: ");
            print_number(exponent, 1);

            for (i = len(exponent); i >= 0; i--) {
                if(i== 0 && exponent[i] == '0') {
                    exponent[0] = '0';
                    continue;
                }
                if (exponent[i] == '0') {
                    exponent[i] = '\0';
                    continue;
                } else break;
            }
            x = power(first_number, exponent, system);
            printf("x: ");
            print_number(x, 1);
            printf("wyszedlem z rekurencji\n");
            print_number(result, 1);
            printf("done\n");
            printf("result size=%d\n", len(result));
            printf("x size=%d\n", len(x));
            result = mul(x, x, system);
            printf("result size=%d\n", len(result));
            if(result != NULL) free(result);
            result = y;
            printf("result: ");
            print_number(result, 1);
            if(x != NULL) free(x);
            for (i = len(result)-1; i >= 0; i--) {
                if(i== 0 && result[i] == '0') {
                    result[0] = '0';
                    continue;
                }
                if (result[i] == '0') {
                    result[i] = '\0';
                    continue;
                } else break;
            }
        } else {
            x = div_2(exponent, system);
            if(exponent != NULL) free(exponent);
            exponent = x;
            printf("mod2=0, x x^n = x * x^(n/2) * x^(n/2)\n");
            printf("exponent: ");
            print_number(exponent, 1);
            for (i = len(exponent); i >= 0; i--) {
                if(i== 0 && exponent[i] == '0') {
                    exponent[0] = '0';
                    continue;
                }
                if (exponent[i] == '0') {
                    exponent[i] = '\0';
                    continue;
                } else break;
            }
            x = power(first_number, exponent, system);
            printf("wyszedlem z rekurencji\n");
            y = mul(x, x, system);
            if(result != NULL) free(result);
            result = mul(y, first_number, system);
            if(x != NULL) free(x);
            if(y != NULL) free(y);

            for (i = len(result)-1; i >= 0; i--) {
                if(i== 0 && result[i] == '0') {
                    result[0] = '0';
                    continue;
                }
                if (result[i] == '0') {
                    result[i] = '\0';
                    continue;
                } else break;
            }
        }

        printf("first_number: ");
        print_number(first_number, 1);
        printf("second_number: ");
        print_number(exponent, 1);
        printf("result: ");
        print_number(result, 1);
        printf("-=-=-=-=-=-=-=-\n");    
    }
    if(exponent != NULL) free(exponent);
    printf("free exponent\n");
    return result;
}
char * arithmetics(char *first_number, char *second_number, char operation, int system[]) {
    char * result=NULL;
    if(operation == '+')  result = add(first_number, second_number, system[0]);
    else if(operation == '*') result = mul(first_number, second_number, system[0]);
    else if(operation == '^') result = power(first_number, second_number, system[0]);
    else if(operation == '/') result = division(first_number, second_number, system[0]);
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
    int c;
    char line[MAX_NUMBER];
    systems[0] = 0;
    systems[1] = 0;
    /*otwieranie pliku*/
    ptr_in = fopen(INPUT, "r");
    ptr_out = fopen(output, "w");
    /*glowna petla funkcji*/
    while(fgets(line, MAX_NUMBER, ptr_in)) {
        if(line[0] == '\n') {
            newline_streak = newline(result, newline_streak, ptr_out);
        } else {
            /*linijka operacji - zapisanie operacji i systemu lub systemu i systemu docelowego*/
            if(newline_streak > 0) {
                operation = find_operation(line[0], systems, line);
                printf("operation=%c, system=%d, ew. system 2 = %d\n", operation, systems[0], systems[1]);
                newline_streak = 0;
                number_streak = 0;
                fprintf(ptr_out, "%s", line);
            }
            /*pierwsza liczba */
            else if(newline_streak == 0 && number_streak == 0) {
                first_number = create_reversed(line);
                printf("first_number reversed: ");
                print_number(first_number, 1);
                number_streak++;
                fprintf(ptr_out, "%s", line);

            /*kolejna liczba */
            } else if(newline_streak == 0 && number_streak > 0) {
                second_number = create_reversed(line);
                printf("second_number reversed: ");
                print_number(second_number, 1);
                fprintf(ptr_out, "%s", line);
                result = arithmetics(first_number, second_number, operation, systems);
                printf("%s", first_number);
                printf("%s", second_number);
                
                c = compare(first_number, second_number);
                printf("compare=%d\n", c);


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
        printf("result: ");
        print_number(result, 1);
        file_print(result, 1, ptr_out);
        printf("freeing result\n");
        printf(result == NULL ? "result is NULL\n" : "result is not NULL\n");
        printf(first_number == NULL ? "first is NULL\n" : "first is not NULL\n");


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
