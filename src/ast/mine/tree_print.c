#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "tree.h"

struct tree_print_table_elem
{
    enum node_type type;
    void (*function)(struct node *, FILE *);
};

struct tree_print_table_elem dictionary[NODE_TYPE_COUNT] = {
    { IF, tree_if_print },
    { FOR, tree_for_print },
    { WHILE, tree_while_print } /*,
     { CMD, tree_cmd_print },
     { AND, tree_and_print },
     { OR, tree_or_print },
     { SUBSHELL, tree_subshell_print },
     { FUNCDEC, tree_funcdec_print },
     { BANG, tree_bang_print },
     { PIPE, tree_pipe_print },
     { SEPAND, tree_sepand_print },
     { SEP, tree_sep_print },
     { CASE, tree_case_print },
     { RED, tree_red_print }*/
};

void tree_print(struct node *tree_ref, const char *filename)
{
    if (tree_ref)
    {
        if (!filename)
            filename = "test.txt"; // TO CHANGE

        FILE *stream = fopen(filename, "w");
        if (stream)
        {
            tree_print_node(tree_ref, stream);
            fclose(stream);
        }
    }
}

void tree_print_node(struct node *tree_ref, FILE *stream)
{
    assert(tree_ref);
    for (int i = 0; i < NODE_TYPE_COUNT; i++)
        if (dictionary[i].type == tree_ref->type)
            (dictionary[i].function)(tree_ref, stream);
}