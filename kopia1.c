#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER 1000000

/*
wczytywanie, dodawanie śmiga i mnożenie też

*/

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
        if (first_number2[i] == '0') {
            first_number2[i] = '\0';
        } else break;
    }
    /*Zwolnienie pamięci*/ 
    free(second_number2);

    return first_number2;
}


int mod_2(char *num) {return ((num[len(num-1)]-48) %2);}

char * div_2(char *first, int system) {
    int n = len(first), i=0, j=0;
    int previous = 0;
    char *wyn = calloc(n, sizeof(*wyn));

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
    return wyn;
}

char * mul(char *first_number, char* second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n + m;
    int i = 0, j=0, multiply, previous = 0;
    char *first_number2, *second_number2, *result;

    /*alokowanie pamięci */
    first_number2 = (char *)malloc(bigger_n);
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    second_number2 = (char *)malloc(bigger_n);
    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    result = (char *)malloc(bigger_n);
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(result);
        return NULL;
    }
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
       if(i %1000 == 0) {
              printf("i=%d\n", i);
       }
       
    }
    return result;
}

char * arithmetics(char *first_number, char *second_number, char operation, int system[]) {
    char * result=NULL;
    if(operation == '+')  result = add(first_number, second_number, system[0]);
    else if(operation == '*') result = mul(first_number, second_number, system[0]);
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
                
                free(first_number);
                printf("freed first_number\n");
                free(second_number);
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
        free(result);
        result = NULL;
    }
    fclose(ptr_in);
    fclose(ptr_out);
}

int main(void) {
    calculate("small_input.txt", "out.txt");
    
    return 0;
}
