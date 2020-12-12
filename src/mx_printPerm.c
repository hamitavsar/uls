#include "uls.h"

static char mx_get_file_acl(t_li *print) {
    acl_t tmp;

    if (listxattr(print->path, NULL, 0, XATTR_NOFOLLOW) > 0)
        return ('@');
    if ((tmp = acl_get_file(print->path, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        return ('+');
    }
    return (' ');
}

static char mx_check_per(t_li *print) {
    if (IS_DIR(print->info.st_mode))
        return 'd';
    if (IS_LNK(print->info.st_mode))
        return 'l';
    if (IS_BLK(print->info.st_mode))
        return 'b';
    if (IS_CHR(print->info.st_mode))
        return 'c';
    if (IS_FIFO(print->info.st_mode))
        return 'p';
    if (IS_SOCK(print->info.st_mode))
        return 's';
    if (IS_WHT(print->info.st_mode))
        return 'w';
    return '-';
}

static char check_chmode1(char chmod) {
    if (chmod == '-')
        return chmod = 'S';
    else
        return chmod = 's';
}

static char check_chmode2(char *chmod) {
    if (chmod[9] == '-')
        return chmod[9] = 'T';
    else
        return chmod[9] = 't';
}

void mx_print_per(t_li *print) {
    char chmod[12];
    
    chmod[0] = mx_check_per(print);
    chmod[1] = (S_IRUSR & print->info.st_mode) ? 'r' : '-';
    chmod[2] = (S_IWUSR & print->info.st_mode) ? 'w' : '-';
    chmod[3] = (S_IXUSR & print->info.st_mode) ? 'x' : '-';
    chmod[4] = (S_IRGRP & print->info.st_mode) ? 'r' : '-';
    chmod[5] = (S_IWGRP & print->info.st_mode) ? 'w' : '-';
    chmod[6] = (S_IXGRP & print->info.st_mode) ? 'x' : '-';
    chmod[7] = (S_IROTH & print->info.st_mode) ? 'r' : '-';
    chmod[8] = (S_IWOTH & print->info.st_mode) ? 'w' : '-';
    chmod[9] = (S_IXOTH & print->info.st_mode) ? 'x' : '-';
    chmod[10] = mx_get_file_acl(print);
    chmod[11] = '\0';
    S_ISUID & print->info.st_mode ? chmod[3] = check_chmode1(chmod[3]) : 0;
    S_ISGID & print->info.st_mode ? chmod[6] = check_chmode1(chmod[6]) : 0;
    S_ISVTX & print->info.st_mode ? chmod[9] = check_chmode2(chmod) : 0;
    for (int i = 0; chmod[i]; i++)
        mx_printchar(chmod[i]);
    mx_printchar(' ');
}
