#include <stdlib.h>
#include <string.h>

#include "../tools/tools.h"
#include "exectree.h"

struct node *createcmdnode(char *argv[])
{
    struct node *n = tree_cmd_create();
    size_t i = 0;
    while (argv[i])
    {
        i++;
    }
    i++;
    char **arg = calloc(i, sizeof(char *));
    for (size_t j = 0; j < i; j++)
    {
        if (argv[j])
            arg[j] = mystrdup(argv[j]);
    }
    n->data.cmdnode.argv = arg;
    return n;
}

void faketree(struct shell *s)
{
    char *arg1[] = { "echo", "Bonsoir", NULL };
    char *arg2[] = { "uniq", "-c", NULL };
    char *arg3[] = { "uniq", "-c", NULL };

    struct node *n1 = createcmdnode(arg1);
    //struct node *n1 = tree_bang_create(n11);

    struct node *n2 = createcmdnode(arg2);
    struct node *n3 = createcmdnode(arg3);

    struct node *n4 = tree_pipe_create(n1, n2);
    struct node *n5 = tree_pipe_create(n4, n3);
    // tree_print_node(n5, stdout);
    exectree(n5, s);
    tree_destroy(n5);
}