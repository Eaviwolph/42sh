#include <stdlib.h>
#include <string.h>

#include "exectree.h"

static char *mstrdup(const char *s)
{
    size_t len = strlen(s) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, s, len);
}

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
            arg[j] = mstrdup(argv[j]);
    }
    n->data.cmdnode.argv = arg;
    return n;
}

void faketree(struct shell *s)
{
    char *arg1[] = { "echo", "Bonsoir", NULL };
    char *arg2[] = { "test", "1", NULL };
    char *arg3[] = { "echo", "world", NULL };

    struct node *n1 = createcmdnode(arg1);
    struct node *n2 = createcmdnode(arg2);
    struct node *n3 = createcmdnode(arg3);

    struct node *n4 = tree_or_create(n2, n3);
    struct node *n5 = tree_and_create(n1, n4);
    // tree_print_node(n1, stdout);
    exectree(n5, s);
    tree_destroy(n5);
}