#include "uls.h"

static t_li *create_li_node(char *data) {
    t_li *node = (t_li *)malloc(1 * sizeof(t_li));

    node->name = mx_strdup(data);
    node->path = mx_strdup(data);
    node->err = NULL;
    if (lstat(data, &(node->info)) == -1)
        node->err = mx_strdup(strerror(errno));	
    node->open = NULL;
    return node;
}

static t_li **create_list(char **name, int count) {
    t_li **new = malloc(count * sizeof(t_li *));
    int i = 0;

    for (i = 0; name[i]; i++)
        new[i] = create_li_node(name[i]);
    new[i] = NULL;
    return new;
}

static char **names(int argc, char **argv, int i, int *count) {
    int j = i;
    char **names = NULL;

    if (i == argc) {
        *count = 2;
        names = malloc(2 * sizeof(char *));
        names[0] = mx_strdup(".");
        names[1] = NULL;
    }
    else {
        for (; argv[j]; j++) {
        }
        names = malloc((j - i + 1) * sizeof(char *));
        for(j = 0; argv[i]; i++, j++) {
            names[j] = mx_strdup(argv[i]);
        }
        names[j] = NULL;
        *count = j + 1;
    }
    return names;
}

t_li **mx_get_names(int argc, char **argv, int i) {
    int count = 0;
    char **name = names(argc, argv, i, &count);
    t_li **args = create_list(name, count);

    mx_del_strarr(&name);
    return args;
}
