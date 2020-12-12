#include "uls.h"

static void out_put1(t_li **names, st_fl *fl) {
    for (int i = 0; names[i]; i++) {
        if (fl->G != 1)
            mx_printstr(names[i]->name);
        else
            mx_printstr_g(names[i]);
        mx_printchar('\n');
    }
}

void mx_del_arr_arr(t_li ***args) {
    t_li **del_arr = *args;

    for (int i = 0; del_arr[i]!= NULL; i++) {
        mx_strdel(&del_arr[i]->name);
        mx_strdel(&del_arr[i]->path);
        if (del_arr[i]->err)
            mx_strdel(&del_arr[i]->err);
        if (del_arr[i]->open != NULL)
            mx_del_arr_arr(&del_arr[i]->open);
        free(del_arr[i]);
        del_arr[i] = NULL;
    }
    free(*args);
    *args = NULL;
}

void mx_out_put_menu(t_li ***names, st_fl *fl, int flag) {
    if (**names != NULL) {
        mx_sort(&(*names), fl);
        (fl->l) ? mx_long_out(*names, fl, flag) : (void) 0;
        if (fl->C == 1 && !fl->G)
            mx_output_c(*names);
        if (fl->x == 1 && !fl->G)
            mx_output_x(*names);
        if (fl->m == 1)
            mx_output_m(*names, fl);
        if (fl->force == 1)
            out_put1(*names, fl);
        if (fl->G == 1 && fl->m != 1 && fl->l != 1 && fl->force != 1)
            mx_output_g(*names, fl);
        if (fl->l != 1 && fl->C != 1 && fl->x != 1 && fl->m != 1
            && fl->force != 1 && !fl->G && !fl->g && !fl->o && isatty(1))
            mx_output_c(*names);
        if (!isatty(1) && fl->C != 1 && fl->x != 1 && fl->m != 1
            && fl->l != 1 && fl->g != 1 && fl->o != 1 && fl->force != 1)
            out_put1(*names, fl);
    }
}

static void outputerropen(t_li **args, st_fl *fl) {
    if ((*args)->open != NULL) {
        mx_out_put_menu(&(*args)->open, fl, 1);
        if (fl->R == 1) {
            fl->files = 1;
            mx_del_files(&(*args)->open, fl);
            if ((*args)->open) {
                mx_printchar('\n');
                mx_opendir(&(*args)->open, fl);
            }
        }
    }
    else if ((*args)->err != NULL) {
        mx_printerr("uls: ");
        mx_printerr((*args)->path);
        mx_printerr(": ");
        mx_printerr((*args)->err);
        mx_printerr("\n");
    }
}

void mx_out_put_all(t_li ***args, st_fl *fl) {
    if (*args) {
        for (int i = 0; (*args)[i] != NULL; i++) {
            if (fl->files == 1) {
                if ((*args)[i]->path[0] == '/' && (*args)[i]->path[1] == '/')
                    mx_printstr(&(*args)[i]->path[1]);
                else
                    mx_printstr((*args)[i]->path);
                mx_printchar(':');
				mx_printchar('\n');
            }
            outputerropen(&(*args)[i], fl);
            if (fl->files == 1 && (*args)[i+1])
                mx_printchar('\n');
        }
        mx_del_arr_arr(args);
    }
}
