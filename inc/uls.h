#ifndef ULS_HEADER_H
#define ULS_HEADER_H

#include "libmx.h"
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

#define IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define IS_EXEC(mode) ((mode) & S_IXUSR)

#define LS_COLOR_RED        "\x1b[31m"
#define LS_COLOR_RESET      "\x1b[0m"

typedef struct fl {
    int l;
    int C;
    int x;
    int R;
    int r;
    int t;
    int u;
    int c;
    int S;
    int a;
    int A;
    int force;
    int m;
    int files;
    int G;
    int T;
    int g;
    int o;
    int ex;
}   st_fl;

typedef struct s_sz {
    int lnk;
    int sz;
    int group;
    int usr;
    bool is_dev;
}   t_sz;

typedef struct s_li {
    char *name;
    char *path;
    char *err;
    struct stat info;
    struct s_li **open;
}   t_li;

typedef struct n_type {
    int n_f;
    int n_d;
    int n_e;
    int i;
}   s_type;

void mx_join(char **res, char *s2);
void mx_printstr_g(t_li *args);
int max_len_names(t_li **names);
void mx_print_tab(int len, int maxlen);
void mx_del_arr_arr(t_li ***args);
void mx_printcharerr(char c);
t_li **mx_get_names(int argc, char **argv, int i);
void mx_opendir(t_li ***names, st_fl *fl);
void mx_out_put_all(t_li ***args, st_fl *fl);
void mx_sort(t_li ***disp, st_fl *fl);
t_li **mx_get_files(t_li ***args, st_fl *fl);
void mx_del_files(t_li ***args, st_fl *fl);
void mx_del_liarr(t_li ***args, t_li **dirs);

// Output
void mx_out_put_menu(t_li ***names, st_fl *fl, int flag);
void mx_out_err(t_li ***error, st_fl *fl);
void mx_output_x(t_li **names);
void mx_output_c(t_li **names);
void mx_output_m(t_li **names, st_fl *fl);
void mx_output_g(t_li **names, st_fl *fl);
void mx_long_out(t_li **names, st_fl *fl, int flag);

void mx_print_per(t_li *print);
void mx_print_sz(t_li *print, t_sz *size);
void mx_print_symblink(t_li *print);
void mx_print_all(t_li *print, t_sz *size, st_fl *fl);

#endif
