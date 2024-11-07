char * div(char *first_number, char *second_number, int system) {
    int n = len(first_number);
    int m = len(second_number);
    int new_n = n - m + 1;
    int i = 0, j=0;
    char *multed, *summed, *h, *l, *result;
    

    /*inicjacja high*/
    h = calloc(new_n, sizeof(*h));
    while(i < new_n) {
        h[i] = (system - 1) + 48;
        i++;
    }
    i=1;
    /*inicjacja low*/
    l = calloc(new_n-1, sizeof(*l));
    l[0] = '1';
    while(i < new_n-1) {
        l[i] = '0';
        i++;
    }
    /*inicjacja result*/
    i=1;
    result[0] = system/2 + 48;
    result = calloc(new_n, sizeof(*result));
    while(i < new_n) {
        result[i] = '0';
        i++;
    }

    printf("first_number: ");
    print_number(first_number, 1);
    printf("second_number: ");
    print_number(second_number, 1);
    printf("h: ");
    print_number(h, 1);
    printf("l: ");
    print_number(l, 1);
    printf("result: ");
    print_number(result, 1);
    printf("new_n=%d\n", new_n);
    prinf("-=-=-=-=-=-=-=-=-=-=-=mnozenie=-=-=-=-=-=-=-\n");


    multed = mul(result, second_number, system);

    while (compare(multed, first_number) >= 0 && compare(multed, sum(first_number, second_number, system)) < 0) {
        multed = mul(result, second_number, system);
        if(compare(multed, first_number) > 0 ){
            h = result;
        } else {
            l = result;
        }
        summed = sum(h, l, system);
        result = div(summed, 2, system);
    }

    /*zwalnianie pamięci*/
    free(multed);
    free(summed);
    free(h);
    free(l);

    return result;
}