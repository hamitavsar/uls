#include "uls.h"

static void print_name(t_li *args) {
    mx_printstr(args->name);
    mx_printstr(LS_COLOR_RESET);
}

static int print_frst(t_li *args) {
    if (IS_DIR(args->info.st_mode)) {
        mx_printstr("\033[34m");
        print_name(args);
        return 1;
    }
    else if (IS_LNK(args->info.st_mode)) {
        mx_printstr("\033[35m");
        print_name(args);
        return 1;
    }
    else if (args->info.st_mode & S_IXOTH) {
        mx_printstr(LS_COLOR_RED);
        print_name(args);
        return 1;
    }
    return 0;
}

static int print_sec(t_li *args) {
    if (IS_BLK(args->info.st_mode)) {
        mx_printstr("\033[34;46m");
        print_name(args);
        return 1;
    }
    else if (IS_CHR(args->info.st_mode)) {
        mx_printstr("\033[34;43m");
        print_name(args);
        return 1;
    }
    else if (IS_SOCK(args->info.st_mode)) {
        mx_printstr("\033[32m");
        print_name(args);
        return 1;
    }
    return 0;
}

void mx_printstr_g(t_li *args) {
    if (print_frst(args) == 1) {
    }
    else if (print_sec(args) == 1) {
    }
    else if (IS_FIFO(args->info.st_mode)) {
        mx_printstr("\033[33m");
        print_name(args);
    }
    else if (IS_WHT(args->info.st_mode)) {
        mx_printstr("\033[36m");
        print_name(args);
    }
    else if (IS_EXEC(args->info.st_mode)) {
        mx_printstr("\033[31m");
        print_name(args);
    }
    else
        mx_printstr(args->name);
}
