#include "libmx.h"

void mx_join(char **res, char *s2) {
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    int i = 0;
    int si = -1;
    char *s1 = *res;

    while(s1[++si]) {
        newstr[i] = s1[si];
        i++;
    }
    si = -1;
    while(s2[++si]) {
        newstr[i] = s2[si];
        i++;
    }
    mx_strdel(&(*res));
    *res = newstr;
}
