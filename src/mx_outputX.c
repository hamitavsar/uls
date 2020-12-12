#include "uls.h"

static void printcols_x(t_li **names, int rows, int cols, int maxlen) {
    int j = 0;
    int tempcols = cols;

    for (int i = 0; i < rows; i++, cols += tempcols) {
        for (; names[j] && j < cols; j++) {
            mx_printstr(names[j]->name);
            if (names[j + 1] && (j != cols - 1))
                mx_print_tab(mx_strlen(names[j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}

static void print_names(t_li **names, int maxlen, int wincol) {
    int rows;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    for(;names[num]; num++) {
    }
    if (maxlen * cols > wincol && cols != 1)
        cols--;
    if (num * maxlen > wincol) {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
            rows += 1;
        printcols_x(names, rows, cols, maxlen);
    } else
        for (int i = 0; names[i]; i++) {
            mx_printstr(names[i]->name);
            if (names[i + 1])
                mx_print_tab(mx_strlen(names[i]->name), maxlen);
        }
        mx_printchar('\n');
}

void mx_output_x(t_li **names) {
    int maxlen;
    struct winsize win;

    if (!names)
        return;
    maxlen = max_len_names(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
        print_names(names, maxlen, win.ws_col);
    else
        print_names(names, maxlen, 80);
}
