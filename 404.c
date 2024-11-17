else if(number_streak==0 && newline_streak == 1 && error_code == 0) {
    fprintf(ptr_out, "%s", line);
    error_code = 402;
    print_error(error_code, ptr_out);
    error_code = 0;
    newline_streak++;
    continue;
            }