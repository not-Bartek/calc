char * to_decimal(char *first_number, int system) {
    int n = len(first_number);
    int i = 0, new_n =2 * n, powered, x; /*2 ≥ log_10(16)*/
    char *result = (char *)malloc(new_n),*y;
    if (result == NULL) { 
        printf("UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for(i=0; i < new_n; i++) {
        result[i] = '0';
    }
    for(i=0; i < n; i++) {
        /*zrobienie stringa z i*/
        /*zrobienie stringa z systemu*/
        /*potegowanie system ^ i*/
        /*x = mul(first[i], powered)*/
        /*y = add(result, x)*/
        /*result = y*/
        /*zwalnianie zmiennych*/

        result = y;
        free(y);
    }
    /*Usuniecie zer*/
    rem_0_rev(result);
    return result;
}