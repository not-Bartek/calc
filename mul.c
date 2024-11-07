char * mul(char *first_number, char *second_number, int system) {
    
    int n = len(first_number);
    int m = len(second_number);
    /*alokacja miejsca na wynik*/
    char *wyn = calloc( (n+m+1), sizeof(char));
    char *result,*half_mul, *double_half_mul;
    if(mod_2(second_number) == 0) {
        /*parzysty mnoznik*/
        printf("mnoznik\t");
        print_number(second_number, 1);
        printf("dlugosc: %d\n", len(second_number));
        if(len(second_number) == 1 && second_number[0] == '2') {
            printf("mnoznik = 2 koniec , ");
            print_number(second_number, 1);
            free(wyn);
            result = add(first_number, first_number, system);
            return result;
        }
        print_number(second_number, 1);
        printf("parzysty mnoznik\t");
        printf("mnoznik[0] =%c\n", second_number[0]);
        second_number = div_2(second_number, system);
        half_mul = mul(first_number, second_number, system);
        wyn = (add(half_mul, half_mul, system));
        printf("wynik\t");
        print_number(wyn, 1);
        free(half_mul);
        return wyn;
    } else {
        /*nieparzysty mnoznik*/
        printf("mnoznik\t");
        print_number(second_number, 1);
        printf("mnoznik[0] =%c\n", second_number[0]);
        printf("dlugosc: %d\n", len(second_number));
        if(len(second_number) == 1 && second_number[0] == '2') {
            printf("mnoznik = 2, ");
            print_number(second_number, 1);
            result = add(first_number, first_number, system);
            free(wyn);
            return result;
        }
        print_number(second_number, 1);
        printf("nieparzysty mnoznik\t");
        second_number = div_2(second_number, system);
        half_mul = mul(first_number, second_number, system);
        double_half_mul = add(half_mul, half_mul, system);

        wyn = add(double_half_mul, first_number, system);
        free(half_mul);
        free(double_half_mul);
        printf("wynik\t");
        print_number(wyn, 1);
        return wyn;
    }
}