#include <stdio.h>
char * add(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n > m ? n : m;
    int i = 0;
    char *first_number2, *second_number2;
    int previous = 0;
    /*zwiekszanie rozmiaru first number 1 i 2 o 1 bajt*/
    
    first_number2 = realloc(first_number, bigger_n + 1);
    if(first_number2 == NULL) printf("UNABLE TO REALLOC MEMORY");
    else first_number = first_number2;
    second_number2 = realloc(second_number, bigger_n + 1);
    if(second_number2 == NULL) printf("UNABLE TO REALLOC MEMORY");
    else second_number = second_number2;
    /*Dopisywanie zer na początku liczby*/
    while(i <  bigger_n + 1) {
        if(i<n) i++;
        else {
            first_number[i] = 48;
            i++;
        }
    }
    i=0;
    while(i <  bigger_n + 1) {
        if(i<m) i++;
        else {
            second_number[i] = 48;
            i++;
        }
    }    
    /*Dodawanie*/
    i=0;
    while(i <  bigger_n + 1) {
        if( first_number[i] - 48 + second_number[i] - 48 + previous >= system) {
            /*Przepełnienie*/
            first_number[i] = (((first_number[i] - 48 + second_number[i] - 48 + previous) % system)) + 48;
            previous = 1;
        } else {
            /*Brak przepełnienia*/
            first_number[i] =  (first_number[i] - 48 + second_number[i] - 48 + previous ) + 48;
            previous = 0;
        }
        i++;
    }
    /*Zwolnienie drugiej liczby*/
    free(second_number);
    second_number = NULL;
    return first_number;
}