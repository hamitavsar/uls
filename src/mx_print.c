#include "uls.h"

static void mx_get_user_name(t_li *print, int usr) {
    struct passwd *pw = getpwuid(print->info.st_uid);
    int counter = 0;
    char *name = NULL;

    if (pw)
        name = mx_strdup(pw->pw_name);
    else
        name = mx_itoa(print->info.st_uid);
    if (mx_strlen(name) == usr)
       mx_printstr(name);
    else if (mx_strlen(name) < usr) {
        counter = mx_strlen(name);
        mx_printstr(name);
        while (counter != usr) {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(name);
}

static void mx_get_group_name(t_li *print, int group) {
    struct group *grp = getgrgid(print->info.st_gid);
    int counter = 0;
    char *name = NULL;

    if (grp)
        name = mx_strdup(grp->gr_name);
    else
        name = mx_itoa(print->info.st_gid);
    if (mx_strlen(name) == group)
        mx_printstr(name);
    else if (mx_strlen(name) < group) {
        counter = mx_strlen(name);
        mx_printstr(name);
        while (counter != group) {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(name);
}

static void print_link_and_color(t_li *print, st_fl *fl) {
    if (fl->G == 1)
        mx_printstr_g(print);
    else if (IS_LNK(print->info.st_mode)) {
        mx_printstr(print->name);
        mx_print_symblink(print);
    }
    else
        mx_printstr(print->name);
}

static void mx_edit_time(t_li *print, char *t, st_fl *fl) {
    int i = 0;

    if (fl->T == 1)
        for (i = 4; i < t[i]; i++)
           mx_printchar(t[i]); 
    else {
        if (1565913600 >= print->info.st_mtime) {
            for(i = 4; i < 10; i++)
                mx_printchar(t[i]);
            mx_printstr("  ");
            for (i = 20; i < 24; i++)
                mx_printchar(t[i]); 
        }
        else
            for(i = 4; i < 16; i++)
                mx_printchar(t[i]);
    }
    mx_printstr(" ");
}

static void mx_print_lnk(t_li *print, t_sz *size) {
    int counter = 0;
    char *res_itoa_now = mx_itoa(print->info.st_nlink);
    char *res_itoa_lnk = mx_itoa(size->lnk);

    if (mx_strlen(res_itoa_now) == mx_strlen(res_itoa_lnk)) {
        mx_printint(print->info.st_nlink);
    }
    else if (mx_strlen(res_itoa_now) < mx_strlen(res_itoa_lnk)) {
        counter = mx_strlen(res_itoa_now);
        while (counter != mx_strlen(res_itoa_lnk)) {
            mx_printchar(' ');
            counter++;
        }
        mx_printint(print->info.st_nlink);
    }
    mx_printchar(' ');
    free(res_itoa_now);
    free(res_itoa_lnk);
}

void mx_print_symblink(t_li *print) {
    char *buf = NULL;
    ssize_t nbytes = 0;
    ssize_t buf_size = 0;

    buf_size = print->info.st_size == 0 ? 100 : print->info.st_size + 1;
    buf = mx_strnew(buf_size);
    nbytes = readlink(print->path, buf, buf_size);
    mx_printstr(" -> ");
    if (nbytes >= 0)
        mx_printstr(buf);
    mx_strdel(&buf);
}

void mx_print_all(t_li *print, t_sz *size, st_fl *fl) {
    time_t *chtime = &print->info.st_ctime;
    time_t *atime = &print->info.st_atime;
    time_t *t = &print->info.st_mtime;

    mx_print_per(print);
    mx_print_lnk(print, size);
    if ((fl->l == 1 && fl->g == 0) || (fl->o == 1 && fl->g == 0))
        mx_get_user_name(print, size->usr);
    if ((fl->l == 1 && fl->o == 0) || (fl->g == 1 && fl->o == 0))
        mx_get_group_name(print, size->group);
    mx_print_sz(print, size);
    if (fl->u == 1)
        t = atime;
    if (fl->c == 1)
        t = chtime;
    mx_edit_time(print, ctime(t), fl);
    print_link_and_color(print, fl);
    mx_printchar('\n');
}
