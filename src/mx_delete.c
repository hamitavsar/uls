#include "uls.h"

static t_li *create_file_node(t_li *arg) {
    t_li *node = (t_li *)malloc(1 * sizeof (t_li));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    node->err = NULL;
    if (arg->err != NULL)
        node->err = mx_strdup(arg->err);
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
        node->open = arg->open;
    else 
        node->open = NULL;
    return node;
}

static void create_fde(t_li ***dirs, t_li ***args) {
    int nDir = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL)
            if (IS_DIR((*args)[i]->info.st_mode) && 
                mx_strcmp((*args)[i]->name, ".") != 0 &&
                mx_strcmp((*args)[i]->name, "..") != 0)
                nDir++;
    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(t_li *));
}

void mx_del_files(t_li ***args, st_fl *fl) {
    t_li **dirs = NULL;
    int nDir = 0;

    create_fde(&dirs, args);
    for (int i = 0; (*args)[i] != NULL; i++) {
        if ((*args)[i]->err == NULL) {
            if (IS_DIR((*args)[i]->info.st_mode) && 
                mx_strcmp((*args)[i]->name, ".") != 0 && 
                mx_strcmp((*args)[i]->name, "..") != 0) {
                dirs[nDir++] = create_file_node((*args)[i]);
                dirs[nDir] = NULL;
            }
        }
    }
    fl->files = 1;
    mx_del_liarr(args, dirs);
}
