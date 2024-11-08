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
