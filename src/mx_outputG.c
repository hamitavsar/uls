#include "uls.h"

static void mx_print_spaces_g(int len, int maxlen) {
    int count = 0;

    count = maxlen - len;
    for (int i = 0; i < count; i++)
        mx_printchar(' ');
}

static void printcols_c(t_li **names, int rows, int num, int maxlen) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < num; j += rows) {
            mx_printstr_g(names[i + j]);
            if (names[i + j + 1] && (i + j + rows < num))
                mx_print_spaces_g(mx_strlen(names[i + j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}

static int mx_max_len_n_g(t_li **names) {
    int max = 0;
    int temp = 0;

    for (int i = 0; names[i]; i++) {
        temp = mx_strlen(names[i]->name);
        if (temp > max)
            max = temp;
    }
    max++;
    return max;
}

static void printcols_x(t_li **names, int rows, int cols, int maxlen) {
    int j = 0;
    int tempcols = cols;

    for (int i = 0; i < rows; i++, cols += tempcols) {
        for (; names[j] && j < cols; j++) {
            mx_printstr_g(names[j]);
            if (names[j + 1] && (j != cols - 1))
                mx_print_spaces_g(mx_strlen(names[j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}

static void printrow_g(t_li **names, int maxlen) {
    for (int i = 0; names[i]; i++) {
        mx_printstr_g(names[i]);
        if (names[i + 1]) 
            mx_print_spaces_g(mx_strlen(names[i]->name), maxlen);
    }
}

static void print_names(t_li **names, int maxlen, int wincol, st_fl *fl) {
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
        if (fl->x == 0)
            printcols_c(names, rows, num, maxlen);
        else
            printcols_x(names, rows, cols, maxlen);
    } else
        printrow_g(names, maxlen);
    mx_printchar('\n');
}

void mx_output_g(t_li **names, st_fl *fl) {
    int maxlen;
    struct winsize win;

    if (!names)
        return;
    maxlen = mx_max_len_n_g(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    print_names(names, maxlen, win.ws_col, fl);
}
