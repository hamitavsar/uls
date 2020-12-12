#include "uls.h"

static int cmp2(t_li *first, t_li *second, st_fl *fl) {
    if (fl->c == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_ctime == second->info.st_ctime) {
            if (first->info.st_ctimespec.tv_nsec
                == second->info.st_ctimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_ctimespec.tv_nsec
                    < second->info.st_ctimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
    }
    else if (fl->t != 1 && fl->S != 1)
        if (mx_strcmp(first->name, second->name) > 0)
            return 1;
    return 0;
}

static int cmp1(t_li *first, t_li *second, st_fl *fl) {
    if (fl->u == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_atime == second->info.st_atime) {
            if (first->info.st_atimespec.tv_nsec
                == second->info.st_atimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_atimespec.tv_nsec
                    < second->info.st_atimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
    }
    else 
        return cmp2(first, second, fl);
}

static int cmp(t_li *first, t_li *second, st_fl *fl) {
    if (fl->S == 1) {
        if (first->info.st_size < second->info.st_size)
            return 1;
        if (first->info.st_size == second->info.st_size)
            return mx_strcmp(first->name, second->name);
    }
    else if (fl->t == 1 && fl->c != 1 && fl->u != 1) {
        if (first->info.st_mtime == second->info.st_mtime) {
            if (first->info.st_mtimespec.tv_nsec
                == second->info.st_mtimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_mtimespec.tv_nsec
                    < second->info.st_mtimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
    }
    return cmp1(first, second, fl);
}


static int count_sizearr(t_li **disp) {
	int i = 0;

	while(disp[i]) {
		i++;
	}
	return i;
}

static void swap_li(t_li **bondOne, t_li **bondTwo) {
    t_li *temp = *bondOne;

    *bondOne = *bondTwo;
    *bondTwo = temp;
}

void mx_sort(t_li ***disp, st_fl *fl) {
	t_li **bond = *disp;
	int size = count_sizearr(bond);

	for (int i = 0; i < size; i++) 
    {
		for (int k = i + 1; k < size; k++) 
        {
            if (bond[i]->err != NULL) {
                    if (mx_strcmp(bond[i]->name, bond[k]->name) == 1)
                        swap_li(&(bond[i]), &(bond[k]));
            }
            else if (cmp(bond[i], bond[k], fl) == fl->r) {
                swap_li(&(bond[i]), &(bond[k]));
			}
		}
	}
}
