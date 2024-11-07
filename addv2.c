char * add(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n > m ? n : m;
    int i = 0;
    char *first_number2, *second_number2;
    int previous = 0;
    printf("n=%d, m=%d, bigger_n=%d\n", n, m, bigger_n);
    /*zwiekszanie rozmiaru first number 1 i 2 o 1 bajt*/
    first_number2 = (char *)malloc(bigger_n + 1);
    printf("allocated first_number2\n");
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    second_number2 = (char *)malloc(bigger_n + 1);
    printf("allocated second_number2\n");
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
    printf("first_number2 (reversed): ");
    print_number(first_number2, 1);
    printf("second_number2 (reversed): ");
    print_number(second_number2, 1);
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
    printf("first_number2 after add operation (reversed): ");
    print_number(first_number2, 1);
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