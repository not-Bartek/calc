char * mul(char *first_number, char* second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int bigger_n = n + m;
    int i = 0, j=0;
    char *first_number2, *second_number2, *result, *x;

    int *mod = calloc(m, sizeof(*mod));
    /*alokowanie pamięci */
    printf("n=%d, m=%d, bigger_n=%d\n", n, m, bigger_n);

    first_number2 = (char *)malloc(bigger_n);
    printf("allocated first_number2\n");
    if (first_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    second_number2 = (char *)malloc(bigger_n);
    printf("allocated second_number2\n");
    if (second_number2 == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        free(first_number2);
        return NULL;
    }
    /*Dopisywanie zer na początku liczby i przepisywanie liczb*/
    
    for (i = 0; i < bigger_n; i++) {
        if (i <  m) {
            second_number2[i] = second_number[i];
        } else {
            /*second_number2[i] = '0';*/
        }
    }
    print_number(first_number, 1);
    printf("first_number2 (reversed): ");
    print_number(first_number2, 1);

    
    printf("first_number2 (reversed): ");
    print_number(second_number2, 1);
    result = first_number2;

    /*Mnożenie*/
    printf("first_number2: ");
    printf("%c\n", second_number2[0]);
    printf("len");
    printf("%d\n", len(second_number2));

    printf("result: ");
    print_number(result, 1);
    printf("first number");
    print_number(first_number2, 1);
    i=0;
    while(second_number2[0] != '1' || len(second_number2) > 1) {
        printf("second_number2: ");
        print_number(second_number2, 1);
        printf("length of second_number2: %d\n", len(second_number2));
        if(mod_2(second_number2) == 0) {
            mod[i] = 0;   
        } else {
            mod[i] = 1;
        }
        second_number2 = div_2(second_number2, system);
        i++;
        printf("result: ");
        print_number(first_number, 1);
    }
    i--;
    
    for (j = 0; j < bigger_n; j++) {
        if (j <  n) {
            first_number2[j] = first_number[j];
        } else {
            first_number2[j] = '0';
        }
    }
    result = first_number2;
    printf("result before multiplication: ");
    print_number(result, 1);
    while(i >= 0) {
        x = add(result, result, system);
        printf("mod[%d]=%d\n", i, mod[i]);
        if(mod[i] == 0) {
            /*reszta 0*/
            result = x;
        } else if(mod[i] == 1) {
            /*reszta 1*/
            result = add(first_number2, x, system);
        }
        printf("result: ");
        print_number(result, 1);
        free(x);
        i--;
    }
    printf("result: ");
    print_number(result, 1);
    printf("first_number2: ");
    print_number(first_number2, 1);
    /*Usunięcie wiodących zer*/


    /*zwalnianie pamięci*/
    free(second_number2);
    print_number(first_number2, 1);
    return result;
}