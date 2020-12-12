#include "uls.h"

static void print_spaces(int size) {
    for(int i = 0; i <= size; i++) {
        mx_printchar(' ');
    }
}

static char *minor_to_hex(char *minor) {
    char *hex_minor = mx_strdup("0x00000000");

    mx_strcpy(hex_minor + (10 - mx_strlen(minor)), minor);
    mx_strdel(&minor);
    return hex_minor;
}

static char *mx_get_minor(t_li *print) {
    int minor_num = (int)(print->info.st_rdev & 0xffffff);
    char *minor = NULL;

    if (minor_num > 255)
        minor = minor_to_hex(mx_nbr_to_hex(minor_num));
    else
        minor = mx_itoa(minor_num);
    return minor;
}

static char *mx_get_major(t_li *print) {
    return mx_itoa((int)(((unsigned int)print->info.st_rdev >> 24) & 0xff));
}

static void print_duo_cases(t_li *print, t_sz *size) {
    char *major = mx_get_major(print);
    char *minor = mx_get_minor(print);
    
    if (size->is_dev == true)
        if (IS_BLK(print->info.st_mode) || IS_CHR(print->info.st_mode)) {
            print_spaces(2 - mx_strlen(major));
            mx_printstr(major);
            mx_printchar(',');
            mx_printchar(' ');
            print_spaces(2 - mx_strlen(minor));
            mx_printstr(minor); 
        }
        else {
            mx_printstr("       ");
            mx_printint(print->info.st_size);
        }
    else
       mx_printint(print->info.st_size); 
    free(major);
    free(minor);
}

void mx_print_sz(t_li *print, t_sz *size) {
    char *res_now = mx_itoa(print->info.st_size);
    char *res_sz = mx_itoa(size->sz);
    int counter = 0;

    if (mx_strlen(res_now) == mx_strlen(res_sz))
        print_duo_cases(print, size);
    else if (mx_strlen(res_now) < mx_strlen(res_sz)) {
        counter = mx_strlen(res_now);
        while (counter != mx_strlen(res_sz)) {
            mx_printchar(' ');
            counter++;
        }
        print_duo_cases(print, size);
    }
    mx_printchar(' ');
    free(res_now);
    free(res_sz);
}
