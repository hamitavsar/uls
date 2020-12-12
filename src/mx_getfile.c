#include "uls.h"

static t_li *create_file_node(t_li *arg) {
    t_li *node = (t_li *)malloc(1 * sizeof (t_li));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    if (arg->err)
        node->err = mx_strdup(arg->err);
    else 
        node->err = NULL;
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
        node->open = arg->open;
    else 
        node->open = NULL;
    return node;
}

static void create_fde(t_li ***files, t_li ***dirs, 
                        t_li ***errors, t_li ***args) {
    int j = 0;
    int nDir = 0;
    int nErr = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL) {
            if (!IS_DIR((*args)[i]->info.st_mode) ) {
                    j++;
            } else
                nDir++;
        } else
            nErr++;
    if (j > 0)
        *files = malloc((j + 1) * sizeof(t_li *));
    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(t_li *));
    if (nErr > 0)
        *errors = malloc((nErr + 1) * sizeof(t_li *));
}

static s_type *create_num() {
    s_type *num = malloc(sizeof (s_type));

    num->n_d = 0;
    num->n_e = 0;
    num->n_f = 0;
    num->i = 0;
    return num;
}

static void fdir(t_li **args, s_type *num, t_li ***files, t_li ***dirs) {
    if (!IS_DIR((*args)->info.st_mode)) {
        (*files)[num->n_f++] = create_file_node((*args));
        (*files)[num->n_f] = NULL;
    }
    else {
        (*dirs)[num->n_d++] = create_file_node((*args));
        (*dirs)[num->n_d] = NULL;
    }
}

t_li **mx_get_files(t_li ***args, st_fl *fl) {
    t_li **files = NULL;
    t_li **dirs = NULL;
    t_li **errors = NULL;
    s_type *num = create_num();

    create_fde(&files, &dirs, &errors, args);
    for (; (*args)[num->i] != NULL; num->i++) {
        if ((*args)[num->i]->err == NULL)
            fdir(&(*args)[num->i], num, &files, &dirs);
        else {
            errors[num->n_e++] = create_file_node((*args)[num->i]);
            errors[num->n_e] = NULL;
        }
    }
    if (num->n_d > 1)
        fl->files = 1;
    mx_del_liarr(args, dirs);
    mx_out_err(&errors, fl);
    free(num);
    return files;
}
